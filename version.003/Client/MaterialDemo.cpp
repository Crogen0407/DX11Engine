#include "pch.h"
#include "MaterialDemo.h"
#include "GeometryHelper.h"
#include "InputManager.h"
#include "Camera.h"
#include "GameObject.h"
#include "CameraScript.h"
#include "ResourceManager.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "RenderManager.h"
#include "Material.h"

void MaterialDemo::Init()
{
	_shader = make_shared<Shader>(L"Lighting.fx");
	GET_SINGLE(ResourceManager)->Init();

	// Material
	{
		shared_ptr<Material> material = make_shared<Material>();
		{
			material->SetShader(_shader);
		}
		{
			auto texture = GET_SINGLE(ResourceManager)->Load<Texture>(L"Player", L"..\\Resources\\Textures\\Player.png");
			material->SetDiffuseMap(texture);
		}

		MaterialDesc& desc = material->GetMaterialDesc();
		desc.ambient = Vec4(1.f);
		desc.diffuse = Vec4(1.f);

		GET_SINGLE(ResourceManager)->Add(L"Player", material);
	}

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform()->SetPosition({0, 0, -10});
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());

	// Object
	_obj = make_shared<GameObject>();
	_obj->GetOrAddTransform()->SetPosition({1, 0, 0});
	_obj->AddComponent(make_shared<MeshRenderer>());
	{
		auto meshRenderer = static_pointer_cast<MeshRenderer>(_obj->GetFixedComponent(ComponentType::MeshRenderer));
		auto mesh = GET_SINGLE(ResourceManager)->Get<Mesh>(L"Sphere");
		meshRenderer->SetMesh(mesh);

		auto material = GET_SINGLE(ResourceManager)->Get<Material>(L"Player");
		meshRenderer->SetMaterial(material);
	}

	_obj2 = make_shared<GameObject>();
	_obj2->GetOrAddTransform()->SetPosition({0, 0, 2});
	_obj2->AddComponent(make_shared<MeshRenderer>());
	{
		auto meshRenderer = static_pointer_cast<MeshRenderer>(_obj2->GetFixedComponent(ComponentType::MeshRenderer));
		auto mesh = GET_SINGLE(ResourceManager)->Get<Mesh>(L"Cube");
		meshRenderer->SetMesh(mesh);

		auto material = GET_SINGLE(ResourceManager)->Get<Material>(L"Player")->Clone();
		MaterialDesc& desc = material->GetMaterialDesc();
		desc.ambient = Vec4(.0f);
		desc.diffuse = Vec4(.0f);

		meshRenderer->SetMaterial(material);
	}

	GET_SINGLE(RenderManager)->Init(_shader);
}

void MaterialDemo::Update()
{
	_camera->Update();

	GET_SINGLE(RenderManager)->Update();

	{
		LightDesc desc;
		desc.ambient = Vec4(0.5f);
		desc.diffuse = Vec4(1.f);
		desc.specular = Vec4(1.f);
		desc.direction = Vec3(1.f, -1.f, 0.f);
		GET_SINGLE(RenderManager)->PushLightData(desc);
	}

	{
		MaterialDesc desc;
		desc.ambient = Vec4(1.f);
		desc.diffuse = Vec4(.4f);
		desc.specular = Vec4(1.f);
		desc.emissive = Vec4(1.0f);
		GET_SINGLE(RenderManager)->PushMaterialData(desc);
		_obj->Update();
	}

	{
		MaterialDesc desc;
		desc.ambient = Vec4(0.2f);
		desc.diffuse = Vec4(1.f);
		desc.specular = Vec4(1.f);
		desc.emissive = Vec4(1.f);
		GET_SINGLE(RenderManager)->PushMaterialData(desc);
		_obj2->Update();
	}
}

void MaterialDemo::Render()
{
	
}
