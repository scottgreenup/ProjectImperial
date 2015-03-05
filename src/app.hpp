#ifndef _APP_HPP_
#define _APP_HPP_

#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class App {
public:
    App(int width, int height, const char* name);
    ~App();

    bool Initialise();
    bool CleanUp();

    bool Update();
    void Render();

    static void KeyCallback(class GLFWwindow* window, int key, int scancode, int action, int mods);
    static void ErrorCallback(int error, const char* desc);

    GLuint LoadShaders(const char* vertFilename, const char* fragFilename);

private:
    App() {}
    App(const App& copy) {};

    class GLFWwindow* window;

    GLuint m_uiProgramId;

    int m_WindowWidth;
    int m_WindowHeight;
    const char* m_WindowName;

    class Polygon* m_pkTriangle;
};

#endif
