#include "pch.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Core.h"
#include "Mesh.h"
#include "Shader.h"
#include "RenderManager.h"

MeshRenderer::MeshRenderer() : Super(ComponentType::MeshRenderer)
{

}

MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::Update()
{
	if (_mesh == nullptr || _texture == nullptr || _shader == nullptr)
		return;

	_shader->GetSRV("Texture0")->SetResource(_texture->GetComPtr().Get());

	auto world = GetTransform()->GetWorld();
	GET_SINGLE(RenderManager)->PushTransformData(TransformDesc{world});

	UINT stride = _mesh->GetVertexBuffer()->GetStride();
	UINT offset = _mesh->GetVertexBuffer()->GetOffset();
	DEVICECONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DEVICECONTEXT->IASetVertexBuffers(0, 1, _mesh->GetVertexBuffer()->GetComPtr().GetAddressOf(), &stride, &offset);
	DEVICECONTEXT->IASetIndexBuffer(_mesh->GetIndexBuffer()->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

	_shader->DrawIndexed(0, 0, _mesh->GetIndexBuffer()->GetCount(), 0, 0);
}
