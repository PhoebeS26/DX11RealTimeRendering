#pragma once

#include <windows.h>
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <vector>
#include <string>
#include "BaseCamera.h"
#include "FlyingCamera.h"
//#include <wrl.h>
//using Microsoft::WRL::ComPtr;

struct MeshData;
class GameObject;

using namespace DirectX;

struct ConstantBuffer
{
    XMMATRIX Projection;
    XMMATRIX View;
    XMMATRIX World;

    XMFLOAT4 DiffuseLight;
    XMFLOAT4 DiffuseMaterial;

    XMFLOAT4 AmbientLight;
    XMFLOAT4 AmbientMaterial;

    XMFLOAT4 SpecularLight;
    XMFLOAT4 SpecularMaterial;
    XMFLOAT3 CameraPosition;

    float SpecPower;
    XMFLOAT3 LightDir;

    XMFLOAT3 SpotPos;
    XMFLOAT3 SpotDir;
    float SpotAngle;

    float count;
};


class DX11Framework
{
    int _WindowWidth = 1280;
    int _WindowHeight = 768;
    
    std::vector<BaseCamera*> _cameras;
    int _activeCameraIndex = 0;
    int _currentRenderMode = 0;

    std::vector<GameObject*> _sceneObjects;

    ID3D11DeviceContext* _immediateContext = nullptr;
    ID3D11Device* _device;
    IDXGIDevice* _dxgiDevice = nullptr;
    IDXGIFactory2* _dxgiFactory = nullptr;
    ID3D11RenderTargetView* _frameBufferView = nullptr;
    IDXGISwapChain1* _swapChain;
    D3D11_VIEWPORT _viewport;

    ID3D11RasterizerState* _fillState;
    ID3D11RasterizerState* _wireframeState;
    ID3D11RasterizerState* _skyboxRasterizerState;
    ID3D11VertexShader* _vertexShader;
    ID3D11InputLayout* _inputLayout;
    ID3D11PixelShader* _pixelShader;
    ID3D11Buffer* _constantBuffer;
    ID3D11Buffer* _vertexBuffer;
    ID3D11Buffer* _indexBuffer;
    ID3D11Buffer* _cubeVertexBuffer;
    ID3D11Buffer* _cubeIndexBuffer;
    ID3D11Buffer* _pyramidVertexBuffer;
    ID3D11Buffer* _pyramidIndexBuffer;
    ID3D11Buffer* _lineVertexBuffer;
    ID3D11Texture2D* _depthStencilBuffer;
    ID3D11DepthStencilView* _depthStencilView;
    ID3D11SamplerState* _bilinearSamplerState;
    ID3D11ShaderResourceView* _crateTexture;
    ID3D11ShaderResourceView* _asphaltTexture;
    ID3D11ShaderResourceView* _skyboxTexture = nullptr;
    ID3D11BlendState* _transparency;

    ID3D11VertexShader* _vertexShaderSkybox;
    ID3D11PixelShader* _pixelShaderSkybox;
    ID3D11DepthStencilState* _depthStencilSkybox;

    HWND _windowHandle;

    XMFLOAT4X4 _WorldSun;
    XMFLOAT4X4 _WorldPlanet;
    XMFLOAT4X4 _WorldMoon;
    XMFLOAT4X4 _WorldMesh;
    XMFLOAT4X4 _WorldCylinder;
    XMFLOAT4X4 _WorldLine;
    XMFLOAT4X4 _View;
    XMFLOAT4X4 _Projection;

    XMFLOAT4 _diffuseLight;
    XMFLOAT4 _diffuseMaterial;

    XMFLOAT4 _ambientLight;
    XMFLOAT4 _ambientMaterial;

    XMFLOAT4 _specularLight;
    XMFLOAT4 _specularMaterial;
    XMFLOAT3 _cameraPosition;

    float _specPower;
    XMFLOAT3 _lightDir;

    XMFLOAT3 _spotPos;
    XMFLOAT3 _spotDir;
    float _spotAngle;

    ConstantBuffer _cbData;

public:
    HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);
    HRESULT CreateWindowHandle(HINSTANCE hInstance, int nCmdShow);
    HRESULT CreateD3DDevice();
    HRESULT CreateSwapChainAndFrameBuffer();
    HRESULT InitShadersAndInputLayout();
    HRESULT InitVertexIndexBuffers();
    HRESULT InitPipelineVariables();
    HRESULT LoadLightsFromJSON(const std::string& path);
    HRESULT LoadSceneFromJSON(const std::string& path);
    HRESULT InitRunTimeData();
    ~DX11Framework();
    void Update();
    void Draw();
};
