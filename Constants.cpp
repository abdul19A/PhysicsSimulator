#include "Constants.h"

Color BgAttrib::color = {0, 0, 0, 255};

const int ScreenAttrib::width = 1000;
const int ScreenAttrib::height = 800;
const int ScreenAttrib::targetFPS = 60;

const float Constants::gravity = 10.1f;
const int Constants::stepsPerFrame = 1;

const float NetAttrib::springLength = 10.00f;
const float NetAttrib::springK = 1000.0f; // Higher stiffness helps hold up longer chains
const float NetAttrib::springC = 1.0;     // Keeps the chain from oscillating infinitely
const float NetAttrib::ballWeight = 0.0f;
const float NetAttrib::ballRadius = 1.0f;

const bool CanDraw::ball = false;
const bool CanDraw::spring = true;
const bool CanDraw::wall = false;
const bool CanDraw::plane = true;

Color BoxAttrib::colors[6] = {RED, PURPLE, BLUE, GREEN, YELLOW, ORANGE};
const float BoxAttrib::size = 1000.0f;
const int Gaurd::collisionLoop = 4;
