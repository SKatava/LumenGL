// src/renderer/Mesh.cpp
#include "lumengl/renderer/Mesh.h"
#include <math.h>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace lgl {

Mesh::Mesh(std::span<const Vertex> vertices,
           std::span<const uint32_t> indices,
           GLenum usage)
    : m_indexCount(static_cast<GLsizei>(indices.size()))
{
    m_vao.bind();
    m_vbo.upload(vertices, usage);
    m_ebo.upload(indices,  usage);
    setupAttribs();
    m_vao.unbind();
}

void Mesh::setupAttribs() const {
    // position — location 0
    m_vao.attrib(0, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, position));
    // normal   — location 1
    m_vao.attrib(1, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, normal));
    // uv       — location 2
    m_vao.attrib(2, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, uv));
}

void Mesh::updateVertices(std::span<const Vertex> vertices) {
    m_vbo.update(vertices);
}

Mesh Mesh::quad() {
    const std::vector<Vertex> verts = {
        // position             normal      uv
        {{ -0.5f, -0.5f, 0.f }, { 0,0,1 }, { 0.f, 0.f }},
        {{  0.5f, -0.5f, 0.f }, { 0,0,1 }, { 1.f, 0.f }},
        {{  0.5f,  0.5f, 0.f }, { 0,0,1 }, { 1.f, 1.f }},
        {{ -0.5f,  0.5f, 0.f }, { 0,0,1 }, { 0.f, 1.f }},
    };
    const std::vector<uint32_t> idx = { 0,1,2, 2,3,0 };
    return Mesh(verts, idx);
}

Mesh Mesh::cube() {
    const std::vector<Vertex> verts = {
        // position             normal      uv
        // front
        {{-0.5f,-0.5f, 0.5f}, { 0, 0, 1}, {0.f,0.f}},
        {{ 0.5f,-0.5f, 0.5f}, { 0, 0, 1}, {1.f,0.f}},
        {{ 0.5f, 0.5f, 0.5f}, { 0, 0, 1}, {1.f,1.f}},
        {{-0.5f, 0.5f, 0.5f}, { 0, 0, 1}, {0.f,1.f}},
        // back
        {{ 0.5f,-0.5f,-0.5f}, { 0, 0,-1}, {0.f,0.f}},
        {{-0.5f,-0.5f,-0.5f}, { 0, 0,-1}, {1.f,0.f}},
        {{-0.5f, 0.5f,-0.5f}, { 0, 0,-1}, {1.f,1.f}},
        {{ 0.5f, 0.5f,-0.5f}, { 0, 0,-1}, {0.f,1.f}},
        // left
        {{-0.5f,-0.5f,-0.5f}, {-1, 0, 0}, {0.f,0.f}},
        {{-0.5f,-0.5f, 0.5f}, {-1, 0, 0}, {1.f,0.f}},
        {{-0.5f, 0.5f, 0.5f}, {-1, 0, 0}, {1.f,1.f}},
        {{-0.5f, 0.5f,-0.5f}, {-1, 0, 0}, {0.f,1.f}},
        // right
        {{ 0.5f,-0.5f, 0.5f}, { 1, 0, 0}, {0.f,0.f}},
        {{ 0.5f,-0.5f,-0.5f}, { 1, 0, 0}, {1.f,0.f}},
        {{ 0.5f, 0.5f,-0.5f}, { 1, 0, 0}, {1.f,1.f}},
        {{ 0.5f, 0.5f, 0.5f}, { 1, 0, 0}, {0.f,1.f}},
        // top
        {{-0.5f, 0.5f, 0.5f}, { 0, 1, 0}, {0.f,0.f}},
        {{ 0.5f, 0.5f, 0.5f}, { 0, 1, 0}, {1.f,0.f}},
        {{ 0.5f, 0.5f,-0.5f}, { 0, 1, 0}, {1.f,1.f}},
        {{-0.5f, 0.5f,-0.5f}, { 0, 1, 0}, {0.f,1.f}},
        // bottom
        {{-0.5f,-0.5f,-0.5f}, { 0,-1, 0}, {0.f,0.f}},
        {{ 0.5f,-0.5f,-0.5f}, { 0,-1, 0}, {1.f,0.f}},
        {{ 0.5f,-0.5f, 0.5f}, { 0,-1, 0}, {1.f,1.f}},
        {{-0.5f,-0.5f, 0.5f}, { 0,-1, 0}, {0.f,1.f}},
    };

    const std::vector<uint32_t> idx = {
         0, 1, 2,  2, 3, 0,   // front
         4, 5, 6,  6, 7, 4,   // back
         8, 9,10, 10,11, 8,   // left
        12,13,14, 14,15,12,   // right
        16,17,18, 18,19,16,   // top
        20,21,22, 22,23,20,   // bottom
    };

    return Mesh(verts, idx);
}

