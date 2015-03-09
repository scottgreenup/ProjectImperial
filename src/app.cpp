
// create camera
// window pointer
// then make primitive
// cube and triangle derive from primitve


// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-4-a-colored-cube/

#include <cmath>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "app.hpp"

#include "primitive.hpp"
#include "camera.hpp"
#include "shader.hpp"
#include "triangle.hpp"
#include "cube.hpp"

App::App(int width, int height, const char* name)
    : m_WindowWidth(width)
    , m_WindowHeight(height)
    , m_WindowName(name) { }

App::~App() { }

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

    // create our shaders
    this->m_simpleShader = new Shader(
        "shaders/shader.vert",
        "shaders/shader.frag"
    );
    if (!this->m_simpleShader->Load()) {
        std::cerr << "Shaders could not be loaded." << std::endl;
        return false;
    }

    int width = 0;
    int height = 0;
    glfwGetFramebufferSize(this->window, &width, &height);

    Camera::Get()->SetProjectionMatrix(
        45.0f, 
        width / (float)height, 
        0.1f, 
        1000.f
    );

    float cx = 0.0f;
    float cy = 0.0f;
    float cz = 0.0f;

    GLfloat verts[] = {
        cx - 1.0f, cy - 1.0f, cz + 0.0f,
        cx + 1.0f, cy - 1.0f, cz + 0.0f,
        cx + 0.0f, cy + 1.0f, cz + 0.0f,
    };

    // generate the colors
    const int vertices = 3;
    GLfloat colors[vertices * 3];

    for (int i = 0; i < vertices; ++i) {
        colors[3 * i + 0] = sinf(i / (float)vertices);
        colors[3 * i + 1] = cosf(i / (float)vertices);
        colors[3 * i + 2] = i / (float)vertices;
    }
    this->m_prim = new Primitive(verts, colors, 3);
    this->m_prim->AttachShader(this->m_simpleShader);

    this->m_cube = new Cube();
    this->m_cube->AttachShader(this->m_simpleShader);

    return true;
}

void App::CleanUp() {
    delete this->m_simpleShader;
    delete this->m_prim;
    delete this->m_cube;
    //delete this->m_pkTriangle;
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->m_cube->Render();
    this->m_prim->Render();

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
