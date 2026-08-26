#include "raylib.h"
#include "Constants.h"
#include "CameraController.h"
#include "Ball.h"
#include "Spring.h"
#include "Modifier.h"
#include "defaults.h"

int main()
{
    // SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(ScreenAttrib::width, ScreenAttrib::height, "-- MUCH PHYSICS --");
    // SetTargetFPS(config.screen.targetFPS);

    FollowCam cc = Basic::camera;
    Modifier::WorldDefaultSetup(Basic::world);
    float dt = 0.0f;
    float duration = 0.0f;
    while (!WindowShouldClose())
    {
        float partial_dt = dt / Constants::stepsPerFrame;
        if (dt > 0.1f)
            dt = 0.1f; // Safeguard against large lag spikes
        if (Basic::world.getNumBalls() > 1)
            cc.FollowPosition(Basic::world.getBall(Basic::world.getNumBalls() / 2).position, dt);
        cc.Update(dt);

        Modifier::Wiggle(Basic::world, duration);
        for (int i = 0; i < Constants::stepsPerFrame; i++)
        {
            Basic::world.ApplyForces(partial_dt);
        }

        // --- Render ---
        BeginDrawing();
        ClearBackground(BgAttrib::color);

        BeginMode3D(cc.GetCamera());
        // Render spring and balls
        Basic::world.Draw();

        EndMode3D();
        DrawFPS(10, 10);
        EndDrawing();
        dt = GetFrameTime();
        duration += dt;
    }

    CloseWindow();
    return 0;
}