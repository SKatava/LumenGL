#include <renderer/Renderer.h>

//Constructor - doesn't do anything
Renderer::Renderer() : m_program() {
    std::vector<std::string> files = {"../shaders/default.vert", "../shaders/default.frag"};
    std::vector<Shader_type> types = {Shader_type::VERTEX, Shader_type::FRAGMENT};
    m_program = Shader_program(files, types);

    Vertex v1, v2, v3, v4, v5;

    v1.position = {-0.5f, 0.0f, 0.5f};
    v1.texture_pos = {0.f, 0.f};
    v2.position = {-0.5f, 0.f, -0.5f};
    v2.texture_pos = {5.f, 0.f};
    v3.position = {0.5f, 0.f, -0.5f};
    v3.texture_pos = {0.f, 0.f};
    v4.position = {0.5f, 0.f, 0.5f};
    v4.texture_pos = {5.f, 0.f};
    v5.position = {0.f, 0.8f, 0.f};
    v5.texture_pos = {2.5f, 5.f};

    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4  
    };
        
    std::vector<Vertex> vertices = {v1, v2, v3, v4, v5};

    obj.mesh = new Mesh();
    obj.material = new Material();
    
    obj.mesh->Init_vertices(vertices, GL_STATIC_DRAW);
    obj.mesh->Init_indices(indices, 18, GL_STATIC_DRAW);
    obj.material->Set_program(&m_program);
    obj.material->Set_color({0.2f, 0.5f, 0.8f});
    Texture texture("../assets/textures/white-granite.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    obj.material->Set_Texture(texture);
    obj.draw_type = GL_TRIANGLES;

    cam = Camera(800, 800, glm::vec3(0.0f, 0.0f, 2.0f));
}

// Initializes OpenGL and default 
void Renderer::Init() {
    glViewport(0, 0, 800, 800);       
}

//Renders everything in queue
void Renderer::Render() {
    glClearColor(0.f, 0.f, 0.f, 1.f); 
    glClear(GL_COLOR_BUFFER_BIT);
    obj.material->Bind();
    cam.Matrix(45.0f, 0.1f, 100.0f, m_program, "camMatrix");
    obj.mesh->Bind();
    glDrawArrays(obj.draw_type, 0, obj.mesh->Get_vertices_count());

}

//Stop the renderer and delete the garbage
void Renderer::Shutdown() {
    obj.material->Delete();
    obj.mesh->Delete();

    delete obj.mesh;
    delete obj.material;
}
