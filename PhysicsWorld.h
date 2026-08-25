#pragma once

#include <vector>
#include "Ball.h"
#include "Spring.h"
#include "Wall.h"
#include "DataLogger.h"

class PhysicsWorld
{
public:
    PhysicsWorld() {};

    void addBall(Ball ball)
    {
        balls.push_back(ball);
    };
    void addSpring(Spring spring)
    {
        springs.push_back(spring);
    };
    void addWall(Wall wall)
    {
        walls.push_back(wall);
    };

    void GenerateBox(float size);
    void GenerateNet(Vector3 start, Vector3 end, int width, int length);

    Spring &getSpring(int index) { return springs.at(index); };
    Ball &getBall(int index) { return balls.at(index); };
    Wall &getWall(int index) { return walls.at(index); };

    int getNumBalls() const { return balls.size(); };
    int getNumWalls() const { return walls.size(); };
    int getNumSprings() const { return springs.size(); };

    void ApplyForces(float dt);
    void Draw() const;
    void OnExit();

private:
    std::vector<Ball> balls;
    std::vector<Spring> springs;
    std::vector<Wall> walls;
};