#pragma once

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
// Include OGL support
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Include local files
#include "include/engine/IAPI.hpp"

// Game objects

class GameObject
{
public:
    double xPos;
    double yPos;
    double width;
    double height;

    double yBias;
    double xBias;

    bool collisionable;

    double speed;

    bool movingLeft, movingBottom, movingRight, movingTop;

    GameObject(double xPos, double yPos, double width, double height, bool collisionable, int maxHealthPoints); 
    ~GameObject();

    void update(GLFWwindow* window);
    virtual void calcBias();
    void setXYBias(double xBias, double yBias);
    void setHealthPoints(int healthPoints);
    void subHealthPoints(int subValue);
    void addHealthPoints(int addValue);
    void moveRight();
    void moveLeft();
    void moveBottom();
    void moveTop();

    std::pair<double, double> getDP(GLFWwindow* window);
protected:
    virtual void draw(GLFWwindow* window);

private:
    int maxHealthPoints;
    int healthPoints;
};

class SpikeObject : public GameObject{
public:
    SpikeObject(double xPos, double yPos, double innerR, double outerR, double lineWidth, double speed);
    
    double innerR, outerR;
    double lineWidth;
protected:
    void draw(GLFWwindow* window) override;
};

class TieFighter : public GameObject{
public:
    TieFighter(double xPos, double yPos, double radius, double width, double speed);
    double radius;
protected:
    void draw(GLFWwindow* window) override;
};

class BasicFighter : public GameObject
{
public:
    using GameObject::GameObject;
    const int maxHealthPoints = 100;
    int healthPoints = 100;
    std::vector<GameObject> parts{};
    bool borderReached{};
    void calcBias() override;
    double xNoise{}, yNoise{};
protected:
    void draw(GLFWwindow* window) override;
};

class PlayerShipShot : public GameObject
{
public:
    PlayerShipShot(double xPos, double yPos, double width, double height);
protected:
    void draw(GLFWwindow* window) override;
};



bool isCollided(GameObject *firstObject, GameObject *secondObject);
