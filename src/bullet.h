#ifndef BULLET_H
#define BULLET_H

#include <GL/glut.h>
#include <iostream>
#include "global.h"

using namespace std;

class Bullet {
private:
    float bulletPositionX;
    float bulletPositionY;
    float bulletVelocity;
    float bulletWidth;
    float bulletHeight;
    
public:
    // Constructor and Destructor
    Bullet(float startingPositionX, float startingPositionY, float velocity);
    ~Bullet();

    // Core functions   
    void drawBullet();
    void updateBullet();

    float getBulletPositionX() const { return bulletPositionX; }
    float getBulletPositionY() const { return bulletPositionY; }
    float getBulletWidth() const { return bulletWidth; }
    float getBulletHeight() const { return bulletHeight; }
};

#endif