#include "Terrain.h"

Terrain::Terrain(ID3D11Device* device): _device(device)
{
}

Terrain::~Terrain()
{
    if (_vertexBuffer) _vertexBuffer->Release();
    if (_indexBuffer) _indexBuffer->Release();
}

void Terrain::GenFlatGrid(float width, float depth, float columns, float rows)
{
    float halfWidth = width * 0.5f;
    float halfDepth = depth * 0.5f;

    float dx = width / (columns - 1);
    float dz = depth / (rows - 1);

    float du = 1.0f / (columns - 1);
    float dv = 1.0f / (rows - 1);

    std::vector<SimpleVertex> vertices(columns * rows);
    std::vector<WORD> indices((rows - 1) * (columns - 1) * 6);

    // Generate vertices
    for (int i = 0; i < rows; ++i)
    {
        float z = halfDepth - i * dz;
        for (int j = 0; j < columns; ++j)
        {
            float x = -halfWidth + j * dx;

            int index = i * columns + j;
            vertices[index].Pos = XMFLOAT3(x, 0.0f, z);  // flat grid, y=0
            vertices[index].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
            vertices[index].TexC = XMFLOAT2(j * du, i * dv);
        }
    }

    // Generate indices
    int k = 0;
    for (int i = 0; i < rows - 1; ++i)
    {
        for (int j = 0; j < columns - 1; ++j)
        {
            int start = i * columns + j;

            indices[k++] = start;
            indices[k++] = start + 1;
            indices[k++] = start + columns;

            indices[k++] = start + columns;
            indices[k++] = start + 1;
            indices[k++] = start + columns + 1;
        }
    }

    // Create D3D buffers
    D3D11_BUFFER_DESC vbd = {};
    vbd.ByteWidth = sizeof(SimpleVertex) * vertices.size();
    vbd.Usage = D3D11_USAGE_IMMUTABLE;
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA vinit = {};
    vinit.pSysMem = vertices.data();
    _device->CreateBuffer(&vbd, &vinit, &_vertexBuffer);

    D3D11_BUFFER_DESC ibd = {};
    ibd.ByteWidth = sizeof(WORD) * indices.size();
    ibd.Usage = D3D11_USAGE_IMMUTABLE;
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA iinit = {};
    iinit.pSysMem = indices.data();
    _device->CreateBuffer(&ibd, &iinit, &_indexBuffer);

    _indexCount = static_cast<UINT>(indices.size());
}

void Terrain::HeightMapLoad(int heightMapWidth, int heightMapHeight, std::string heightMapFileName)
{
    std::vector<unsigned char> in(heightMapWidth * heightMapHeight);

    std::ifstream inFile;
    inFile.open(heightMapFileName.c_str(), std::ios_base::binary);

    if (inFile)
    {
        inFile.read((char*)&in[0], (std::streamsize)in.size());
        inFile.close();
    }

    heightMapData.resize(heightMapHeight * heightMapWidth);
    heightScale = 10.0f;

    for (unsigned int i = 0; i < heightMapHeight * heightMapWidth; ++i)
    {
        heightMapData[i] = (in[i] / 255.0f) * heightScale;
    }
}

