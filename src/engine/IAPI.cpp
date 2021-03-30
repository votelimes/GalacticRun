#include "include/engine/IAPI.hpp"

// Draw functions
void drawPoint(double x, double y, int size, int r, int g, int b){
    
    glPointSize(size);
    glColor3ub(r, g, b);
    
    glBegin(GL_POINTS);
    glVertex2d(x, y);

    glEnd();
}

void drawLine(double x1, double y1, double x2, double y2, int width, int r, int g, int b){
    
    glLineWidth(width); 
    glColor3ub(r, g, b);

    glBegin(GL_POINTS);

    glVertex2d(x1, y1);
    glVertex2d(x2, y2);

    glEnd();
}

void drawTriangle(double x1, double y1, double x2, double y2, double x3, double y3, int r, int g, int b){
    
    glColor3ub(r, g, b);
    glBegin(GL_TRIANGLES);

    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glVertex2d(x3, y3);

    glEnd();

}

void drawRectangle(double x1, double y1, double x2, double y2, int r, int g, int b){
    
    glColor3ub(r, g, b);

    glBegin(GL_POLYGON);
    glVertex2d(x1, y1);
    glVertex2d(x1, y2);
    glVertex2d(x2, y2);
    glVertex2d(x2, y1);
    glEnd();
}

void drawRectangleS(double x, double y, double width, double height, int r, int g, int b){
    
    glColor3ub(r, g, b);
    
    glBegin(GL_POLYGON);
    glVertex2d(x, y + height);
    glVertex2d(x, y);
    glVertex2d(x + width, y);
    glVertex2d(x + width, y + height);
    glEnd();
}

void drawQuad(double x, double y, double length, int r, int g, int b){
    
    double x1 = x;
    double y1 = y;

    double x2 = x + length;
    double y2 = y + length;
    
    drawRectangle(x1, y1, x2, y2, r, g, b);
}

void drawFilledEllipse(double x, double y, double xRadius, double yRadius, int precision, int r, int g, int b){
	glColor3ub(r, g, b);
	
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(x, y);
    for(auto i = 0; i <= precision;i++) {
        glVertex2d(
                x + (xRadius * cos(i *  2.0 * M_PI / precision)), 
            y + (yRadius * sin(i * 2.0 * M_PI / precision))
        );
    }
	glEnd();
}

void drawFilledCircle(double x, double y, double radius, int precision, int r, int g, int b){
	
    glColor3ub(r, g, b);
	
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(x, y); // center of circle
    for(auto i = 0; i <= precision;i++) { 
        glVertex2d(
                x + (radius * cos(i *  2.0 * M_PI / precision)), 
            y + (radius * sin(i * 2.0 * M_PI / precision))
        );
    }
	glEnd();
}

void drawFilledHalfCircleUpper(double x, double y, double radius, int precision, int r, int g, int b){	
	
    glColor3ub(r, g, b);
	
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(x, y); // center of circle
    for(auto i = 0; i <= precision;i++) { 
        glVertex2d(
                x + (radius * cos(i *  M_PI / precision)), 
            y + (radius * sin(i * M_PI / precision))
        );
    }
	glEnd();
}

void drawFilledHalfCircleLower(double x, double y, double radius, int precision, int r, int g, int b){

	glColor3ub(r, g, b);
	
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(x, y); // center of circle
    for(auto i = 0; i <= precision;i++) { 
        glVertex2d(
                x + (radius * cos(i *  M_PI / precision)), 
            y + (radius * sin((i * M_PI / precision) + M_PI))
        );
    }
	glEnd();
}

void drawCircle(double x, double y, double radius, int precision, int r, int g, int b){

    double sides = precision == 0 ? 60 : precision;
    glColor3ub(r, g, b);
    glBegin(GL_LINE_LOOP);

    for (int a = 0; a < 360; a += 360 / sides)
    {
        double heading = a * M_PI / 180;
        glVertex2d((cos(heading) * radius) + x, (sin(heading) * radius) + y);
    }

    glEnd();

}

void drawHalfCircleUpper(double x, double y, double radius, int r, int g, int b) { 
        
        glColor3ub(r, g, b);
        glBegin(GL_LINE_STRIP);
        
        //glVertex2d(x, y); // Center
        
        for(size_t i = 0; i <= 180; i++){
            glVertex2d(radius*cos(M_PI * i / 180.0) + x, radius*sin(M_PI * i / 180.0) + y);
        }
        
        glEnd();
}

void drawHalfCircleLower(double x, double y, double radius, int r, int g, int b) {
        double i = 180.0;

        glColor3ub(r, g, b);
        glBegin(GL_LINE_STRIP);
        
        //glVertex2d(x, y); // Center
        
        for(i = 180.0; i <= 360; i++){
            glVertex2d(radius*cos(M_PI * i / 180.0) + x, radius*sin(M_PI * i / 180.0) + y);
        }
        
        glEnd();
}

void drawSpike(double x, double y, double radius, int count, int r, int g, int b){
    double sides = count == 0 ? 12 : count;

    glColor3ub(r, g, b);
    glBegin(GL_LINES);

    for (int a = 0; a < 360; a += 360 / sides)
    {
        double heading = a * M_PI / 180;
        glVertex2d(x, y);
        glVertex2d((cos(heading) * radius) + x, (sin(heading) * radius) + y);
    }

    glEnd();
} 

// Physical functions
bool CheckCollision(GameObject &one, GameObject &two) // AABB - AABB collision
{
    // collision x-axis?
    bool collisionX = one.xPos + one.width >= two.xPos &&
        two.xPos + two.width >= one.xPos;
    // collision y-axis?
    bool collisionY = one.yPos + one.height >= two.yPos &&
        two.yPos + two.height >= one.yPos;
    // collision only if on both axes
    return collisionX && collisionY;
}


double getRandom(const double lower_limit, const double upper_limit)
{
    
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::uniform_real_distribution<double> uid(lower_limit, upper_limit);
    
    double rv;
    rv = uid(gen);
    return rv;
}
int getRandom(const int lower_limit, const int upper_limit)
{
    
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::uniform_int_distribution<int> uid(lower_limit, upper_limit);
    
    int rv;
    rv = uid(gen);
    return rv;
}
