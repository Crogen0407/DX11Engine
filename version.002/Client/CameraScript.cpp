#include "pch.h"
#include "CameraScript.h"
#include "InputManager.h"

void CameraScript::Start()
{
}

void CameraScript::Update()
{
	Vec3 pos = GetTransform()->GetPosition();
	
	if (GET_BUTTON(KEY_TYPE::W))
		pos += GetTransform()->GetForward() * _speed * DELTA_TIME;
	if (GET_BUTTON(KEY_TYPE::S))
		pos -= GetTransform()->GetForward() * _speed * DELTA_TIME;
	if (GET_BUTTON(KEY_TYPE::A))
		pos -= GetTransform()->GetRight() * _speed * DELTA_TIME;
	if (GET_BUTTON(KEY_TYPE::D))
		pos += GetTransform()->GetRight() * _speed * DELTA_TIME;

	GetTransform()->SetPosition(pos);
}
	