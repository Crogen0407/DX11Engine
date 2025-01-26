#pragma once

class VertexBuffer
{
public:
	VertexBuffer(ComPtr<ID3D11Device> device);
	~VertexBuffer();

	ComPtr<ID3D11Buffer> GetComPtr() { return _vertexBuffer; }
	UINT GetStride() { return _stride; }
	UINT GetOffest() { return _offset; }
	UINT GetCount() { return _count; }

	template<typename T>
	void Create(const vector<T>& vertices)
	{
		_stride = sizeof(T);
		_count = static_cast<UINT>(vertices.size());

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_IMMUTABLE; // �ش� ���۸� CPU�� GPU�� ������ �� �ִ����� ���θ� �����ش�
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // ���ؽ� ���۸� ����� �� ����� ���̴�
		desc.ByteWidth = (UINT)(_stride * _count);

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = vertices.data();

		HRESULT hr = _device->CreateBuffer(&desc, &data, _vertexBuffer.GetAddressOf());
		CHECK(hr);
	}


private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11Buffer> _vertexBuffer = nullptr;
	
	UINT _stride = 0;
	UINT _offset = 0;
	UINT _count = 0;
};

