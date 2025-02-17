#include "pch.h"
#include "Component.h"
#include "GameObject.h"

Component::Component(ComponentType type) : _type(type)
{
}

Component::~Component()
{
}

shared_ptr<Transform> Component::GetTransform()
{
	return _owner.lock()->GetTransform();
}
