#include <GLFW/glfw3.h>

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetKeyCallback(window, key_callback);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;

        // get aspect ratio
        glfwGetFramebufferSize(window, &width, &height);
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

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}
