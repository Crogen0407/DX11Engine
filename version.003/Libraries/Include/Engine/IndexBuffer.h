#pragma once

class IndexBuffer
{
public:
	IndexBuffer();
	~IndexBuffer();

	ComPtr<ID3D11Buffer> GetComPtr() { return _indexBuffer; }
	UINT GetStride() { return _stride; }
	UINT GetOffset() { return _offset; }
	UINT GetCount() { return _count; }

	void Create(const vector<UINT>& indices);

private:
	ComPtr<ID3D11Buffer> _indexBuffer;

	UINT _stride = 0;
	UINT _offset = 0;
	UINT _count = 0;
};

