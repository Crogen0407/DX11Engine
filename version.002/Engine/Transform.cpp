#include "pch.h"
#include "Transform.h"
#include "GameObject.h"

Transform::Transform() : Component(ComponentType::Transform)
{
}

Transform::~Transform()
{
}

void Transform::Awake()
{

}

Vec3 ToEulerAngles(Quaternion q) 
{
	Vec3 angles;

	// roll (x-axis rotation)
	double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
	double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
	angles.x = std::atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	double sinp = std::sqrt(1 + 2 * (q.w * q.y - q.x * q.z));
	double cosp = std::sqrt(1 - 2 * (q.w * q.y - q.x * q.z));
	angles.y = 2 * std::atan2(sinp, cosp) - XM_PI / 2;

	// yaw (z-axis rotation)
	double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
	double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
	angles.z = std::atan2(siny_cosp, cosy_cosp);

	return angles;
}

void Transform::Update()
{
	Matrix scale = Matrix::CreateScale(_localScale);
	Matrix rotation = Matrix::CreateRotationX(_localRotation.x);
	rotation *= Matrix::CreateRotationY(_localRotation.y);
	rotation *= Matrix::CreateRotationZ(_localRotation.z);
	Matrix translation = Matrix::CreateTranslation(_localPosition);

	_local = scale * rotation * translation; 

	if (HasParent())
	{
		_world = _local * _parent->GetWorld();
	}
	else
	{
		_world = _local;
	}

	Quaternion quat;
	_world.Decompose(_scale, quat, _position);
	_rotation = ToEulerAngles(quat);

	// Children
	for (const shared_ptr<Transform>& child : _children)
		child->Update();
}

void Transform::SetScale(const Vec3& scale)
{
	if (HasParent())
	{
		Vec3 parentScale = _parent->GetScale();
		Vec3 selfScale = scale;
		selfScale.x /= parentScale.x;
		selfScale.y /= parentScale.y;
		selfScale.z /= parentScale.z;
		SetLocalScale(selfScale);
	}
	else
		SetLocalScale(scale);
}

void Transform::SetRotation(const Vec3& rotation)
{
	if (HasParent())
	{
		Matrix inverseMatrix = _parent->GetWorld().Invert();

		Vec3 selfRotation;
		selfRotation.TransformNormal(rotation, inverseMatrix);

		SetLocalPosition(selfRotation);
	}
	else
		SetLocalRotation(rotation);
}

void Transform::SetPosition(const Vec3& position)
{
	if (HasParent())
	{
		Matrix worldToParentLocalMatrix = _parent->GetWorld().Invert();
		
		Vec3 selfPosition;
		selfPosition.Transform(position, worldToParentLocalMatrix);

		SetLocalPosition(selfPosition);
	}
	else
		SetLocalPosition(position);
}