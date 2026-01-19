#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include <vector>
#include <memory>
#include <string>
#include <map>
#include <algorithm>
#include <ranges>

#include <LumenGL/Camera.h>
#include <LumenGL/RenderObject.h>
#include <LumenGL/Texture.h>

namespace lumen::gl {
    class Scene {
        public:
            //Constructors and ownership managment-----------

            Scene(const std::string& name = "default_scene");

            Scene(const Scene&) = delete;
            Scene& operator=(const Scene&) = delete;

            Scene(Scene&&) noexcept = default;
            Scene& operator=(Scene&&) noexcept = default;

            ~Scene();

            //Getters and setters----------------------------

            //Core interface---------------------------------

            void AddObject(std::shared_ptr<RenderObject> object);
            void RemoveObject();
            void SetCamera();
            void RenderScene(); 
            std::shared_ptr<ShaderProgram> GetOrLoadProgram(const std::string& vertPath, const std::string& fragPath, const std::string& name);
            std::shared_ptr<Texture> GetOrLoadTexture(const std::string& texturePath);

        private:
            std::string m_name;
            std::vector<std::shared_ptr<RenderObject>> m_objects;
            std::shared_ptr<Camera> m_camera;
            std::map<std::string, std::shared_ptr<ShaderProgram>> m_programCache;
            std::map<std::string, std::shared_ptr<Texture>> m_textureCache;
    };

}
#endif
