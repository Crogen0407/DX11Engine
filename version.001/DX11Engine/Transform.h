#pragma once
#include "Component.h"

class Transform : public Component
{
public:
	Transform();
	~Transform();

	virtual void Awake() override;
	virtual void Update() override;

	//Local
	Vec3 GetLocalScale() { return _localScale; }
	void SetLocalScale(const Vec3& localScale) { _localScale = localScale; Update(); }
	void AddLocalScale(const Vec3& localScale) { _localScale += localScale; Update(); }

	Vec3 GetLocalRotation() { return _localRotation; }
	void SetLocalRotation(const Vec3& localRotation) { _localRotation = localRotation; Update(); }
	void AddLocalRotation(const Vec3& localRotation) { _localRotation += localRotation; Update(); }

	Vec3 GetLocalPosition() { return _localPosition; }
	void SetLocalPosition(const Vec3& localPosition) { _localPosition = localPosition; Update(); }
	void AddLocalPosition(const Vec3& localPosition) { _localPosition += localPosition; Update(); }


	//World
	Vec3 GetScale() { return _scale; }
	void SetScale(const Vec3& scale);
	void AddScale(const Vec3& scale) { SetScale(GetScale() + scale); }

	Vec3 GetRotation() { return _rotation; }
	void SetRotation(const Vec3& rotation);
	void AddRotation(const Vec3& rotation) { SetRotation(GetRotation() + rotation); }

	Vec3 GetPosition() { return _position; }
	void SetPosition(const Vec3& position);
	void AddPosition(const Vec3& position) { SetPosition(GetPosition() + position); }

	Vec3 GetRight() { return _world.Right(); }
	Vec3 GetUp() { return _world.Up(); }
	Vec3 GetForward() { return _world.Backward(); }


	Matrix GetWorld() { return _world; }

	// °èÃþ °ü°è
	bool HasParent() { return _parent != nullptr; }

	shared_ptr<Transform> GetParent() { return _parent; }
	void SetParent(shared_ptr<Transform> parent) { _parent = parent; }

	const vector<shared_ptr<Transform>>& GetChildren() { return _children; }
	void AddChild(shared_ptr<Transform>& child) { _children.push_back(child); }

private:
	Vec3 _localScale = { 1.f, 1.f, 1.f };
	Vec3 _localRotation = { 0.f, 0.f, 0.f };
	Vec3 _localPosition = { 0.f, 0.f, 0.f };

	Matrix _local = Matrix::Identity;
	Matrix _world = Matrix::Identity;

	Vec3 _scale = { 1.f, 1.f, 1.f };
	Vec3 _rotation = { 0.f, 0.f, 0.f };
	Vec3 _position = { 0.f, 0.f, 0.f };

private:
	shared_ptr<Transform> _parent;
	vector<shared_ptr<Transform>> _children;
};

