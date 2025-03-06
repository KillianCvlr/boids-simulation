# Boids-Simulation
A (On-going) cellular automata in c++  that use SDL2 for rendering

## Goal
Make message based automatas that commuicates between each others using messages depending on what they can perceive.

## Requirements
This project compiles using clang :
>sudo apt install clang

It also uses the sdl2 library :
>sudo apt install sdl2-dev

## Controls 
Here is a list of the in-simulation controls implemented :
 - MOUSE_CLICK : Adds a new BOIDS on mouse position
 - "a" : SWITCH the complete display of the first boids (acceleration, velocity, near neighbors links/average position/average velocity)
 - "r" : THANOS ALL, clean up every BOIDS
 - "p" : SWITCH the proximity display of each BOIDS
 - "q" : SWITCH the display of quad-tree space-hashing
 - "f" : SWITCH the display of field of views
 - "l" : SWITCH the display of linked neighbors
 - "c" : SWITCH the display of BOIDS
 - "n" : GENERATES a new simulation

## Next steps : 
- Options parsing
- Debug-mode with sliders to change values
- optimisation 

