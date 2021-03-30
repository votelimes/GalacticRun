#pragma once

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


namespace GLSL
{
    enum class ShaderType
    {
        VERTEX = GL_VERTEX_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER,
        GEOMETRY = GL_GEOMETRY_SHADER
    };

    class Shader
    {
        public:
            Shader(std::string, ShaderType);
            std::string get_code() const;
            GLuint get_handler() const;
            bool compile();
        private:
            GLuint handler;
            std::string shader_code;
    };

    class Program
    {
        public:
            Program();
            void add_shader(const Shader&);
            bool link();
            void use();
        private:
            GLuint handler;
    };

    GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
};