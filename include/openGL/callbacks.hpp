#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Include local files
#include "include/engine/Window.hpp"
#include "include/game/game.hpp"
#include "include/shared.hpp"
#include "include/main.hpp"

void keyCallback (GLFWwindow* window, int key, int scanCode, int action, int mods);
void mouseCallback (GLFWwindow* window, int button, int action, int mods);
void resizeCallback (GLFWwindow* window, int width, int height);

// Globals

//extern BasicFighter *playerShip;