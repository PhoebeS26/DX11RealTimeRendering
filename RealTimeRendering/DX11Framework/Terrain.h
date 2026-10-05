#pragma once
#include <d3d11_1.h>
#include <DirectXMath.h>
#include <vector>
#include <string>
#include <fstream>
#include "Structures.h"

using namespace DirectX;

class Terrain
{
public:
    Terrain(ID3D11Device* device);
    ~Terrain();

    void GenFlatGrid(float width, float depth, float columns, float rows);
    void HeightMapLoad(int heightMapWidth, int heightmapHeight, std::string heightMapFileName);
    ID3D11Buffer* GetVertexBuffer() const { return _vertexBuffer; }
    ID3D11Buffer* GetIndexBuffer() const { return _indexBuffer; }
    UINT GetIndexCount() const { return _indexCount; }

private:

    std::vector<float> heightMapData;
    float heightScale;

    ID3D11Device* _device;
    ID3D11Buffer* _vertexBuffer = nullptr;
    ID3D11Buffer* _indexBuffer = nullptr;
    UINT _indexCount = 0;
};


