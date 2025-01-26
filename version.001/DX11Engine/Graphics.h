#pragma once
class Graphics
{
public:
	Graphics(HWND hWnd);
	~Graphics();

	ComPtr<ID3D11Device> GetDevice() { return _device; }
	ComPtr<ID3D11DeviceContext> GetDeviceContext() { return _deviceContext; }

private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewport();

public:
	void RenderBegin();
	void RenderEnd();

private:
	HWND _hWnd;
	UINT _width;
	UINT _height;

private:
	ComPtr<ID3D11Device> _device = nullptr; // ���ҽ��� ����� �Ҵ��Ű�� �������̽�
	ComPtr<ID3D11DeviceContext> _deviceContext = nullptr; // ���Ҹ��� ���������� ���ο� �����ϴ� �������̽�
	ComPtr<IDXGISwapChain> _swapChain = nullptr; // ���� ���۸��� ���� �������̽�

	// RTV(�ĸ� ���۸� �׸��� View)
	ComPtr<ID3D11RenderTargetView> _renderTargetView;

	// Misc
	D3D11_VIEWPORT _viewport = { };
	float _clearColor[4] = { 1, 1, 1, 1 };
	//float _clearColor[4] = { 15.f / 255.f, 56.f / 255.f, 15.f / 255.f, 1.f };

};

