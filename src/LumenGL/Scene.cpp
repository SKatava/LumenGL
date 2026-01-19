#include <LumenGL/Scene.h>

//Scene constructor - sets default camera and shader programs
lumen::gl::Scene::Scene(const std::string& name) : m_name(name) {
    m_camera = std::make_shared<Camera>(800, 800, glm::vec3(0.0f, 0.0f, 5.0f));
    GetOrLoadProgram("../shaders/default.vert", "../shaders/default.frag", "DEFAULT_PROGRAM");
    GetOrLoadTexture("../assets/textures/white-granite.png");
}

//Scene destructor
lumen::gl::Scene::~Scene() {}

//Add the object the scene
void lumen::gl::Scene::AddObject(std::shared_ptr<RenderObject> object) {
    m_objects.push_back(object); 
}

//Render all objects in the scene - sorted by material for fewer draw calls
void lumen::gl::Scene::RenderScene() {

    std::vector<const RenderObject*> sorted;
    sorted.reserve(m_objects.size());

    for (const auto& obj : m_objects) {
        sorted.push_back(obj.get());
    }

    std::ranges::sort(sorted, {}, &RenderObject::material);
    
    Material* currentMaterial = nullptr;

    for (const auto* obj : sorted) {
        if (obj->material.get() != currentMaterial) {
            currentMaterial = obj->material.get();
            currentMaterial->Bind();

            m_camera->Matrix(45.0f, 0.1f, 100.0f, currentMaterial->GetProgram(), "camMatrix");

        }

        obj->mesh->Bind();
        
        obj->transform.Apply(currentMaterial->GetProgram(), "modelMatrix");

        glDrawElements(obj->drawMode, obj->mesh->GetIndicesCount(), GL_UNSIGNED_INT, 0);
    }
}

//Loads the shader to the cache and returns it
std::shared_ptr<ShaderProgram> lumen::gl::Scene::GetOrLoadProgram(const std::string& vertPath, const std::string& fragPath, const std::string& name) {
    auto it = m_programCache.find(name);

    if(it != m_programCache.end()) {
        return it->second;
    }

    std::vector<std::string> files = {vertPath, fragPath};
    std::vector<ShaderType> types = {ShaderType::VERTEX, ShaderType::FRAGMENT};
    m_programCache[name] = std::make_shared<ShaderProgram>(files, types);    
    return m_programCache[name];
}

std::shared_ptr<Texture> lumen::gl::Scene::GetOrLoadTexture(const std::string& texturePath) {
    auto it = m_textureCache.find(texturePath);
    
    if (it != m_textureCache.end()) {
        return it->second;
    }

    m_textureCache[texturePath] = std::make_shared<Texture>(texturePath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    return m_textureCache[texturePath];
}
