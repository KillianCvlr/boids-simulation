#include "RenderHandler.hpp"
#include "Window.hpp"  

int main(int argc, char const *argv[])
{
    std::cout << "Main started" << std::endl;
    Window window;
    window.mainLoop();
    std::cout << "Main ended" << std::endl;
    return 0;
}