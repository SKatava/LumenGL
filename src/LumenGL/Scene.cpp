#include <LumenGL/Scene.h>

#include <iostream>

namespace lumen::gl {

    //Scene constructor - sets default camera and shader program
    Scene::Scene(const std::string& name) : m_name(name) {
        m_camera = std::make_shared<Camera>(800, 800, glm::vec3(0.0f, 0.0f, 5.0f));
        GetOrLoadProgram("../shaders/default.vert", "../shaders/default.frag", "DEFAULT_PROGRAM");
        GetOrLoadTexture("../assets/textures/white-granite.png");
    }

    //Scene destructor
    Scene::~Scene() {}

    std::vector<std::shared_ptr<RenderObject>> Scene::GetRenderObjects() const noexcept {
        return m_objects;
    }

    //Add the object the scene
    void Scene::AddObject(std::shared_ptr<RenderObject> object) {
        m_objects.push_back(object); 
        m_shouldSort = true;
    }

    //Render all objects in the scene
    //TODO - do instancing for massive amount of objects/draw calls
    void Scene::RenderScene() {
        if(m_shouldSort) SortObjects();

        Material* currentMaterial = nullptr;
        
        for (const auto* obj : m_sorted) {
            if (!currentMaterial || obj->material->GetProgram().get() != currentMaterial->GetProgram().get()) {
                currentMaterial = obj->material.get();
                currentMaterial->GetProgram()->Activate();
                m_camera->Matrix(45.0f, 0.1f, 100.0f, currentMaterial->GetProgram(), "camMatrix");
            }
            
            obj->material->GetTexture()->Bind();
            obj->material->SetUniforms();
            obj->mesh->Bind();
            obj->transform.Apply(currentMaterial->GetProgram(), "modelMatrix");

            glDrawElements(obj->drawMode, obj->mesh->GetIndicesCount(), GL_UNSIGNED_INT, 0);
        }
    }    

    //Loads the shader to the cache(if it doesn't exist) and returns it
    std::shared_ptr<ShaderProgram> Scene::GetOrLoadProgram(const std::string& vertPath, const std::string& fragPath, const std::string& name) {
        auto it = m_programCache.find(name);

        if(it != m_programCache.end()) {
            return it->second;
        }

        std::vector<std::string> files = {vertPath, fragPath};
        std::vector<ShaderType> types = {ShaderType::VERTEX, ShaderType::FRAGMENT};
        m_programCache[name] = std::make_shared<ShaderProgram>(files, types);    
        return m_programCache[name];
    }

    //Loads the texture to the cache(if it doesn't exist) and returns it
    std::shared_ptr<Texture> Scene::GetOrLoadTexture(const std::string& texturePath) {
        auto it = m_textureCache.find(texturePath);

        if (it != m_textureCache.end()) {
            return it->second;
        }

        m_textureCache[texturePath] = std::make_shared<Texture>(texturePath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
        return m_textureCache[texturePath];
    }

    //Sort all the objects int the scene by shader program
    //TODO - make better sorting system since this one doesnt account for same shader and different textures
    void Scene::SortObjects() {
        m_sorted.clear();
        m_sorted.reserve(m_objects.size());

        for (const auto& obj : m_objects) {
            m_sorted.push_back(obj.get());
        }

        std::ranges::sort(m_sorted, {}, [](const RenderObject* obj) {return obj->material->GetProgram(); } );

        m_shouldSort = false;
    }
}


