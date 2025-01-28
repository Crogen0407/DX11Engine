#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Animation.h"

ResourceManager::ResourceManager(ComPtr<ID3D11Device> device)
	: _device(device)
{
}

void ResourceManager::Init()
{
	CreateDefaultTexture();
	CreateDefaultMesh();
	CreateDefaultShader();
	CreateDefaultMaterial();
	CreateDefaultAnimation();
}

void ResourceManager::CreateDefaultTexture()
{
	{
		auto texture = make_shared<Texture>(_device);
		texture->SetName(L"Player");
		texture->Create(L"Player.png");
		Add(texture->GetName(), texture);
	}

	{
		auto texture = make_shared<Texture>(_device);
		texture->SetName(L"Enemy06");
		texture->Create(L"Enemy06.png");
		Add(texture->GetName(), texture);
	}
}

void ResourceManager::CreateDefaultMesh()
{
	// Mesh
	shared_ptr<Mesh> mesh = make_shared<Mesh>(_device);
	mesh->SetName(L"Quad");
	mesh->CreateDefaultQuad();
	Add(mesh->GetName(), mesh);
}

void ResourceManager::CreateDefaultShader()
{
	auto vertexShader = std::make_shared<VertexShader>(_device);
	vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");
	auto inputLayout = std::make_shared <InputLayout>(_device);
	inputLayout->Create(VertexTextureData::descs, vertexShader->GetBlob());
	auto pixelShader = std::make_shared<PixelShader>(_device);
	pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");

	shared_ptr<Shader> shader = make_shared<Shader>();
	shader->SetName(L"Default");
	shader->_vertexShader = vertexShader;
	shader->_inputLayout = inputLayout;
	shader->_pixelShader = pixelShader;
	Add(shader->GetName(), shader);
}

void ResourceManager::CreateDefaultMaterial()
{
	shared_ptr<Material> material = make_shared<Material>();
	material->SetName(L"Default");
	material->SetShader(Get<Shader>(L"Default"));
	material->SetTexture(Get<Texture>(L"Player"));
	Add(material->GetName(), material);
}

void ResourceManager::CreateDefaultAnimation()
{
	shared_ptr<Animation> animation = make_shared<Animation>();
	animation->SetName(L"Enemy06_Idle");
	animation->SetTexture(Get<Texture>(L"Enemy06"));
	animation->SetLoop(true);

	animation->AddKeyframe(Keyframe{ {0.f, 0.f}, {32.f, 32.f}, 0.1f });
	animation->AddKeyframe(Keyframe{ {32.f, 0.f}, {32.f, 32.f}, 0.1f });
	animation->AddKeyframe(Keyframe{ {64.f, 0.f}, {32.f, 32.f}, 0.1f });
	animation->AddKeyframe(Keyframe{ {96.f, 0.f}, {32.f, 32.f}, 0.1f });
	animation->AddKeyframe(Keyframe{ {128.f, 0.f}, {32.f, 32.f}, 0.1f });

	Add(animation->GetName(), animation);

	//XML
	animation->Save(L"TestAnimation.xml");

	shared_ptr<Animation> anim2 = make_shared<Animation>();
	anim2->Load(L"TestAnimation.xml");
	int a = 0;
}
