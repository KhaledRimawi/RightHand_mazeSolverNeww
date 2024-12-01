#include <stdio.h>
#include "API.h"

enum Direction { NORTH, EAST, SOUTH, WEST };

int x = 0, y = 0;
enum Direction dir = NORTH;

void log(char* text) {
    fprintf(stderr, "%s\n", text);
    fflush(stderr);
}

void colorCell(int x, int y, char color) {
    API_setColor(x, y, color);
    API_setText(x, y, "X");
}

void colorWall(int x, int y, enum Direction dir) {
    switch (dir) {
        case NORTH: API_setWall(x, y, 'n'); break;
        case EAST:  API_setWall(x, y, 'e'); break;
        case SOUTH: API_setWall(x, y, 's'); break;
        case WEST:  API_setWall(x, y, 'w'); break;
    }
}

void colorSideWalls() {
    // Color the right wall
    if (API_wallRight()) {
        colorWall(x, y, (dir + 1) % 4); 
    }

    // Color the left wall
    if (API_wallLeft()) {
        colorWall(x, y, (dir + 3) % 4); 
    }
}

void updatePosition() {
    if (dir == NORTH) y++;
    else if (dir == EAST) x++;
    else if (dir == SOUTH) y--;
    else if (dir == WEST) x--;
}

void turnLeft() {
    dir = (dir + 3) % 4;
    API_turnLeft();
}

void turnRight() {
    dir = (dir + 1) % 4;
    API_turnRight();
}

int main(int argc, char* argv[]) {
    log("Running...");
    colorCell(x, y, 'G');

    while (1) {
        if (!API_wallRight()) {
            turnRight();
        } else {
            colorWall(x, y, (dir + 1) % 4);
        }

        while (API_wallFront()) {
            colorWall(x, y, dir);
            turnLeft();
        }

        API_moveForward();
        updatePosition();
        colorCell(x, y, 'G');
        colorSideWalls(); 
    }

    return 0;
}