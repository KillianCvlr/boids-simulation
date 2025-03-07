#include "Window.hpp"  
#include "DefaultValues.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    // Display parameters
    

    std::cout << "Main started" << std::endl;
    Window window;
    window.mainLoop();
    std::cout << "Main ended" << std::endl;
    return 0;
}