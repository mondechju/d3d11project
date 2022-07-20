#include "DEVICE.h"
#include <d3d11.h>
#include <wrl/client.h>
HRESULT DEVICE::createBuffer(D3D11_BUFFER_DESC* bdc, void* data, __out ID3D11Buffer* buffer)
{
    D3D11_SUBRESOURCE_DATA resourceData = {};
    resourceData.pSysMem = data;
    auto res = device->CreateBuffer(bdc,&resourceData,&buffer);
    if (res != S_OK) throw "failed to create a buffer";
    return res;
}

HRESULT DEVICE::createIndexBuffer(std::vector<int>* data, __out ID3D11Buffer* indexBuffer)  // possible to do with std::span (recomendation from c++ together)
{
    D3D11_BUFFER_DESC bdc = {};
    bdc.ByteWidth = data->size();//  Size of the buffer in bytes.
    bdc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
    bdc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
    bdc.CPUAccessFlags = 0;
    bdc.MiscFlags = 0;
    bdc.StructureByteStride = sizeof(int); // The size of each element in the buffer structure (in bytes) 
    
    return createBuffer(&bdc,data->data(), indexBuffer);
}

HRESULT DEVICE::createVertexBuffer(std::vector<double>* data, __out ID3D11Buffer* vertexBuffer)
{
    D3D11_BUFFER_DESC bdc = {};
    bdc.ByteWidth = data->size();//  Size of the buffer in bytes.
    bdc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
    bdc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
    bdc.CPUAccessFlags = 0;
    bdc.MiscFlags = 0;
    bdc.StructureByteStride = sizeof(double);

   return createBuffer(&bdc, data->data(), vertexBuffer);
}

HRESULT DEVICE::CreateRenderTargetView(ID3D11Resource* backBuffer)
{
    auto res = device->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);
    if (res != S_OK) throw "Failed creating render target view";
    return res;
}

 ID3D11Device* DEVICE::operator->()
{
    return device.operator->();
}

 Microsoft::WRL::Details::ComPtrRef<Microsoft::WRL::ComPtr<ID3D11Device>>  DEVICE::operator&()
{
    return device.operator&();
}

 ID3D11Device** DEVICE::GetAddressOf()
{
    return device.GetAddressOf();
}

 Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& DEVICE::getRenderTargetView()
 {
     return renderTargetView;
 }
