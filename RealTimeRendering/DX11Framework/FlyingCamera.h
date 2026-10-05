#pragma once
#include <Windows.h>
#include "BaseCamera.h"



class FlyingCamera : public BaseCamera
{
private:
    XMFLOAT3 _forward;
    float _moveSpeed;
    float _turnSpeed;
    float _yaw;
    float _pitch;

public:
    FlyingCamera(XMFLOAT3 eye, XMFLOAT3 forward, XMFLOAT3 up, float windowWidth, float windowHeight, float nearDepth, float farDepth);

    void Update(float deltaTime) override;
};
