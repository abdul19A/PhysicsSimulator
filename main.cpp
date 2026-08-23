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

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        float partial_dt = dt / config.stepsPerFrame;
        if (dt > 0.1f)
            dt = 0.1f; // Safeguard against large lag spikes

        cc.FollowPosition(configPhysicsWorld.getBall(21 * 21 / 2).position, dt);
        cc.Update(dt);

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

        EndDrawing();
    }

    CloseWindow();
    return 0;
}