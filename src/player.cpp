#include "player.h"
#include "bullet.h"

Player::Player() {
    playerState = START_SCREEN; 
    score = 0;
    lives = 3;

    playerPositionX = SCREEN_WIDTH / 2.0f;
    playerPositionY = 50.0f;
    playerVelocity = 2.0f;
    playerHitboxWidth = 25.0f;
    playerHitboxHeight = 25.0f;
}

void Player::setPlayerState(GameState newState) {
    playerState = newState;
}

void Player::drawPlayer() {
    if (playerState != PLAYING) return;

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 1.0f, 0.0f); // Green Color Triangle for the player ship
    glVertex2f(playerPositionX, playerPositionY);
    glVertex2f(playerPositionX + playerHitboxWidth / 2.0f, playerPositionY + playerHitboxHeight);
    glVertex2f(playerPositionX + playerHitboxWidth, playerPositionY);
    glEnd();
}

void Player::drawScoreboard() {
    glColor3f(1.0f, 1.0f, 1.0f);
    string scoreStr = "Score: " + to_string(score);
    glRasterPos2f(20.0f, SCREEN_HEIGHT - 30.0f);
    for (char c : scoreStr) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    string livesStr = "Lives: " + to_string(lives);
    glRasterPos2f(SCREEN_WIDTH - 120.0f, SCREEN_HEIGHT - 30.0f); 
    for (char c : livesStr) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void Player::onKeyDown(unsigned char key) {
    keysHeld[key] = true;
}

void Player::onKeyUp(unsigned char key) {
    keysHeld[key] = false;
}

void Player::updatePlayer() {
    // Handle movement input
    if (keysHeld['a'] && !keysHeld['d']) {
        playerPositionX -= playerVelocity;
    } else if (keysHeld['d'] && !keysHeld['a']) {
        playerPositionX += playerVelocity;
    }

    // Clamping player position (boundary check)
    if (playerPositionX < 0.0f) {
        playerPositionX = 0.0f;
    }
    if (playerPositionX + playerHitboxWidth > SCREEN_WIDTH) {
        playerPositionX = SCREEN_WIDTH - playerHitboxWidth;
    }

    // Handle shooting input
    if (keysHeld[' '] && bullets.size() < 1) {
        shoot();
    }
}

void Player::shoot() {
    float startingPositionX = playerPositionX + playerHitboxWidth / 2.0f - (2.0f / 2.0f); // Center of the player ship, adjusted for bullet width (2.0f)
    float startingPositionY = playerPositionY + playerHitboxHeight;
    bullets.push_back(new Bullet(startingPositionX, startingPositionY, 6.0f));
}

Player::~Player() {
    for (Bullet* bullet : bullets) {
        delete bullet;
    }
    bullets.clear();
}
