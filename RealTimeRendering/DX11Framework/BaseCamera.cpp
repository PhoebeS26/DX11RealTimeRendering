#include "BaseCamera.h"
#include <DirectXMath.h>

using namespace DirectX;

BaseCamera::BaseCamera(XMFLOAT3 eye, XMFLOAT3 at, XMFLOAT3 up, float windowWidth, float windowHeight, float nearDepth, float farDepth) : _eye(eye), _at(at), _up(up), _windowWidth(windowWidth), _windowHeight(windowHeight), _nearDepth(nearDepth), _farDepth(farDepth)
{
    // Create view matrix
    XMMATRIX viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&_eye), XMLoadFloat3(&_at), XMLoadFloat3(&_up));
    XMStoreFloat4x4(&_view, viewMatrix);

    // Create projection matrix
    float aspect = _windowWidth / _windowHeight;
    XMMATRIX projMatrix = XMMatrixPerspectiveFovLH(XMConvertToRadians(90.0f), aspect, _nearDepth, _farDepth);
    XMStoreFloat4x4(&_projection, projMatrix);
}

BaseCamera::~BaseCamera()
{
   
}

void BaseCamera::Update(float deltaTime)
{
    
}

