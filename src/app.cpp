
// create camera
// window pointer
// then make primitive
// cube and triangle derive from primitve


// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-4-a-colored-cube/

#include <cstdlib>
#include <cmath>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "app.h"

#include "primitive.h"
#include "camera.h"
#include "shader.h"
#include "cube.h"

App::App(int width, int height, const char* name)
    : m_cubeCount(50)
    , m_WindowWidth(width)
    , m_WindowHeight(height)
    , m_WindowName(name)
{}

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
        this->m_WindowName.c_str(),
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

    this->m_cubeGrid = new Cube*[m_cubeCount];

    for (int i = 0; i < m_cubeCount; i++) {
        this->m_cubeGrid[i] = new Cube[m_cubeCount];

        for (int j = 0; j < m_cubeCount; j++) {
            this->m_cubeGrid[i][j].AttachShader(this->m_simpleShader);
            this->m_cubeGrid[i][j].position = glm::vec3(1.1 * i, 0, 1.1 * j);
        }
    }

    /*
    Camera::Get()->MoveTo(5.5f, 20.0f, -5.0f);
    Camera::Get()->LookAt(5.5f, 0.0f, 5.5f);
    // */

    Camera::Get()->MoveTo(0.0f, 80.0f, -1.0f);
    Camera::Get()->LookAt(0.0f, 0.0f, 0.0f);

    return true;
}

void App::CleanUp() {
    delete this->m_simpleShader;
    glfwDestroyWindow(window);
    glfwTerminate();
}


bool App::Update() {
    if (glfwWindowShouldClose(this->window)) {
        return false;
    }   

    m_prevTime = m_currTime;
    m_currTime = glfwGetTime();
    float dt = m_currTime - m_prevTime;
    
    for (int i = 0; i < m_cubeCount; i++) {
        for (int j = 0; j < m_cubeCount; j++) {

            float sine = (1.5f + sinf(1.0f * glfwGetTime())) * 0.5f;

            int half = m_cubeCount / 2;

            if (i < half) {
                this->m_cubeGrid[i][j].position.x = (((i - half)) * sine * 1.5f);
            } else {
                this->m_cubeGrid[i][j].position.x = (((i - half)) * sine * 1.5f);
            }

            if (j < half) {
                this->m_cubeGrid[i][j].position.z = (((j - half)) * sine * 1.5f);
            } else {
                this->m_cubeGrid[i][j].position.z = (((j - half)) * sine * 1.5f);
            }
        }
    }

    glfwPollEvents();
    return true;
}

void App::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i = 0; i < m_cubeCount; i++) {
        for (int j = 0; j < m_cubeCount; j++) {
            this->m_cubeGrid[i][j].Render();
        }
    }

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
