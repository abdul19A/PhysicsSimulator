#include "CameraController.h"
#include <cmath>

// ============================================================
// CameraController (base)
// ============================================================

CameraController::CameraController(Vector3 startPos, float turnSpeed, float pitchLimit, float moveSpeed, float fovy)
    : turnSpeed(turnSpeed), pitchLimit(pitchLimit), moveSpeed(moveSpeed) {
    camera.position = startPos;
    camera.target = { startPos.x, startPos.y, startPos.z + 1.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = fovy;
    camera.projection = CAMERA_PERSPECTIVE;
}

Vector3 CameraController::GetForward() const {
    return { cosf(pitch) * sinf(yaw), sinf(pitch), cosf(pitch) * cosf(yaw) };
}

Vector3 CameraController::GetRight() const {
    return { -cosf(yaw), 0.0f, sinf(yaw) };
}

// ============================================================
// FollowCam
// ============================================================

FollowCam::FollowCam(Vector3 startPos, float turnSpeed, float pitchLimit,
                      float moveSpeed, float fovy, float followRadius)
    : CameraController(startPos, turnSpeed, pitchLimit, moveSpeed, fovy),
      followRadius(followRadius) {}

FollowCam& FollowCam::operator=(const CameraController& other) {
    CameraController::operator=(other);
    followRadius = 1.0f; // default
    return *this;
}
void FollowCam::UpdateOrbit(float dt) {
    if (IsKeyDown(KEY_LEFT))  yaw += turnSpeed * dt;
    if (IsKeyDown(KEY_RIGHT)) yaw -= turnSpeed * dt;
    if (IsKeyDown(KEY_UP))    pitch += turnSpeed * dt;
    if (IsKeyDown(KEY_DOWN))  pitch -= turnSpeed * dt;

    if (IsKeyDown(KEY_W))  followRadius -= moveSpeed * dt;
    if (IsKeyDown(KEY_S))  followRadius += moveSpeed * dt;

    if (followRadius <= 1.0f) followRadius = 1.0f;
    if (pitch > pitchLimit) pitch = pitchLimit;
    if (pitch < -pitchLimit) pitch = -pitchLimit;
}
void FollowCam::Update(float dt){
    UpdateOrbit(dt);
}
void FollowCam::FollowPosition(Vector3 pos, float dt) {
    // spherical -> Cartesian: yaw/pitch pick a direction, followRadius scales it
    Vector3 dir = {
        cosf(pitch) * sinf(yaw),
        sinf(pitch),
        cosf(pitch) * cosf(yaw)
    };

    Vector3 desiredPos = {
        pos.x - dir.x * followRadius,   // sit BEHIND the target along the look direction
        pos.y - dir.y * followRadius,
        pos.z - dir.z * followRadius
    };

    float t = 1.0f - expf(-(moveSpeed *moveSpeed) * dt);
    camera.position.x += (desiredPos.x - camera.position.x) * t;
    camera.position.y += (desiredPos.y - camera.position.y) * t;
    camera.position.z += (desiredPos.z - camera.position.z) * t;

    camera.target = pos;
}

// ============================================================
// FreeCam
// ============================================================

void FreeCam::UpdateLook(float dt) {
    if (IsKeyDown(KEY_LEFT))  yaw += turnSpeed * dt;
    if (IsKeyDown(KEY_RIGHT)) yaw -= turnSpeed * dt;
    if (IsKeyDown(KEY_UP))    pitch += turnSpeed * dt;
    if (IsKeyDown(KEY_DOWN))  pitch -= turnSpeed * dt;

    if (pitch > pitchLimit) pitch = pitchLimit;
    if (pitch < -pitchLimit) pitch = -pitchLimit;

    Vector3 forward = GetForward();
    camera.target.x = camera.position.x + forward.x;
    camera.target.y = camera.position.y + forward.y;
    camera.target.z = camera.position.z + forward.z;
}
void FreeCam::UpdateMove(float dt) {
    Vector3 moveForward = { sinf(yaw), 0.0f, cosf(yaw) };
    Vector3 moveRight = GetRight();

    Vector3 move = { 0.0f, 0.0f, 0.0f };
    if (IsKeyDown(KEY_W)) { move.x += moveForward.x; move.z += moveForward.z; }
    if (IsKeyDown(KEY_S)) { move.x -= moveForward.x; move.z -= moveForward.z; }
    if (IsKeyDown(KEY_D)) { move.x += moveRight.x;   move.z += moveRight.z;   }
    if (IsKeyDown(KEY_A)) { move.x -= moveRight.x;   move.z -= moveRight.z;   }
    if (IsKeyDown(KEY_SPACE))      { move.y += 1.0f; }
    if (IsKeyDown(KEY_LEFT_SHIFT)) { move.y -= 1.0f; }

    float lengthSq = move.x * move.x + move.y * move.y + move.z * move.z;
    if (lengthSq > 0.0f) {
        float invLen = 1.0f / sqrtf(lengthSq);
        move.x *= invLen;
        move.y *= invLen;
        move.z *= invLen;
    }

    camera.position.x += move.x * moveSpeed * dt;
    camera.position.y += move.y * moveSpeed * dt;
    camera.position.z += move.z * moveSpeed * dt;

    Vector3 forward = GetForward();
    camera.target.x = camera.position.x + forward.x;
    camera.target.y = camera.position.y + forward.y;
    camera.target.z = camera.position.z + forward.z;
}
void FreeCam::Update(float dt) {
    UpdateLook(dt);
    UpdateMove(dt);
}