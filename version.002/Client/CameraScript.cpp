#include "pch.h"
#include "CameraScript.h"
#include "InputManager.h"

void CameraScript::Start()
{
	lastMousePos = GET_MOUSEPOS;
}

void CameraScript::Update()
{
	float mouseDeltaX = GET_MOUSEPOS.x-lastMousePos.x;

	Vec3 pos = GetTransform()->GetPosition();
	
	if (GET_BUTTON(KEY_TYPE::W))
		pos += GetTransform()->GetForward() * _speed * DELTA_TIME;
	if (GET_BUTTON(KEY_TYPE::S))
		pos -= GetTransform()->GetForward() * _speed * DELTA_TIME;
	if (GET_BUTTON(KEY_TYPE::A))
		pos -= GetTransform()->GetRight() * _speed * DELTA_TIME;
	if (GET_BUTTON(KEY_TYPE::D))
		pos += GetTransform()->GetRight() * _speed * DELTA_TIME;

	if (GET_BUTTON(KEY_TYPE::Q))
		pos += GetTransform()->GetUp() * _speed * DELTA_TIME;
	if (GET_BUTTON(KEY_TYPE::E))
		pos -= GetTransform()->GetUp() * _speed * DELTA_TIME;

	//GetTransform()->AddRotation(GetTransform()->GetUp()*mouseDeltaX * DELTA_TIME * 0.1f);
	//GetTransform()->AddRotation(GetTransform()->GetUp() * pos.y);

	GetTransform()->SetPosition(pos);

	lastMousePos = GET_MOUSEPOS;
}
	