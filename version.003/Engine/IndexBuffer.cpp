#include "pch.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer()
{

}

IndexBuffer::~IndexBuffer()
{

}

void IndexBuffer::Create(const vector<UINT>& indices)
{
	_stride = sizeof(UINT);
	_count = static_cast<UINT>(indices.size());

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.ByteWidth = (UINT)(_stride * _count);

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = indices.data();

	HRESULT hr = DEVICE->CreateBuffer(&desc, &data, _indexBuffer.GetAddressOf());
	CHECK(hr);
}
