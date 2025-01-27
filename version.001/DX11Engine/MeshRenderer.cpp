#include "pch.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Core.h"
#include "Mesh.h"

MeshRenderer::MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
	: Component(ComponentType::MeshRenderer), _device(device)
{
}

MeshRenderer::~MeshRenderer()
{
}