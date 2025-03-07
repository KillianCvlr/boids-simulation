#include "Window.hpp"  
#include "GlobalValues.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    // Display parameters
    setDefaultValues();

    std::cout << "Main started" << std::endl;
    Window window;
    window.mainLoop();
    std::cout << "Main ended" << std::endl;
    return 0;
}