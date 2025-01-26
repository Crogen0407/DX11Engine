#pragma once
class GameObject
{
public:
	GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	virtual ~GameObject();

public:
	virtual void Update();
	virtual void Render(std::shared_ptr<Pipeline> pipeline);

private:
	ComPtr<ID3D11Device> _device;

	std::shared_ptr<Geometry<VertexTextureData>> _geometry;

	std::shared_ptr<VertexBuffer> _vertexBuffer;
	std::shared_ptr<IndexBuffer> _indexBuffer;
	std::shared_ptr<InputLayout> _inputLayout;

	std::shared_ptr<VertexShader> _vertexShader;
	std::shared_ptr<RasterizerState> _rasterizerState = nullptr;
	std::shared_ptr<PixelShader> _pixelShader;
	std::shared_ptr<Texture> _texture;
	std::shared_ptr<SamplerState> _samplerState = nullptr;
	std::shared_ptr<BlendState> _blendState = nullptr;

private:
	TransformData _transformData;
	std::shared_ptr<ConstantBuffer<TransformData>> _constantBuffer;

	shared_ptr<Transform> _transform = make_shared<Transform>();
};

