
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include <iostream>

#include "App.hpp"

App::App(int width, int height, const char* name)
    : m_WindowWidth(width)
    , m_WindowHeight(height)
    , m_WindowName(name) {
}

App::~App() {

}

bool App::Initialise() {
    if (!glfwInit()) {
        return false;
    }

    this->window = glfwCreateWindow(
        this->m_WindowWidth,
        this->m_WindowHeight,
        this->m_WindowName,
        glfwGetPrimaryMonitor(),
        NULL
    );

    if (!this->window) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(this->window);
    glfwSwapInterval(1);

    glfwSetKeyCallback(this->window, App::KeyCallback);
    glfwSetErrorCallback(App::ErrorCallback);
}

bool App::CleanUp() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void draw_matrix(float size) {
        glLoadIdentity();
        glBegin(GL_LINES);

        // draw line for x axis
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(size, 0.0, 0.0);

        // draw line for y axis
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, size, 0.0);

        // draw line for Z axis
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, size);

        glEnd();
}

bool App::Update() {
    while (!glfwWindowShouldClose(this->window)) {
        float ratio;
        int width, height;

        // get aspect ratio
        glfwGetFramebufferSize(this->window, &width, &height);
        ratio = width / (float) height;

        // create the view port and clear it
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        // set up the view port
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);

        // reset the glmatrix
        glLoadIdentity();
        glRotatef((float) glfwGetTime() * 50.f, 1.f, 0.f, 1.f);

        glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3f(-0.6f, -0.4f, 0.0f);
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex3f(0.6f, -0.4f, 0.0f);
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.6f, 0.0f);
        glEnd();

        draw_matrix(0.5f);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void App::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void App::ErrorCallback(int error, const char* desc) {
    std::cerr << "error occured (" << error << "): " << desc << std::endl;
}
