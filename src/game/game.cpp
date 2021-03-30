#include "include/game/game.hpp"


GameObject::GameObject(double xPos, double yPos, double width, double height, bool collisionable, int maxHealthPoints)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->width = width;
    this->height = height;
    this->collisionable = collisionable;
    this->maxHealthPoints = maxHealthPoints;
    this->healthPoints = maxHealthPoints;
    this->speed = 0.0;
    this->xBias = 0.0;
    this->yBias = 0.0;
    this->movingLeft = false;
    this->movingBottom = false;
    this->movingRight = false;
    this->movingTop = false;
}

GameObject::~GameObject(){}

// Needs to be 
void GameObject::draw(GLFWwindow* window){

}

std::pair<double, double> GameObject::getDP(GLFWwindow* window){
    int windowWidth{}, windowHeight{};
    
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    return std::pair<double, double>(2.0 / (double) windowWidth, 2.0 / (double) windowHeight);
}

void GameObject::update(GLFWwindow* window){
    this->draw(window);
}

void GameObject::calcBias(){
    if(movingLeft){
        xBias -= speed;
    }
    else if(movingRight){
        xBias += speed;
    }

    if(movingTop){
        yBias += speed;
    }
    else if(movingBottom){
        yBias -= speed;
    }
}

void GameObject::setXYBias(double xBias, double yBias){
    this->xBias = xBias;
    this->yBias = yBias;
}

void GameObject::setHealthPoints(int healthPoints){
        this->healthPoints = healthPoints;
        }

void GameObject::subHealthPoints(int subValue){
    this->healthPoints-=subValue;
}

void GameObject::addHealthPoints(int addValue){
    this->healthPoints+=addValue;
}

void GameObject::moveRight(){
        //this->xBias += this->speed;
        this->movingRight = true;
    }

void GameObject::moveLeft(){
    //this->xBias -= this->speed;
    this->movingLeft = true;
}

void GameObject::moveBottom(){
    this->movingBottom = true;
}

void GameObject::moveTop(){
    this->movingTop = true;
}

SpikeObject::SpikeObject(double xPos, double yPos, double innerR, double outerR, double lineWidth, double speed)
: GameObject(xPos, yPos, innerR, innerR, true, 100)
{
    calcBias();

    this->innerR = innerR;
    this->outerR = outerR;
    this->lineWidth = lineWidth;
    this->movingBottom = true;
    this->speed = speed;
}

void SpikeObject::draw(GLFWwindow* window) {
    
    calcBias();

    glLineWidth(lineWidth);
    
    drawSpike(xPos + xBias, yPos + yBias, outerR, 12, 255, 255, 255);
    drawFilledCircle(xPos + xBias, yPos + yBias, innerR, 40, 255, 255, 255);

}

TieFighter::TieFighter(double xPos, double yPos, double radius, double width, double speed)
: GameObject(xPos, yPos, radius, radius, true, 100)
{
    calcBias();

    this->radius = radius;
    this->movingBottom = true;
    this->speed = speed;
}

void TieFighter::draw(GLFWwindow* window) {

    calcBias();

    drawTriangle(xPos + xBias, yPos + yBias + radius, xPos + xBias - radius/2 - 0.04, yPos + yBias, 
    xPos + xBias, yPos + yBias - radius, 140, 140, 140);
    drawTriangle(xPos + xBias, yPos + yBias + radius, xPos + xBias, yPos + yBias - radius, 
    xPos + xBias + radius/2 + 0.04, yPos + yBias, 140, 140, 140);

    drawRectangleS(xPos - 0.04 - radius/2 + xBias, yPos - 0.008 + yBias, 0.04 * 2 + radius, 0.008 * 2, 140, 140, 140);
    drawFilledCircle(xPos + xBias, yPos + yBias, radius, 90, 255, 255, 255);
    drawRectangleS(xPos - radius/2 + xBias - 0.04, yPos + yBias - 0.05, 0.008, 0.10, 51, 51, 51);
    drawRectangleS(xPos + radius/2 + xBias + 0.04 - 0.008, yPos + yBias - 0.05, 0.008, 0.10, 51, 51, 51);

    drawRectangleS(xPos + xBias - 0.004, yPos + yBias - radius + 0.002, 0.004 * 2, (radius - 0.002) * 2, 45, 45, 45);
    drawRectangleS(xPos + xBias - 0.014, yPos + yBias - radius + 0.009, 0.003 * 2, (radius - 0.009) * 2, 0, 102, 255);
    drawRectangleS(xPos + xBias + 0.008, yPos + yBias - radius + 0.009, 0.003 * 2 - 0.001, (radius - 0.009) * 2, 0, 102, 255);
}

void BasicFighter::calcBias(){
    if(movingLeft && xBias > -0.95){
        xBias -= speed;
        //movingLeft = false;
    }
    else if(movingRight && xBias < 0.82){
        xBias += speed;
        //movingRight = false;
    }

    if(movingTop && yBias < 0.8){
        yBias += speed;
        //movingTop = false;
    }
    else if(movingBottom && yBias > -0.95){
        yBias -= speed;
        //movingBottom = false;
    }

    movingLeft = false;
    movingRight = false;
    movingTop = false;
    movingBottom = false;
}

