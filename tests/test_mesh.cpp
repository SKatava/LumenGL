// tests/test_mesh.cpp
#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <cmath>
#include "lumengl/renderer/Mesh.h"

TEST(IcosphereData, VerticesOnUnitSphere) {
    auto data = lgl::icosphereData(2);
    for (const auto& v : data.vertices) {
        float len = glm::length(v.position);
        EXPECT_NEAR(len, 1.0f, 1e-5f)
            << "Vertex not on unit sphere: " << len;
    }
}

TEST(IcosphereData, NormalsMatchPosition) {
    // For a unit sphere, normal == position
    auto data = lgl::icosphereData(2);
    for (const auto& v : data.vertices) {
        EXPECT_NEAR(v.normal.x, v.position.x, 1e-5f);
        EXPECT_NEAR(v.normal.y, v.position.y, 1e-5f);
        EXPECT_NEAR(v.normal.z, v.position.z, 1e-5f);
    }
}

TEST(IcosphereData, UVsInRange) {
    auto data = lgl::icosphereData(2);
    for (const auto& v : data.vertices) {
        EXPECT_GE(v.uv.x, 0.0f);
        EXPECT_LE(v.uv.x, 2.0f); // seam fix allows up to 2.0
        EXPECT_GE(v.uv.y, 0.0f);
        EXPECT_LE(v.uv.y, 1.0f);
    }
}

TEST(IcosphereData, IndexCountGrowsWithSubdivision) {
    auto d0 = lgl::icosphereData(0);
    auto d1 = lgl::icosphereData(1);
    auto d2 = lgl::icosphereData(2);
    // Each subdivision multiplies triangle count by 4
    EXPECT_EQ(d1.indices.size(), d0.indices.size() * 4);
    EXPECT_EQ(d2.indices.size(), d1.indices.size() * 4);
}

TEST(IcosphereData, IndicesInBounds) {
    auto data = lgl::icosphereData(3);
    for (uint32_t idx : data.indices) {
        EXPECT_LT(idx, data.vertices.size());
    }
}

TEST(QuadData, HasFourVertices) {
    auto data = lgl::quadData();
    EXPECT_EQ(data.vertices.size(), 4);
    EXPECT_EQ(data.indices.size(), 6);
}

TEST(QuadData, NormalsFaceForward) {
    auto data = lgl::quadData();
    for (const auto& v : data.vertices) {
        EXPECT_NEAR(v.normal.z, 1.0f, 1e-5f);
    }
}
