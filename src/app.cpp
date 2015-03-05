
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-4-a-colored-cube/

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "app.hpp"
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
    std::cerr << "Using " << glGetString(GL_VERSION) << std::endl;

    //glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialise GLEW." << std::endl;
        return false;
    }

    glClearColor(0.1, 0.1, 0.1, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glfwSwapInterval(1);
    glfwSetKeyCallback(this->window, App::KeyCallback);
    glfwSetErrorCallback(App::ErrorCallback);

    this->m_pkTriangle = new Triangle();
    this->m_cube = new Cube();

    this->m_uiProgramId = LoadShaders(
        "shaders/shader.vert",
        "shaders/shader.frag"
    );

    return true;
}

void App::CleanUp() {
    glDeleteProgram(this->m_uiProgramId);

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

//void draw_triangle(float x, float y, float z, float size) {
//
//    float a = 0.5f * sqrtf(size * size * 2.0f);
//    float b = sqrtf(size * size - a * a);
//
//    glLoadIdentity();
//    glBegin(GL_TRIANGLES);
//    glColor3f(0.0f, 1.0f, 1.0f);
//    glVertex3f(x - a, y - b, z);
//    glColor3f(1.0f, 0.0f, 1.0f);
//    glVertex3f(x + a, y - b, z);
//    glColor3f(1.0f, 1.0f, 0.0f);
//    glVertex3f(    x, y + b, z);
//    glEnd();
//}

void App::Render() {

    int width, height;
    glfwGetFramebufferSize(this->window, &width, &height);
    float ratio = width / (float) height;


    float x = 5 * sinf(glfwGetTime() * 3.0f);

    glm::mat4 projection = glm::perspective(45.0f, ratio, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(
        glm::vec3(x,5,-5), // pos
        glm::vec3(0,0,0), // look at
        glm::vec3(0,1,0)  // up
    );

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 mvp = projection * view * model;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(this->m_uiProgramId);

    GLuint matrixId = glGetUniformLocation(this->m_uiProgramId, "MVP");
    glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp[0][0]);

    this->m_pkTriangle->Render();
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

GLuint App::LoadShaders(const char* vertFilename, const char* fragFilename) {
    GLuint vertId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragId = glCreateShader(GL_FRAGMENT_SHADER);

    // get .vert code
    std::string vertCode;
    std::ifstream vertStream(vertFilename, std::ios::in);
    if (!vertStream.is_open()) {
        std::cerr << "Could not open " << vertFilename << "." << std::endl;
        return 0;
    }
    std::string line = "";
    while (getline(vertStream, line)) {
        vertCode += "\n" + line;
    }
    vertStream.close();

    // get .frag code
    std::string fragCode;
    std::ifstream fragStream(fragFilename, std::ios::in);
    if (!fragStream.is_open()) {
        std::cerr << "Could not open " << fragFilename << "." << std::endl;
        return 0;
    }
    line = "";
    while (getline(fragStream, line)) {
        fragCode += "\n" + line;
    }
    fragStream.close();

    GLint result = GL_FALSE;
    int infoLogLength;

    // compile .vert
    char const* vertSource = vertCode.c_str();
    glShaderSource(vertId, 1, &vertSource, NULL);
    glCompileShader(vertId);

    // check .vert
    glGetShaderiv(vertId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        std::vector<char> vertErrMessage(infoLogLength + 1);
        glGetShaderInfoLog(vertId, infoLogLength, NULL, &vertErrMessage[0]);
        std::cerr << &vertErrMessage[0] << std::endl;
    }

    // compile .frag
    char const* fragSource = fragCode.c_str();
    glShaderSource(fragId, 1, &fragSource, NULL);
    glCompileShader(fragId);

    // check .vert
    glGetShaderiv(fragId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        std::vector<char> fragErrMessage(infoLogLength + 1);
        glGetShaderInfoLog(fragId, infoLogLength, NULL, &fragErrMessage[0]);
        std::cerr << &fragErrMessage[0] << std::endl;
    }

    // link the program
    GLuint programId = glCreateProgram();
    glAttachShader(programId, vertId);
    glAttachShader(programId, fragId);
    glLinkProgram(programId);

    // check program
    glGetProgramiv(programId, GL_LINK_STATUS, &result);
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        std::vector<char> message(infoLogLength + 1);
        glGetShaderInfoLog(programId, infoLogLength, NULL, &message[0]);
        std::cerr << &message[0] << std::endl;
    }

    glDeleteShader(vertId);
    glDeleteShader(fragId);

    return programId;
}
