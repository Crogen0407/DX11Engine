#pragma once

enum class ResourceType : UINT
{
	None = -1,
	Mesh,
	Shader,
	Texture,
	Material,
	Animation,

	End
};

enum
{
	RESOURCE_TYPE_COUNT = static_cast<UINT>(ResourceType::End)
};

class ResourceBase : public enable_shared_from_this<ResourceBase>
{
public:
	ResourceBase(ResourceType type);
	virtual ~ResourceBase();

	ResourceType GetType() { return _type; }

	void SetName(const wstring& name) { _name = name; }
	const wstring& GetName() { return _name; }
	UINT GetID() { return _id; }

protected:
	virtual void Load(const wstring& path) { }
	virtual void Save(const wstring& path) { }

protected:
	ResourceType _type = ResourceType::None;
	wstring _name;
	wstring _path;
	UINT _id = 0;
};

