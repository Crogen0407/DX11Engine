#include "pch.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Core.h"
#include "Mesh.h"
#include "Shader.h"

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

	auto world = GetTransform()->GetWorld();
	_shader->GetMatrix("World")->SetMatrix((float*)&world);
	
	_shader->GetMatrix("View")->SetMatrix((float*)&Camera::View);
	_shader->GetMatrix("Projection")->SetMatrix((float*)&Camera::Projection);
	_shader->GetSRV("Texture0")->SetResource(_texture->GetComPtr().Get());
	
	// TEMP
	Vec3 lightDir = {0.f, 0.f, 1.f};
	_shader->GetVector("LightDir")->SetFloatVector((float*)&lightDir);

	UINT stride = _mesh->GetVertexBuffer()->GetStride();
	UINT offset = _mesh->GetVertexBuffer()->GetOffset();
	DEVICECONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DEVICECONTEXT->IASetVertexBuffers(0, 1, _mesh->GetVertexBuffer()->GetComPtr().GetAddressOf(), &stride, &offset);
	DEVICECONTEXT->IASetIndexBuffer(_mesh->GetIndexBuffer()->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

	_shader->DrawIndexed(0, 0, _mesh->GetIndexBuffer()->GetCount(), 0, 0);
}
