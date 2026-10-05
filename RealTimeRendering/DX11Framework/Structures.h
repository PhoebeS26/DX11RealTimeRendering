#pragma once
#include "DX11Framework.h"
#include <DirectXMath.h>

// Simple structure for a vertex in 3D space
struct SimpleVertex
{
    XMFLOAT3 Pos;
    XMFLOAT3 Normal;
    XMFLOAT2 TexC;

    bool operator<(const SimpleVertex other) const
    {
        return memcmp((void*)this, (void*)&other, sizeof(SimpleVertex)) > 0;
    }
};
