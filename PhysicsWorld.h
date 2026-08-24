#pragma once

#include <vector>
#include "Ball.h"
#include "Spring.h"
#include "Wall.h"
#include "DataLogger.h"

class PhysicsWorld
{
public:
    PhysicsWorld() : BallForce("bf") {};

    void addBall(Ball ball)
    {
        numBalls++;
        balls.push_back(ball);
    };
    void addSpring(Spring spring)
    {
        numSprings++;
        springs.push_back(spring);
    };
    void addWall(Wall wall)
    {
        numWalls++;
        walls.push_back(wall);
    };

    void GenerateBox(float size);
    void GenerateNet(Vector3 start, Vector3 end, int width, int length);

    Spring &getSpring(int index) { return springs.at(index); };
    Ball &getBall(int index) { return balls.at(index); };
    Wall &getWall(int index) { return walls.at(index); };

    void ApplyForces(float dt);
    void Draw();
    void OnExit();

    int numBalls;
    int numWalls;
    int numSprings;

private:
    std::vector<Ball> balls;
    std::vector<Spring> springs;
    std::vector<Wall> walls;
    DataLogger<Vector3> BallForce;
};