using EdgeKey = uint64_t;

static EdgeKey edgeKey(uint32_t a, uint32_t b) {
    return a < b
        ? (static_cast<uint64_t>(a) << 32) | b
        : (static_cast<uint64_t>(b) << 32) | a;
}

static uint32_t midpoint(
    uint32_t a, uint32_t b,
    std::vector<Vertex>& verts,
    std::unordered_map<EdgeKey, uint32_t>& cache)
{
    EdgeKey key = edgeKey(a, b);
    auto it = cache.find(key);
    if (it != cache.end()) return it->second;

    // Average positions and normalize onto unit sphere
    glm::vec3 pa = verts[a].position;
    glm::vec3 pb = verts[b].position;
    glm::vec3 mid = glm::normalize((pa + pb) * 0.5f);

    // Normal = position on unit sphere
    // UV from spherical coordinates
    float u = 0.5f + std::atan2(mid.z, mid.x) / (2.f * glm::pi<float>());
    float v = 0.5f - std::asin(glm::clamp(mid.y, -1.f, 1.f)) / glm::pi<float>();

    uint32_t idx = static_cast<uint32_t>(verts.size());
    verts.push_back({ mid, mid, { u, v } }); // normal == position for unit sphere
    cache[key] = idx;
    return idx;
}

Mesh Mesh::icosphere(int subdivisions) {
    const float t = (1.f + std::sqrt(5.f)) / 2.f;

    std::vector<glm::vec3> positions;
    positions.reserve(12);

    auto addPos = [&](glm::vec3 p) {
        positions.push_back(glm::normalize(p));
    };

    addPos({-1, t, 0}); addPos({ 1, t, 0});
    addPos({-1,-t, 0}); addPos({ 1,-t, 0});
    addPos({ 0,-1, t}); addPos({ 0, 1, t});
    addPos({ 0,-1,-t}); addPos({ 0, 1,-t});
    addPos({ t, 0,-1}); addPos({ t, 0, 1});
    addPos({-t, 0,-1}); addPos({-t, 0, 1});

    std::vector<uint32_t> idx = {
        0,11,5,  0,5,1,   0,1,7,   0,7,10,  0,10,11,
        1,5,9,   5,11,4,  11,10,2, 10,7,6,  7,1,8,
        3,9,4,   3,4,2,   3,2,6,   3,6,8,   3,8,9,
        4,9,5,   2,4,11,  6,2,10,  8,6,7,   9,8,1
    };

    // Subdivide positions only — no UVs yet
    std::unordered_map<EdgeKey, uint32_t> cache;

    for (int s = 0; s < subdivisions; ++s) {
        std::vector<uint32_t> next;
        next.reserve(idx.size() * 4);

        for (size_t i = 0; i < idx.size(); i += 3) {
            uint32_t a = idx[i], b = idx[i+1], c = idx[i+2];

            // Midpoint on positions only
            auto midPos = [&](uint32_t x, uint32_t y) -> uint32_t {
                EdgeKey key = edgeKey(x, y);
                auto it = cache.find(key);
                if (it != cache.end()) return it->second;
                glm::vec3 mid = glm::normalize((positions[x] + positions[y]) * 0.5f);
                uint32_t newIdx = static_cast<uint32_t>(positions.size());
                positions.push_back(mid);
                cache[key] = newIdx;
                return newIdx;
            };

            uint32_t ab = midPos(a, b);
            uint32_t bc = midPos(b, c);
            uint32_t ca = midPos(c, a);

            next.insert(next.end(), {
                a,ab,ca,  b,bc,ab,  c,ca,bc,  ab,bc,ca
            });
        }

        idx = std::move(next);
        cache.clear();
    }

    // Now build final vertices with correct UVs
    // Fix seam and poles by duplicating where needed
    std::vector<Vertex> verts;
    std::vector<uint32_t> finalIdx;
    verts.reserve(positions.size() + subdivisions * 100);

    auto calcUV = [](const glm::vec3& p) -> glm::vec2 {
        float u = 0.5f + std::atan2(p.z, p.x) / (2.f * glm::pi<float>());
        float v = 0.5f + std::asin(glm::clamp(p.y, -1.f, 1.f)) / glm::pi<float>();
        return { u, v };
    };

    for (size_t i = 0; i < idx.size(); i += 3) {
        glm::vec3 pa = positions[idx[i]];
        glm::vec3 pb = positions[idx[i+1]];
        glm::vec3 pc = positions[idx[i+2]];

        glm::vec2 uva = calcUV(pa);
        glm::vec2 uvb = calcUV(pb);
        glm::vec2 uvc = calcUV(pc);

        // Detect seam crossing — if any U difference > 0.5, the triangle wraps
        // Fix by pushing the low U vertex to the high side (add 1.0)
        auto fixSeam = [](glm::vec2& a, glm::vec2& b, glm::vec2& c) {
            // Find the average U to detect which side the triangle is on
            if (std::abs(a.x - b.x) > 0.5f) {
                if (a.x < b.x) a.x += 1.f; else b.x += 1.f;
            }
            if (std::abs(b.x - c.x) > 0.5f) {
                if (b.x < c.x) b.x += 1.f; else c.x += 1.f;
            }
            if (std::abs(a.x - c.x) > 0.5f) {
                if (a.x < c.x) a.x += 1.f; else c.x += 1.f;
            }
        };

        fixSeam(uva, uvb, uvc);

        // Fix poles — a pole vertex has v=0 or v=1, u is undefined
        // Set pole U to the average of the other two vertices
        auto fixPole = [](glm::vec3 pos, glm::vec2& uv,
                          glm::vec2 other1, glm::vec2 other2)
        {
            if (std::abs(pos.x) < 1e-6f && std::abs(pos.z) < 1e-6f) {
                uv.x = (other1.x + other2.x) * 0.5f;
            }
        };

        fixPole(pa, uva, uvb, uvc);
        fixPole(pb, uvb, uva, uvc);
        fixPole(pc, uvc, uva, uvb);

        // Each triangle gets its own 3 vertices — no sharing across seam
        uint32_t base = static_cast<uint32_t>(verts.size());
        verts.push_back({ pa, pa, uva });
        verts.push_back({ pb, pb, uvb });
        verts.push_back({ pc, pc, uvc });
        finalIdx.insert(finalIdx.end(), { base, base+1, base+2 });
    }

    return Mesh(verts, finalIdx);
}

