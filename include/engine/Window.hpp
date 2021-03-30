#pragma once


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
    public:

        Window(int, int, std::string);
        ~Window();

        GLFWwindow* getContext();

        int getWidth() const;
        int getHeight() const;

        void setWidth(int width);
        void setHeight(int height);

        bool should_close();
        void swap_buffers();

        void set_current();
        
        void show();
        void hide();

    private:

        GLFWwindow* context;
        int width{1024};
        int height{768};
        
};