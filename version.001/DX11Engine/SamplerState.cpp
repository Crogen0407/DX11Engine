#include "pch.h"
#include "SamplerState.h"

SamplerState::SamplerState(ComPtr<ID3D11Device> device)
	: _device(device)
{	
}

SamplerState::~SamplerState()
{
}

void SamplerState::Create()
{
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.MipLODBias = 0.f;
	desc.MaxAnisotropy = 2;
	desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	desc.BorderColor[0] = 1;
	desc.BorderColor[1] = 0;
	desc.BorderColor[2] = 0;
	desc.BorderColor[3] = 1;
	desc.MaxLOD = FLT_MAX;       //�Ӹ��� ��������ġ MaxLod >= MinLod�̾�� �ϸ�         
	desc.MinLOD = -FLT_MAX;      //�Ӹ��� ��������ġ 0�� �ִ��̸� ���� �������� �Ӹ� ������ ��Ÿ����

	_device->CreateSamplerState(&desc, _samplerState.GetAddressOf());

}
