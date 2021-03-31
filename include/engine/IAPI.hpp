#pragma once
#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <random>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "include/game/game.hpp"

// Draw functions
void drawPoint(double x, double y, int size, int r, int g, int b);
void drawLine(double x1, double y1, double x2, double y2, int width, int r, int g, int b);
void drawTriangle(double x1, double y1, double x2, double y2, double x3, double y3, int r, int g, int b);
void drawTriangle(double x1, double y1, double x2, double y2, double x3, double y3, GLubyte *CA);
void drawRectangle(double x1, double y1, double x2, double y2, int r, int g, int b);
void drawRectangle(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, int r, int g, int b);
void drawRectangleS(double x, double y, double width, double height, int r, int g, int b);
void drawQuad(double x, double y, double length, int r, int g, int b);
void drawFilledEllipse(double x, double y, double xRadius, double yRadius, int precision, int r, int g, int b);
void drawFilledEllipse(double x, double y, double xRadius, double yRadius, int precision, GLubyte *CA);
void drawFilledCircle(double x, double y, double radius, int precision, int r, int g, int b);
void drawFilledCircle(double x, double y, double radius, int precision, int r1, int g1, int b1, int r2, int g2, int b2);
void drawFilledHalfCircleUpper(double x, double y, double radius, int precision, int r, int g, int b);
void drawFilledHalfCircleLower(double x, double y, double radius, int precision, int r, int g, int b);
void drawCircle(double x, double y, double radius, int precision, int r, int g, int b);
void drawHalfCircleUpper(double x, double y, double radius, int r, int g, int b);
void drawHalfCircleLower(double x, double y, double radius, int r, int g, int b);
void drawSpike(double x, double y, double radius, int count, int r, int g, int b);

// Utility functions
double getRandom(const double lower_limit, const double upper_limit);
int getRandom(const int lower_limit, const int upper_limit);
