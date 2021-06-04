#ifndef I3D_ASTEROIDCONSTANTS_H
#define I3D_ASTEROIDCONSTANTS_H

float constexpr ASTEROID_MIN_SPEED = 250;
float constexpr ASTEROID_MAX_SPEED = 500;

float constexpr ASTEROID_MIN_ROTATION_SPEED = 50;
float constexpr ASTEROID_MAX_ROTATION_SPEED = 100;

float constexpr ASTEROID_MIN_RADIUS = 90;
float constexpr ASTEROID_MAX_RADIUS = 180;

int constexpr ASTEROID_MIN_HEALTH = 10;
int constexpr ASTEROID_MAX_HEALTH = 20;

float constexpr ASTEROID_STACK_COUNT = 10;
float constexpr ASTEROID_SECTOR_COUNT = 10;

float constexpr ASTEROID_FUDGE = 0.3; // +- % to the XZ plane of each asteroid vertex (keep between 0 and 1!)

#endif // I3D_ASTEROIDCONTANTS_H