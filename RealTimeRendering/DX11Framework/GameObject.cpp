#include "GameObject.h"
#include <cstring> 

// Initialize world matrix to identity
GameObject::GameObject()
{
    XMStoreFloat4x4(&worldMatrix, XMMatrixIdentity());
}

void GameObject::Draw(ID3D11DeviceContext* context, ID3D11Buffer* constantBuffer, ConstantBuffer& cbData, ID3D11VertexShader* vs, ID3D11PixelShader* ps)
{
    // Make sure mesh has valid buffers before attempting to draw
    if (!mesh.VertexBuffer || !mesh.IndexBuffer) return;
    
    // Update world matrix inside constant buffer
    cbData.World = XMMatrixTranspose(XMLoadFloat4x4(&worldMatrix));

    // Map constant buffer
    D3D11_MAPPED_SUBRESOURCE mappedSubresource;
    context->Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
    memcpy(mappedSubresource.pData, &cbData, sizeof(cbData));
    context->Unmap(constantBuffer, 0);

    // Bind mesh buffers
    UINT stride = mesh.VBStride;
    UINT offset = mesh.VBOffset;
    context->IASetVertexBuffers(0, 1, &mesh.VertexBuffer, &stride, &offset);
    context->IASetIndexBuffer(mesh.IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Bind shaders and texture
    context->VSSetShader(vs, nullptr, 0);
    context->PSSetShader(ps, nullptr, 0);
    if (texture)
        context->PSSetShaderResources(0, 1, &texture);

    // Draw
    context->DrawIndexed(mesh.IndexCount, 0, 0);
}
