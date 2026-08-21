#pragma once 

#include <vector>
#include "Ball.h"
#include "Spring.h"
#include "Wall.h"
#include "DataLogger.h"

class PhysicsWorld {
public:
    PhysicsWorld() : BallForce("bf") {};

    void addBall(Ball ball) {balls.push_back(ball); };
    void addSpring(Spring spring) {springs.push_back(spring); };
    void addWall(Wall wall) {walls.push_back(wall); };

    Spring& getSpring(int index) {return springs.at(index); };
    Ball& getBall(int index) {return balls.at(index); };
    Wall& getWall(int index) {return walls.at(index); };

    void ApplyForces(float dt);
    void Draw();
    void OnExit();

private:
    std::vector<Ball>   balls;
    std::vector<Spring> springs;
    std::vector<Wall>   walls;
    DataLogger<Vector3> BallForce;
};