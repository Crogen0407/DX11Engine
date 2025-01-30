#pragma once
class MonoBehaviour;
#include "Component.h"
class GameObject : public enable_shared_from_this<GameObject>
{
public:
	GameObject();
	virtual ~GameObject();

	void Awake();
	void Start();
	void FixedUpdate();
	void Update();
	void LateUpdate();

	shared_ptr<Component> GetFixedComponent(ComponentType type);
	shared_ptr<Transform> GetTransform();
	shared_ptr<Transform> GetOrAddTransform();
	void AddComponent(shared_ptr<Component> component);

private:
	ComPtr<ID3D11Device> _device;

protected:
	std::array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> _components;
	vector<shared_ptr<MonoBehaviour>> _scripts;
};

