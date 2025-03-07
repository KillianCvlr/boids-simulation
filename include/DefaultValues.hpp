#pragma once
#include <math.h>

// Display parameters

extern int SCREEN_X;
extern int SCREEN_Y;

extern int COLUMN_NUMBER;
extern int LINE_NUMBER;

extern int FPS;

//Simulation parameters

extern int NB_CELLULAR_UNITS;
//extern int NB_CELLULAR_UNITS;
extern int CELL_SIZE;

extern float ANGLE_VIEW;
extern int DISTANCE_VIEW;

extern int SIZE_MAX_QTREE;
extern int MAX_LEVEL_QTREE;

extern float COHESION_FACTOR;
extern float ALIGNMENT_FACTOR;
extern float SEPARATION_FACTOR;
extern float MAX_SPEED;
extern float MAX_ACCEL;
extern int MIN_SEPARATOR_DISTANCE;

extern float DT;

void setDefaultValues();
