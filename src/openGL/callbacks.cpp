#include "include/openGL/callbacks.hpp"



void keyCallback (GLFWwindow* window, int key, int scanCode, int action, int mods){
    if(action == GLFW_PRESS || action == GLFW_REPEAT){
        if(key == GLFW_KEY_ESCAPE){
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        else if(key == GLFW_KEY_RIGHT){
            playerShip->moveRight();
        }
        else if(key == GLFW_KEY_LEFT){
            playerShip->moveLeft();
        }
        else if(key == GLFW_KEY_UP){
            playerShip->moveTop();
        }
        else if(key == GLFW_KEY_DOWN){
            playerShip->moveBottom();
        }
        else if(key == GLFW_KEY_SPACE){
            playerShipShots->push_back(new PlayerShipShot(playerShip->xPos - 0.004, playerShip->yPos + 0.086, 0.01, 0.02));
        }
        else if(key == GLFW_KEY_S){
            if(stopAnim){
                stopAnim = false;
            }
            else{
                stopAnim = true;
            }
        }
    }
}
void mouseCallback (GLFWwindow* window, int button, int action, int mods){
    if(action == GLFW_PRESS){
        switch(button){
            case GLFW_MOUSE_BUTTON_LEFT:
            {
                static long int outputNumber{};
                double xPos{}, yPos{};
                glfwGetCursorPos(window, &xPos, &yPos);

                std::cout << "----------" << std::endl;
                std::string output = "Pixels #" + std::to_string(outputNumber) + ":";
                std::cout << output << std::endl;
                std::cout << xPos << ", " << yPos << std::endl;

                int windowWidth{}, windowHeight{};
                glfwGetWindowSize(window, &windowWidth, &windowHeight);

                output = "Window size #" + std::to_string(outputNumber) + ":";
                std::cout << output << std::endl;
                std::cout << windowWidth << ", " << windowHeight << std::endl;

                // double glXPos = (2.0 / (double) windowWidth) * xPos - 1; // Right top corner is +1;+1
                // double glYPos = (((2.0 / (double) windowHeight) * yPos - 1) * -1) - (2.0 / (double) windowHeight);
                
                double glXPos = 2.0 * (xPos + 0.5) / windowWidth - 1.0;
                double glYPos = (2.0 * (yPos + 0.5) / windowHeight - 1.0) * -1;
                
                
                std::cout.precision(4);
                output = "OpenGL coordinates #" + std::to_string(outputNumber) + ":";
                std::cout << output << std::endl;
                std::cout << std::fixed << glXPos << ", " << std::fixed << glYPos << std::endl;
                std::cout << "----------" << std::endl;
                break;
            }
            default:{
                
            }
        }
    }
}
void resizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}