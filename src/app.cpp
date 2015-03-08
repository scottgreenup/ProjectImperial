
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-4-a-colored-cube/

#include <cmath>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "app.hpp"
#include "shader.hpp"
#include "triangle.hpp"
#include "cube.hpp"

App::App(int width, int height, const char* name)
    : m_WindowWidth(width)
    , m_WindowHeight(height)
    , m_WindowName(name) {

}

App::~App() {

}

bool App::Initialise() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialise the GLFW." << std::endl;
        return false;
    }

    // create the window using GLFW
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x AA
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    this->window = glfwCreateWindow(
        this->m_WindowWidth,
        this->m_WindowHeight,
        this->m_WindowName,
        glfwGetPrimaryMonitor(),
        NULL
    );
    if (!this->window) {
        std::cerr << "Failed to initialise the GLFW window." << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(this->window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(this->window, App::KeyCallback);
    glfwSetErrorCallback(App::ErrorCallback);

    // setup OpenGL specific configuration
    std::cerr << "Using " << glGetString(GL_VERSION) << std::endl;
    // TODO work out what `glewExperimental = true;` does
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialise GLEW." << std::endl;
        return false;
    }
    glClearColor(0.15, 0.1, 0.35, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // create our objects
    this->m_pkTriangle = new Triangle();
    this->m_cube = new Cube();

    // create our shaders
    this->m_simpleShader = new Shader(
        "shaders/shader.vert",
        "shaders/shader.frag"
    );
    if (!this->m_simpleShader->Load()) {
        std::cerr << "Shaders could not be loaded." << std::endl;
        return false;
    }

    return true;
}

void App::CleanUp() {
    delete this->m_simpleShader;
    delete this->m_cube;
    delete this->m_pkTriangle;
    glfwDestroyWindow(window);
    glfwTerminate();
}


bool App::Update() {
    if (glfwWindowShouldClose(this->window)) {
        return false;
    }   

    glfwPollEvents();
    return true;
}

void App::Render() {
    int width = 0;
    int height = 0;
    glfwGetFramebufferSize(this->window, &width, &height);
    float ratio = width / (float) height;

    float x = 5 * sinf(glfwGetTime() * 3.0f);

    glm::mat4 projection = glm::perspective(45.0f, ratio, 0.1f, 1000.0f);
    glm::mat4 view = glm::lookAt(
        glm::vec3(x,5,-5), // pos
        glm::vec3(0,0,0), // look at
        glm::vec3(0,1,0)  // up
    );

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 mvp;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->m_simpleShader->Use();

    GLuint matrixId = 0;

    matrixId = glGetUniformLocation(this->m_simpleShader->Id(), "MVP");
    model = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
    mvp = projection * view * model;
    glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp[0][0]);
    this->m_pkTriangle->Render();

    matrixId = glGetUniformLocation(this->m_simpleShader->Id(), "MVP");
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::rotate(model, 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    mvp = projection * view * model;
    glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp[0][0]);
    this->m_cube->Render();

    glfwSwapBuffers(window);
}

void App::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    (void)scancode;
    (void)mods;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void App::ErrorCallback(int error, const char* desc) {
    std::cerr << "error occured (" << error << "): " << desc << std::endl;
}
