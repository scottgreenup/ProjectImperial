
#include "App.hpp"

#include <GLFW/glfw3.h>

int main(void)
{
    App kApp(1920, 1080, "Hello World");
    kApp.Initialise();
    kApp.Update();
    kApp.CleanUp();

    return 0;
}