void BasicFighter::draw(GLFWwindow* window) {  
     
    calcBias();
    static double bodyTriangle1 = 0.05;
    static double bodyCircleRadius1 = 0.02;
    static double bodyCircleRadius2 = 0.01;
    static double bodyRectangleGunX1 = 0.01;
    static double bodyRectangleGunY1 = 0.07;

    static double bodyRectangleGunX2 = 0.004;
    static double bodyRectangleGunY2 = 0.014;

    static double bodyRectangleWindowX1 = 0.006;
    static double bodyRectangleWindowY1 = 0.040;
    static double bodyRectangleWindowX2 = 0.002;
    static double bodyRectangleWindowY2 = 0.022;

    
    drawTriangle(xPos - bodyTriangle1, yPos, xPos, yPos, xPos, yPos + bodyTriangle1, 255, 255, 200);
    drawTriangle(xPos, yPos + bodyTriangle1, xPos, yPos, xPos + bodyTriangle1, yPos, 255, 255, 200);
    drawFilledCircle(xPos, yPos, bodyCircleRadius1, 90, 255, 255, 255);
    drawFilledCircle(xPos, yPos, bodyCircleRadius2, 90, 255, 255, 255);
    // Main gun 1st part
    drawRectangle(xPos - bodyRectangleGunX1, yPos + bodyRectangleGunY1, xPos, yPos, 240, 200, 200);
    drawRectangle(xPos, yPos + bodyRectangleGunY1, xPos + bodyRectangleGunX1, yPos, 240, 200, 200);
    // Main gun 2nd part
    drawRectangle(xPos - bodyRectangleGunX1, yPos + bodyRectangleGunY1 + bodyRectangleGunY2, xPos - bodyRectangleGunX1 + 
    bodyRectangleGunX2, yPos + bodyRectangleGunY1, 255, 15, 15);
    drawRectangle(xPos + bodyRectangleGunX1 - bodyRectangleGunX2, yPos + bodyRectangleGunY1 + bodyRectangleGunY2, 
    xPos + bodyRectangleGunX1, yPos + bodyRectangleGunY1, 255, 15, 15);
    // Windows
    drawRectangle(xPos - bodyRectangleWindowX1, yPos + bodyRectangleWindowY1, 
    xPos - bodyRectangleWindowX2, yPos + bodyRectangleWindowY2, 0, 0, 255);
    drawRectangle(xPos + bodyRectangleWindowX2, yPos + bodyRectangleWindowY1, 
    xPos + bodyRectangleWindowX1, yPos + bodyRectangleWindowY2, 0, 0, 200);

    return;
    // Body
    drawRectangleS(0.0 + xBias, 0.0 + yBias, 0.12, 0.02, 102, 102, 153);
    drawRectangleS(0.0 + xBias, 0.015 + yBias, 0.015, 0.08, 102, 102, 153);
    drawRectangleS(0.105 + xBias, 0.015 + yBias, 0.015, 0.08, 102, 102, 153);

    // Main gun
    drawRectangleS(0.04 + xBias, 0.015 + yBias, 0.04, 0.015, 0, 150, 255);
    drawRectangleS(0.045 + xBias, 0.025 + yBias, 0.030, 0.015, 100, 150, 255);
    drawRectangleS(0.050 + xBias, 0.035 + yBias, 0.020, 0.04, 0, 255, 255);
    
    drawRectangleS(0.050 + xBias, 0.075 + yBias, 0.004, 0.02, 255, 0, 0);
    drawRectangleS(0.066 + xBias, 0.075 + yBias, 0.004, 0.02, 255, 0, 0);

    // Lower wings
    drawTriangle(0.0 + xBias, 0.0 + yBias, 0.0 + xBias, 0.04 + yBias, -0.03 + xBias, 0.0 + yBias, 139, 139, 152);
    drawTriangle(0.12 + xBias, 0.0 + yBias, 0.12 + xBias, 0.04 + yBias, 0.15 + xBias, 0.0 + yBias, 139, 139, 152);

    // Upper wings
    drawTriangle(0.0 + xBias, 0.095 + yBias, 0.0 + xBias, 0.06 + yBias, -0.08 + xBias, 0.00 + yBias, 0, 102, 102);
    drawTriangle(0.12 + xBias, 0.095 + yBias, 0.12 + xBias, 0.06 + yBias, 0.20 + xBias, 0.0 + yBias, 0, 102, 102);

    // Engines
    drawFilledHalfCircleLower(0.03 + xBias, 0.0 + yBias, 0.018, 40, 252, 57, 3);
    drawFilledHalfCircleLower(0.09 + xBias, 0.0 + yBias, 0.018, 40, 252, 57, 3);
    drawFilledHalfCircleLower(0.03 + xBias, 0.0 + yBias, 0.01, 40, 252, 153, 3);
    drawFilledHalfCircleLower(0.09 + xBias, 0.0 + yBias, 0.01, 40, 252, 153, 3);
}

PlayerShipShot::PlayerShipShot(double xPos, double yPos, double width, double height)
: GameObject(xPos, yPos, width, height, true, 100)
{
    calcBias();

    this->movingTop = true;
    this->speed = 0.01;
}

void PlayerShipShot::draw(GLFWwindow* window){
    calcBias();
    
    drawFilledEllipse(xPos + xBias + 0.004, yPos + yBias, 0.006, 0.017, 6, 255, 51, 0);
}

bool isCollided(GameObject *firstObject, GameObject *secondObject){

    // collision x-axis?
    bool collisionX = firstObject->xPos + firstObject->xBias + firstObject->width >= secondObject->xPos + secondObject->xBias &&
        secondObject->xPos + secondObject->xBias + secondObject->width >= firstObject->xPos + firstObject->xBias;
    // collision y-axis?
    bool collisionY = firstObject->yPos + firstObject->yBias + firstObject->height >= secondObject->yPos + secondObject->yBias &&
        secondObject->yPos + secondObject->yBias + secondObject->height >= firstObject->yPos + firstObject->yBias;
    // collision only if on both axes
    return collisionX && collisionY;
}