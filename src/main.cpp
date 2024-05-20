#include "RenderHandler.hpp"
#include "Window.hpp"  

int main(int argc, char const *argv[])
{
    Window window;
    window.mainLoop();
    std::cout << "Main ended" << std::endl;
    return 0;
}