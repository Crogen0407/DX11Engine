#pragma once
class GameObject;
class Transform;

enum class ComponentType : UINT
{
	Transform,
	MeshRenderer,
	Camera,
	Animator,
	Script,
	End
};

enum
{
	FIXED_COMPONENT_COUNT = static_cast<UINT>(ComponentType::End) - 1
};

class Component
{
public:
	Component(ComponentType type);
	virtual ~Component();

	virtual void Awake() { }
	virtual void Start() { }
	virtual void FixedUpdate() { }
	virtual void Update() { }
	virtual void LateUpdate() { }

public:
	ComponentType GetType() { return _type; }

	shared_ptr<GameObject> GetOwner() { return _owner.lock(); }
	shared_ptr<Transform> GetTransform();
private:
	friend class GameObject;
	void SetOwner(shared_ptr<GameObject> owner) { _owner = owner; }

protected:
	ComponentType _type;
	weak_ptr<GameObject> _owner;
};

