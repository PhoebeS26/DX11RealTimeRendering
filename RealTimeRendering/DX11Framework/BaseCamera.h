#pragma once
#include <DirectXMath.h>
using namespace DirectX;

class BaseCamera
{
protected:
    XMFLOAT3 _eye;
    XMFLOAT3 _at;
    XMFLOAT3 _up;

    float _windowWidth;
    float _windowHeight;
    float _nearDepth;
    float _farDepth;

    XMFLOAT4X4 _view;
    XMFLOAT4X4 _projection;

public:
    BaseCamera(XMFLOAT3 eye, XMFLOAT3 at, XMFLOAT3 up, float windowWidth, float windowHeight, float nearDepth = 0.01f, float farDepth = 100.0f);
    ~BaseCamera();

    virtual void Update(float deltaTime); 

    // Accessors
    XMFLOAT3 GetEye() const { return _eye; }
    XMFLOAT3 GetAt() const { return _at; }
    XMFLOAT3 GetUp() const { return _up; }

    XMFLOAT4X4& GetViewMatrix() { return _view; }
    XMFLOAT4X4& GetProjectionMatrix() { return _projection; }

 
};



