#pragma once
#include <raylib.h>

class CameraController {
public:
    CameraController(Vector3 startPos, float turnSpeed, float pitchLimit, float moveSpeed, float fovy);
    CameraController(const CameraController& other) = default;
    CameraController& operator=(const CameraController& other) = default;

    Vector3 GetForward() const;
    Vector3 GetRight() const;
    Camera3D GetCamera() const { return camera; }

protected:
    Camera3D camera;
    float yaw = 0.0f;
    float pitch = 0.0f;
    float turnSpeed;
    float pitchLimit;
    float moveSpeed;
};

class FollowCam : public CameraController {
public:
    FollowCam(Vector3 startPos, float turnSpeed, float pitchLimit,
              float moveSpeed, float fovy, float followRadius);

    FollowCam& operator=(const CameraController& other);
    void UpdateOrbit(float dt);
    void Update(float dt);
    void FollowPosition(Vector3 pos, float dt);

private:
    float followRadius;
};

class FreeCam : public CameraController {
public:
    using CameraController::CameraController;
    void UpdateLook(float dt);
    void UpdateMove(float dt);
    void Update(float dt);
};