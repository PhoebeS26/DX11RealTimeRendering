#include "FlyingCamera.h"


using namespace DirectX;

FlyingCamera::FlyingCamera(XMFLOAT3 eye, XMFLOAT3 forward, XMFLOAT3 up, float windowWidth, float windowHeight, float nearDepth, float farDepth) : BaseCamera(eye, XMFLOAT3(eye.x + forward.x, eye.y + forward.y, eye.z + forward.z), up, windowWidth, windowHeight, nearDepth, farDepth)
{
    _forward = forward;
    _moveSpeed = 5.0f;
    _turnSpeed = 2.0f;
    _yaw = 0.0f;
    _pitch = 0.0f;
}

void FlyingCamera::Update(float deltaTime)
{
    XMVECTOR eye = XMLoadFloat3(&_eye);
    XMVECTOR forward = XMLoadFloat3(&_forward);
    XMVECTOR up = XMLoadFloat3(&_up);

    // Right vector
    XMVECTOR right = XMVector3Normalize(XMVector3Cross(up, forward));

    // WASDQE movement
    if (GetAsyncKeyState('W') & 0x8000) eye += forward * (_moveSpeed * deltaTime);
    if (GetAsyncKeyState('S') & 0x8000) eye -= forward * (_moveSpeed * deltaTime);
    if (GetAsyncKeyState('A') & 0x8000) eye -= right * (_moveSpeed * deltaTime);
    if (GetAsyncKeyState('D') & 0x8000) eye += right * (_moveSpeed * deltaTime);
    if (GetAsyncKeyState('Q') & 0x8000) eye += up * (_moveSpeed * deltaTime);
    if (GetAsyncKeyState('E') & 0x8000) eye -= up * (_moveSpeed * deltaTime);

    // Arrow keys rotation
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) _yaw -= _turnSpeed * deltaTime;
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) _yaw += _turnSpeed * deltaTime;
    if (GetAsyncKeyState(VK_UP) & 0x8000) _pitch += _turnSpeed * deltaTime;
    if (GetAsyncKeyState(VK_DOWN) & 0x8000) _pitch -= _turnSpeed * deltaTime;

    // Clamp pitch
    if (_pitch > XM_PIDIV2 - 0.1f) _pitch = XM_PIDIV2 - 0.1f;
    if (_pitch < -XM_PIDIV2 + 0.1f) _pitch = -XM_PIDIV2 + 0.1f;

    // Update forward
    XMMATRIX rotation = XMMatrixRotationRollPitchYaw(_pitch, _yaw, 0);
    forward = XMVector3TransformCoord(XMVectorSet(0, 0, 1, 0), rotation);
    forward = XMVector3Normalize(forward);

    // Store
    XMStoreFloat3(&_eye, eye);
    XMStoreFloat3(&_forward, forward);

    // Update view
    XMMATRIX view = XMMatrixLookToLH(eye, forward, up);
    XMStoreFloat4x4(&_view, view);
}
