#include <LumenGL/Renderer.h>

//Constructor - doesn't do anything
lumen::gl::Renderer::Renderer() {}

//Destructor - doesn't do anything
lumen::gl::Renderer::~Renderer() {}

//Set the position and the size of the viewport in window coordinates
void lumen::gl::Renderer::SetViewport(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
    m_viewport = glm::ivec4(x, y, width, height);
}

//Set the clear color - color of the screen
void lumen::gl::Renderer::SetColor(int r, int g, int b, int a) {
    m_clearColor = glm::vec4(r, g, b, a);
}

//Set the active scene the renderer will render
void lumen::gl::Renderer::SetActiveScene(Scene* scene) {
    m_activeScene = scene;
}

//Initializes OpenGL and default 
void lumen::gl::Renderer::Init() const {
    glViewport(m_viewport.x, m_viewport.y, m_viewport.z, m_viewport.w); 
    glEnable(GL_DEPTH_TEST);
}

//Prepeare the screen for rendering
void lumen::gl::Renderer::BeginFrame() const {
    glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//Render active scene
void lumen::gl::Renderer::Render() const {
    m_activeScene->RenderScene();    
}

//After frame - doesn't do anythin rn
void lumen::gl::Renderer::EndFrame() const {}

