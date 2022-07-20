#pragma once
#include <wrl/client.h>
#include <d3d11.h>
class DEVICECONTEXT
{
private:
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> devContext;


public:
	void ChangeColor(ID3D11RenderTargetView* pRenderTargetView , float r, float g, float b);
	void setTopology(D3D11_PRIMITIVE_TOPOLOGY topology);
	void setInputLayout(ID3D11InputLayout* inputLayout);
	void bindIndexBuffer(ID3D11Buffer* buffer);

	template<class T>
	void bindVertexBuffer(T* vertices, ID3D11Buffer* buffer)
	{
		// needs to be created with a ID3D11Device::CreateBuffer
		const UINT stride = sizeof(T);
		devContext->IAGetVertexBuffers(0, 1, buffer, stride, 0);
	}
	
	 Microsoft::WRL::Details::ComPtrRef<Microsoft::WRL::ComPtr<ID3D11DeviceContext>> operator&();
	 ID3D11DeviceContext* operator->();
	 ID3D11DeviceContext** GetAddressOf();

};

