#pragma once
class Texture;
class Shader;
class Material;
class Animation;
class Mesh;
class ResourceManager
{
public:
	ResourceManager(ComPtr<ID3D11Device> device);

	void Init();

	template<typename T>
	shared_ptr<T> Load(const wstring& key, const wstring& path);

	template<typename T>
	bool Add(const wstring& key, shared_ptr<T> object);

	template<typename T>
	shared_ptr<T> Get(const wstring& key);

	template<typename T>
	ResourceType GetResourceType();

private:
	void CreateDefaultTexture();
	void CreateDefaultMesh();
	void CreateDefaultShader();
	void CreateDefaultMaterial();
	void CreateDefaultAnimation();

private:
	ComPtr<ID3D11Device> _device;

	using KeyObjMap = map<wstring, shared_ptr<ResourceBase>>;

	array<KeyObjMap, RESOURCE_TYPE_COUNT> _resources;
};

template<typename T>
inline shared_ptr<T> ResourceManager::Load(const wstring& key, const wstring& path)
{
	auto objectType = GetResourceType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<UINT>(objectType)];

	auto findIter = keyObjMap.find(key);
	if (findIter != keyObjMap.end())
		return static_pointer_cast<T>(findIter->second);

	shared_ptr<T> object = make_shared<T>();
	object->Load(path);
	keyObjMap[key] = object;

	return object;
}

template<typename T>
inline bool ResourceManager::Add(const wstring& key, shared_ptr<T> object)
{
	ResourceType resourceType = GetResourceType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<UINT>(resourceType)];

	auto findIter = keyObjMap.find(key);
	if (findIter != keyObjMap.end())
		return false;

	keyObjMap[key] = object;

	return true;
}

template<typename T>
inline shared_ptr<T> ResourceManager::Get(const wstring& key)
{
	ResourceType resourceType = GetResourceType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<UINT>(resourceType)];

	auto findIter = keyObjMap.find(key);
	if (findIter != keyObjMap.end())
		return static_pointer_cast<T>(findIter->second);

	return nullptr;
}

template<typename T>
inline ResourceType ResourceManager::GetResourceType()
{
	if (std::is_same<T, Mesh>())
		return ResourceType::Mesh;
	if (std::is_same<T, Material>())
		return ResourceType::Material;
	if (std::is_same<T, Shader>())
		return ResourceType::Shader;
	if (std::is_same<T, Animation>())
		return ResourceType::Animation;
	if (std::is_same<T, Texture>())
		return ResourceType::Texture;

	assert(false);
	return ResourceType::None;
}
