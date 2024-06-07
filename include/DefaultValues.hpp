#pragma once

#define SCREEN_X 2000
#define SCREEN_Y 1000

#define COLUMN_NUMBER (SCREEN_X / CELL_SIZE)
#define LINE_NUMBER (SCREEN_Y / CELL_SIZE)

#define FPS 200

//#define NB_CELLULAR_UNITS ((COLUMN_NUMBER * LINE_NUMBER) / 1000)
#define NB_CELLULAR_UNITS 100
#define CELL_SIZE 4

#define ANGLE_VIEW M_PI/3
#define DISTANCE_VIEW 20*CELL_SIZE
#define DISTANCE_COLLISION 2*CELL_SIZE

#define SIZE_MAX_QTREE 1
#define MAX_LEVEL_QTREE 20