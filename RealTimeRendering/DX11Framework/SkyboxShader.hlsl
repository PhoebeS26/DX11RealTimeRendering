TextureCube skybox : register(t0);
SamplerState bilinearSampler : register(s0);

cbuffer ConstantBuffer : register(b0)
{
    float4x4 Projection;
    float4x4 View;
};

struct SkyboxVS_Out
{
    float4 position : SV_POSITION;
    float3 texCoord : TEXCOORD;
};

SkyboxVS_Out VS_Skybox(float3 Position : POSITION)
{
    SkyboxVS_Out output;

    // Transform vertex from model space to view space 
    float4 posView = mul(float4(Position, 1.0f), View);
    
    // Transform vertex from view space to clip space 
    float4 posViewProj = mul(posView, Projection);

    // Force depth to far plane
    output.position = float4(posViewProj.xy, posViewProj.w, posViewProj.w);

    // Pass original vertex position to pixel shader as texture coordinate
    output.texCoord = Position;

    return output;
}

float4 PS_Skybox(SkyboxVS_Out input) : SV_TARGET
{
     // Sample the cube map using the vertex direction
    return skybox.Sample(bilinearSampler, input.texCoord);
}

