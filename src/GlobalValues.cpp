#include "GlobalValues.hpp"



// Display parameters

int SCREEN_X;
int SCREEN_Y;

int COLUMN_NUMBER;
int LINE_NUMBER;

int FPS;

//Simulation parameters

size_t NB_CELLULAR_UNITS;
//int NB_CELLULAR_UNITS;
int CELL_SIZE;

float ANGLE_VIEW;
int DISTANCE_VIEW;

int SIZE_MAX_QTREE;
int MAX_LEVEL_QTREE;

float COHESION_FACTOR;
float ALIGNMENT_FACTOR;
float SEPARATION_FACTOR;
float MAX_SPEED;
float MAX_ACCEL;
float MIN_SEPARATOR_DISTANCE;

float DT;


void setDefaultValues(){
    // Display parameters

    SCREEN_X = 2000;
    SCREEN_Y = 1000;

    CELL_SIZE = 1;
    COLUMN_NUMBER = (SCREEN_X / CELL_SIZE);
    LINE_NUMBER = (SCREEN_Y / CELL_SIZE);

    FPS = 200;

    //Simulation parameters 

    NB_CELLULAR_UNITS = ((COLUMN_NUMBER * LINE_NUMBER) / 200);
    // NB_CELLULAR_UNITS = 1

    ANGLE_VIEW =  M_PIf + M_PI_4f;
    DISTANCE_VIEW = 20*CELL_SIZE;

    SIZE_MAX_QTREE = 2;
    MAX_LEVEL_QTREE = 20;

    COHESION_FACTOR = 0.02;
    ALIGNMENT_FACTOR = 0.05;
    SEPARATION_FACTOR = 0.05;
    MAX_SPEED = 1.0;
    MAX_ACCEL = 1.0;
    MIN_SEPARATOR_DISTANCE = 4*CELL_SIZE;

    DT = 0.01;
}
