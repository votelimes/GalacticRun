#include "include/engine/Window.hpp"

Window::Window(int width, int height, std::string title)
       : width(width), height(height)
{   
    this->context = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    
    if (context){
        std::cout << "WINDOW CREATION STATUS... [OK]\n";
    }
    else{
        throw std::runtime_error("ERROR: Failed to open GLFW window");
    }
    
}
Window::~Window()
{
    glfwTerminate();
}

GLFWwindow* Window::getContext(){
    return this->context;
}

int Window::getWidth() const
{
    return this->width;
}
int Window::getHeight() const
{
    return this->height;
}

void Window::setWidth(int width){
    this->width = width;
}
void Window::setHeight(int height){
    this->height = height;
}


bool Window::should_close()
{
    return glfwWindowShouldClose(this->context);
}
void Window::swap_buffers()
{
    glfwSwapBuffers(this->context);
}

void Window::set_current()
{
    glfwMakeContextCurrent(this->context);
}

void Window::show(){
    glfwShowWindow(this->context);
}
void Window::hide(){
    glfwHideWindow(this->context);
}