#ifndef _APP_HPP_
#define _APP_HPP_

class App {
public:
    App(int width, int height, const char* name);
    ~App();

    bool Initialise();
    bool CleanUp();

    bool Update();

    static void KeyCallback(class GLFWwindow* window, int key, int scancode, int action, int mods);
    static void ErrorCallback(int error, const char* desc);

private:
    App() {}
    App(const App& copy) {};

    class GLFWwindow* window;

    int m_WindowWidth;
    int m_WindowHeight;
    const char* m_WindowName;
};

#endif
