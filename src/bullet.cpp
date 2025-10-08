#include "bullet.h"
#include "global.h"

Bullet::Bullet(float startingPositionX, float startingPositionY, float velocity) {
    bulletPositionX = startingPositionX;
    bulletPositionY = startingPositionY;
    bulletVelocity = velocity;
    bulletWidth = 2.0f;
    bulletHeight = 4.0f;
}

void Bullet::drawBullet() {
    // Set the bullet color to white
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);
    glVertex2f(bulletPositionX, bulletPositionY);
    glVertex2f(bulletPositionX, bulletPositionY + bulletHeight);
    glVertex2f(bulletPositionX + bulletWidth, bulletPositionY + bulletHeight);
    glVertex2f(bulletPositionX + bulletWidth, bulletPositionY);
    glEnd();
}

void Bullet::updateBullet() {
    // Place bullet in motion with set velocity
    bulletPositionY += bulletVelocity;
}

Bullet::~Bullet() {

}
