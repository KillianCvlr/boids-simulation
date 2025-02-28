#pragma once

// Display parameters

#define SCREEN_X 2000
#define SCREEN_Y 1000

#define COLUMN_NUMBER (SCREEN_X / CELL_SIZE)
#define LINE_NUMBER (SCREEN_Y / CELL_SIZE)

#define FPS 200

//Simulation parameters

#define NB_CELLULAR_UNITS ((COLUMN_NUMBER * LINE_NUMBER) / 200)
//#define NB_CELLULAR_UNITS 1
#define CELL_SIZE 4

#define ANGLE_VIEW  M_PIf + M_PI_4f
#define DISTANCE_VIEW 20*CELL_SIZE

#define SIZE_MAX_QTREE 2
#define MAX_LEVEL_QTREE 20

#define COHESION_FACTOR 0.02
#define ALIGNMENT_FACTOR 0.05
#define SEPARATION_FACTOR 0.05
#define MAX_SPEED 1.0
#define MAX_ACCEL 1.0
#define MIN_SEPARATOR_DISTANCE 4*CELL_SIZE

#define DT 0.01