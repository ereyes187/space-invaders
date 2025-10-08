// Space Invaders
#include <GL/glut.h>
#include <ctime>
#include <algorithm>
#include <array>
#include "global.h"
#include "player.h"
#include "bullet.h"

using namespace std; 

Player player;

// Helper function to draw text on the screen
void drawText(const char* text, int x, int y) {
    glRasterPos2i(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        ++text;
    }
}

void drawStartScreen() {
    glColor3f(1.0f, 1.0f, 1.0f);
    drawText("Space Invaders", (SCREEN_WIDTH / 2.0f) - 65.0f, 400);
    drawText("Press 'Enter' to start", (SCREEN_WIDTH / 2.0f) - 85.0f, 350);
}

void drawEndScreen() {
    glColor3f(1.0f, 1.0f, 1.0f);
    drawText("Game Over", (SCREEN_WIDTH / 2.0f) - 55.0f, 400);
    drawText("Press 'Enter' to start", (SCREEN_WIDTH / 2.0f) - 85.0f, 350);
}

void keyboard(unsigned char key, int x, int y) {
    if (player.getPlayerState() == START_SCREEN || player.getPlayerState() == END_SCREEN) {
        if (key == 13) { // ASCII value for 'Enter'
            player.setPlayerState(PLAYING);
            glutPostRedisplay();
        }
    } else if (player.getPlayerState() == PLAYING) {
        // When game state is set to "PLAYING", register key presses
        player.onKeyDown(key);
        glutPostRedisplay();
    }
}

void keyboardUp(unsigned char key, int x, int y) {
    if (player.getPlayerState() == PLAYING) {
        // When game state is set to "PLAYING", register key releases
        player.onKeyUp(key);
    }
}

void display() { 
    // Handle transitions between start of game, playing the game, and game end
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
        
    GameState state_ = player.getPlayerState();
    player.drawScoreboard();

    if (state_ == START_SCREEN) {
        drawStartScreen();
    } else if (state_ == PLAYING) {
        // When game state is "PLAYING", draw the player and any bullets that are shot by the player
        player.drawPlayer();

        for (Bullet* bullet : player.getBullets()) {
            bullet->drawBullet();
        }

    } else if (state_ == END_SCREEN){
        drawEndScreen();
    }
    glutSwapBuffers();
}

void update(int value) {
    if (player.getPlayerState() == PLAYING) {
        // Poll input state and move the player/shoot every frame
        player.updatePlayer(); 
    }

    for (Bullet* bullet : player.getBullets()) {
        bullet->updateBullet();
    }

    // NEW: Remove off-screen bullets and free memory
    player.getBullets().erase(
        std::remove_if(
            player.getBullets().begin(), 
            player.getBullets().end(), 
            [](Bullet* b) {
                if (b->getBulletPositionY() > SCREEN_HEIGHT - 50.0f) {
                    delete b; // Free memory
                    return true; // Remove from vector
                }
                return false;
            }
        ), 
        player.getBullets().end()
    );    
    // 2. Update all enemies (move them down/across)
    // 3. Check for collisions (bullet vs. alien, alien vs. player, etc.)

    glutPostRedisplay(); // Request a redraw after all logic updates
    glutTimerFunc(16, update, 0); // Call update again in ~16ms (~60 FPS)
}

int main( int argc, char** argv ) {
    glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
    glutCreateWindow( "Space Invaders" );

    glutDisplayFunc( display );
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 1);
    glMatrixMode(GL_MODELVIEW);
	glutKeyboardFunc(keyboard); // Register when keys are pressed
    glutKeyboardUpFunc(keyboardUp); // Register when keys are released
	glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}