// ─────────────────────────────────────────────
// UV Sphere — simpler, good for textured planets
// ─────────────────────────────────────────────
Mesh Mesh::uvsphere(int stacks, int slices) {
    std::vector<Vertex> verts;
    std::vector<uint32_t> idx;

    for (int i = 0; i <= stacks; ++i) {
        float phi = glm::pi<float>() * static_cast<float>(i) / static_cast<float>(stacks);
        float y   = std::cos(phi);
        float r   = std::sin(phi);

        for (int j = 0; j <= slices; ++j) {
            float theta = 2.f * glm::pi<float>() * static_cast<float>(j) / static_cast<float>(slices);
            float x = r * std::cos(theta);
            float z = r * std::sin(theta);

            glm::vec3 pos    = { x, y, z };
            glm::vec3 normal = pos; // unit sphere: normal == position
            glm::vec2 uv     = {
                static_cast<float>(j) / static_cast<float>(slices),
                static_cast<float>(i) / static_cast<float>(stacks)
            };

            verts.push_back({ pos, normal, uv });
        }
    }

    for (int i = 0; i < stacks; ++i) {
        for (int j = 0; j < slices; ++j) {
            uint32_t a = i * (slices + 1) + j;
            uint32_t b = a + slices + 1;

            idx.insert(idx.end(), {
                a, b, a + 1,
                b, b + 1, a + 1
            });
        }
    }

    return Mesh(verts, idx);
}

} 
