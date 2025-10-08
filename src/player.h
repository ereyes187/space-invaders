#ifndef PLAYER_H
#define PLAYER_H

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "global.h"
#include "bullet.h"

using namespace std;

class Player {
private:
    GameState playerState;
    int score;
    int lives;

    float playerPositionX;
    float playerPositionY;
    float playerVelocity;
    float playerHitboxWidth;
    float playerHitboxHeight;
    vector<Bullet*> bullets;
    map<unsigned char, bool> keysHeld;


public:
    // Constructor and Destructor
    Player();
    ~Player();

    // Core functions   
    void setPlayerState(GameState newState);
    void drawPlayer();      
    void drawScoreboard();
    void onKeyDown(unsigned char key);
    void onKeyUp(unsigned char key);    
    void updatePlayer();
    void shoot();

    GameState getPlayerState() const { return playerState; }
    int getScore() const { return score; }    
    int getLives() const { return lives; }
    float getPlayerPositionX() const { return playerPositionX; }
    float getPlayerPositionY() const { return playerPositionY; }
    float getHitBoxWidth() const { return playerHitboxWidth; }
    float getHitBoxHeight() const { return playerHitboxHeight; }
    vector<Bullet*>& getBullets() { return bullets; } 
};

#endif