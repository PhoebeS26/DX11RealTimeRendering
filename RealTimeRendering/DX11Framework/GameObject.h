#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "OBJLoader.h"    
#include "Structures.h"  

using namespace DirectX;

class GameObject
{
private:
    MeshData mesh;                          
    XMFLOAT4X4 worldMatrix;
    ID3D11ShaderResourceView* texture = nullptr;
    bool _isTransparent = false;

public:
    GameObject();

    // Enable/disable transparency flag
    void SetTransparent(bool value) { _isTransparent = value; }

    // Returns true if object should be drawn transparent
    bool IsTransparent() const { return _isTransparent; }

    // Assign mesh data
    void SetMeshData(const MeshData& inMesh) { mesh = inMesh; }

    // Assign object texture
    void SetTexture(ID3D11ShaderResourceView* inTexture) { texture = inTexture; }

    // Set the world transform matrix
    void SetWorldMatrix(const XMFLOAT4X4& m) { worldMatrix = m; }

    // Access to mesh data
    MeshData* GetMeshData() { return &mesh; }

    // Access to world matrix
    XMFLOAT4X4* GetWorldMatrix() { return &worldMatrix; }

    // Access to texture SRV
    ID3D11ShaderResourceView* GetTexture() const { return texture; }

    // Render mesh
    void Draw(ID3D11DeviceContext* context, ID3D11Buffer* constantBuffer, ConstantBuffer& cbData, ID3D11VertexShader* vs, ID3D11PixelShader* ps);
};

