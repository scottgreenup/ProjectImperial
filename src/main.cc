
#include "App.h"

int main(void) {

    App kApp(1920, 1080, "Hello World");
    if (!kApp.Initialise()) {
        return 1;
    }

    while (kApp.Update()) {
        kApp.Render();
    }

    kApp.CleanUp();

    return 0;
}

