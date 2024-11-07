#include <graphics.h>
#include <conio.h>
#include <cmath>
#include <dos.h>

void drawLimb(int x, int y, int length, float angle) {
    int endX = x + length * cos(angle);
    int endY = y + length * sin(angle);
    line(x, y, endX, endY);
}

void drawRunningMan(int baseX, int baseY, float angle, bool isJumping) {
    int jumpOffset = isJumping ? -30 : 0;  // Offset for jumping
    
    // Draw Head
    circle(baseX, baseY - 40 + jumpOffset, 10);

    // Draw Body
    line(baseX, baseY - 30 + jumpOffset, baseX, baseY + jumpOffset);

    // Draw Arms swinging
    drawLimb(baseX, baseY - 30 + jumpOffset, 20, angle);       // Right arm
    drawLimb(baseX, baseY - 30 + jumpOffset, 20, -angle);      // Left arm

    // Draw Legs swinging
    drawLimb(baseX, baseY + jumpOffset, 25, angle);            // Right leg
    drawLimb(baseX, baseY + jumpOffset, 25, -angle);           // Left leg
}

void drawObstacle(int x, int y) {
    // Draw a rectangular obstacle
    setfillstyle(SOLID_FILL, RED);
    bar(x, y - 20, x + 20, y);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    float angle = 0;
    int direction = 1;
    bool isJumping = false;
    int baseX = 100;  // Starting position of the man
    int baseY = 300;  // Ground level

    // Initial obstacle position
    int obstacleX = 500;
    int obstacleY = baseY;

    while (!kbhit()) {
        cleardevice();

        // Update limb swinging angle
        if (angle > 0.5 || angle < -0.5) {
            direction = -direction;
        }
        angle += 0.05 * direction;

        // Draw the running man, with jump effect
        drawRunningMan(baseX, baseY, angle, isJumping);

        // Draw obstacle
        drawObstacle(obstacleX, obstacleY);

        // Check if man reaches obstacle and is not jumping
        if (baseX + 10 >= obstacleX && baseX <= obstacleX + 20 && !isJumping) {
            outtextxy(250, 200, "Press Space to Jump!");
        }

        // Move the man forward
        baseX += 5;

        // Loop back the man and obstacle when off screen
        if (baseX > getmaxx()) baseX = 0;
        if (obstacleX < 0) obstacleX = getmaxx();

        // Check for jump key
        if (GetAsyncKeyState(VK_SPACE)) {
            isJumping = true;
        }

        // Reset jump state after a delay
        if (isJumping) {
            delay(100);  // Control the jump duration
            isJumping = false;
        }

        delay(50);
    }

    closegraph();
    return 0;
}