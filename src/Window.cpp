#include "../include/Window.hpp"

Window::Window()
    : m_renderHandler("breakout",SCREEN_WIDTH, SCREEN_HEIGHT ), m_WindowState(WindowState::MAIN_TITLE)
{
}

Window::~Window()
{
}

void Window::mainLoop()
{   
    std::cout << "Main loop started" << std::endl;
}
