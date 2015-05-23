
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
#include "shaderprogram.h"
#include "cube.h"

#include "centermatrix.h"

#include "texture.h"

App::App(int width, int height, const char* name)
 : m_WindowWidth(width)
 , m_WindowHeight(height)
 , m_WindowName(name)
 , m_cubeCount(22)
 , m_prevTime(0) 
 , m_currTime(0)
 , m_mxPrev(0)
 , m_myPrev(0)
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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // setup OpenGL specific configuration
    std::cerr << "Using " << glGetString(GL_VERSION) << std::endl;
    // TODO work out what `glewExperimental = true;` does
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialise GLEW." << std::endl;
        return false;
    }
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glDepthFunc(GL_LESS);
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    //glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );

    // create our shaders
    
    ShaderProgram::Builder shaderProgramBuilder;
    shaderProgramBuilder.buildShader("shaders/shader.vert", GL_VERTEX_SHADER);
    shaderProgramBuilder.buildShader("shaders/shader.frag", GL_FRAGMENT_SHADER);
    m_simpleShader = shaderProgramBuilder.getResult();

    if (m_simpleShader == nullptr) {
        std::cerr << "Shaders could not be loaded." << std::endl;
        return false;
    }

    int width = 0;
    int height = 0;
    glfwGetFramebufferSize(this->window, &width, &height);

    Camera::Get().SetProjectionMatrix(
        45.0f, 
        width / (float)height, 
        0.1f, 
        1000.f
    );

    this->m_cubeGrid = new Cube**[m_cubeCount];

    for (int i = 0; i < m_cubeCount; i++) {
        this->m_cubeGrid[i] = new Cube*[m_cubeCount];

        for (int j = 0; j < m_cubeCount; j++) {
            this->m_cubeGrid[i][j] = new Cube[m_cubeCount];

            for (int k = 0; k < m_cubeCount; k++) {
                this->m_cubeGrid[i][j][k].AttachShader(this->m_simpleShader);
                this->m_cubeGrid[i][j][k].position = glm::vec3(1.1 * i, 1.1 * k, 1.1 * j);
            }
        }
    }


     /* distant
    Camera::Get().MoveTo(200.0f, 400.0f, -1.0f);
    Camera::Get().LookAt(0.0f, 100.0f, 0.0f);
    // */

    /* in the midst
    Camera::Get().MoveTo(000.0f, 90.0f, -1.0f);
    Camera::Get().LookAt(0.0f, 100.0f, 0.0f);
    // */
    
    ///* square
    Camera::Get().MoveTo(0.0f, 0.0f, 0.0f);
    Camera::Get().LookAt(0.0f, 0.0f, 1.0f);
    // */
    
    Camera::Get().SetWindow(window);

    double mx, my;
    glfwGetCursorPos(window, &mx, &my);
    m_myPrev = my;
    m_mxPrev = mx;

    ShaderProgram::Builder shaderColorBuilder;
    shaderColorBuilder.buildShader("shaders/color.vert", GL_VERTEX_SHADER);
    shaderColorBuilder.buildShader("shaders/color.frag", GL_FRAGMENT_SHADER);
    ShaderProgram* colorShader= shaderColorBuilder.getResult();

    m_matrix = new CenterMatrix(2.0f);
    m_matrix->AttachShader(colorShader);
    m_matrix->position = glm::vec3(0.0f, 0.0f, 0.0f);


    return true;
}

void App::CleanUp() {
    delete m_matrix;

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

    double mx, my;
    glfwGetCursorPos(window, &mx, &my);

    double mxDelta = mx - m_mxPrev;
    double myDelta = my - m_myPrev;

    m_mxPrev = mx;
    m_myPrev = my;

    Camera::Get().Update(dt, mxDelta, myDelta);

    ///* Yeah... ugly... I know...
    float speed = 0.1f;
    float sep = 4.5f + sinf(glfwGetTime()) * 1.5f;

    float sine = (16.0f + sinf(speed * glfwGetTime()) * 5.0f) * 0.5f;

    for (int i = 0; i < m_cubeCount; i++) {
        for (int j = 0; j < m_cubeCount; j++) {
            for (int k = 0; k < m_cubeCount; k++) {
                float scale_size = sine * 0.8f;
                this->m_cubeGrid[i][j][k].scale.x = scale_size;
                this->m_cubeGrid[i][j][k].scale.y = scale_size;
                this->m_cubeGrid[i][j][k].scale.z = scale_size;

                int half = m_cubeCount / 2;
                if (i < half) {
                    this->m_cubeGrid[i][j][k].position.x = (((i - half)) * sine * sep);
                } else {
                    this->m_cubeGrid[i][j][k].position.x = (((i - half)) * sine * sep);
                }

                if (j < half) {
                    this->m_cubeGrid[i][j][k].position.z = (((j - half)) * sine * sep);
                } else {
                    this->m_cubeGrid[i][j][k].position.z = (((j - half)) * sine * sep);
                }

                this->m_cubeGrid[i][j][k].position.y = (k * sine * sep);

                this->m_cubeGrid[i][j][k].eulerAngles.y = (sine * 1.5f);
                this->m_cubeGrid[i][j][k].eulerAngles.x = (sine * 1.5f);
            }
        }
    }
    // */

    glfwPollEvents();
    return true;
}

void App::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //m_matrix->Render();

    for (int i = 0; i < m_cubeCount; i++) {
        for (int j = 0; j < m_cubeCount; j++) {
            for (int k = 0; k < m_cubeCount; k++) {

                int x = m_cubeCount / 2;

                //if (i == x && j == x && k == 0) continue;

                this->m_cubeGrid[i][j][k].Render();
            }
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
