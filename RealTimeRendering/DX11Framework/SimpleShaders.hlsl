Texture2D diffuseTex : register(t0);
SamplerState bilinearSampler : register(s0);

cbuffer ConstantBuffer : register(b0)
{
    float4x4 Projection;
    float4x4 View;
    float4x4 World;
    
    float4 DiffuseLight;
    float4 DiffuseMaterial;
    
    float4 AmbientLight;
    float4 AmbientMaterial;
    
    float4 SpecularLight;
    float4 SpecularMaterial;
    float3 CameraPosition;

    float SpecPower;
    float3 LightDir;
    
    float3 SpotPos;
    float3 SpotDir;
    float SpotAngle;
    
    float count;
    
    uint hasTexture;

}

struct VS_Out
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float3 NormalW : NORMAL0;
    float3 PosW : POSITION0;
    float2 Tex : TEXCOORD0;
};

VS_Out VS_main(float3 Position : POSITION, float3 Normal : NORMAL, float2 Tex : TEXCOORD0)
{   
    //Position.y += sin(count);
    
    VS_Out output = (VS_Out)0;

     // World space position
    float4 PosWorld = mul(float4(Position, 1.0f), World);
    output.PosW = PosWorld.xyz;

    // Transform normal to world space
    output.NormalW = normalize(mul(Normal, (float3x3) World));
    
    output.Tex = Tex;

    // Transform to clip space
    output.position = mul(PosWorld, View);
    output.position = mul(output.position, Projection);

    return output;
}

float4 PS_main(VS_Out input) : SV_TARGET
{
    
     // Texture Sample
    float4 texColor = diffuseTex.Sample(bilinearSampler, input.Tex);
  
      // Re-normalize interpolated normal!
    float3 NormalW = normalize(input.NormalW);

    // Reverse light direction first
    float3 LightDirW = normalize(LightDir);

    // Lambert diffuse
    float DiffuseAmount = max(dot(NormalW, LightDirW), 0.0f);
    float4 DiffuseColor = DiffuseAmount * (texColor * DiffuseLight);

    // Ambient contribution
    float4 AmbientColor = texColor * AmbientLight;
    
    // Specular
    float3 viewDir = normalize(CameraPosition - input.PosW);
    
    float3 reflectDir = reflect(LightDirW, NormalW);
    float specFactor = pow(max(dot(viewDir, reflectDir), 0.0f), SpecPower);
    float4 SpecularColor = specFactor * (SpecularMaterial * SpecularLight);
    
    // Spotlight
    float3 lightToFrag = normalize(input.PosW - SpotPos);
    float spotEffect = dot(-lightToFrag, normalize(SpotDir));
    
    float intensity = saturate((spotEffect - SpotAngle) / 0.2f); 
    float4 SpotLight = float4(0.0f, 0.0f, 1.0f, 1.0f) * intensity * 0.2f; 
    
    // Combine
    float4 finalColor = AmbientColor + DiffuseColor + SpecularColor + SpotLight;
    
    return finalColor;

}