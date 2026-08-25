#include "raylib.h"
#include "PhysicsConfig.h"
#include "CameraController.h"
#include "Ball.h"
#include "Spring.h"

int main()
{
    InitWindow(config.screen.width, config.screen.height, "-- MUCH PHYSICS --");
    SetTargetFPS(config.screen.targetFPS);

    FollowCam cc = config.basicCamera;
    setUpWorldDefault(configPhysicsWorld);

    bool drawInfo = false;
    int numFrame = 0;
    while (!WindowShouldClose())
    {
        numFrame++;
        float dt = GetFrameTime();
        float partial_dt = dt / config.stepsPerFrame;
        if (dt > 0.1f)
            dt = 0.1f; // Safeguard against large lag spikes
        if (configPhysicsWorld.getNumBalls() > 1)
            cc.FollowPosition(configPhysicsWorld.getBall(configPhysicsWorld.getNumBalls() / 2).position, dt);
        cc.Update(dt);

        if (IsKeyDown(KEY_P))
            partial_dt = 0.0f;

        if (IsKeyDown(KEY_I))
            drawInfo = true;
        else
        {
            drawInfo = false;
        }
        for (int i = 0; i < config.stepsPerFrame; i++)
        {
            configPhysicsWorld.ApplyForces(partial_dt);
        }

        // --- Render ---
        BeginDrawing();
        ClearBackground(config.background.color);

        BeginMode3D(cc.GetCamera());
        // Render spring and balls
        configPhysicsWorld.Draw();

        EndMode3D();
        DrawFPS(10, 10);
        DrawText(TextFormat("numFrame: %d", numFrame), config.screen.width * .025, config.screen.height * .1, 10, BLUE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}