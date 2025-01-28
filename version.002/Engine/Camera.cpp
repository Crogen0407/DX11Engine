#include "pch.h"
#include "Camera.h"
#include "Core.h"
Matrix Camera::View = Matrix::Identity;
Matrix Camera::Projection = Matrix::Identity;

Camera::Camera() : Component(ComponentType::Camera)
{
	_width = static_cast<float>(CORE->GetCoreDesc().width);
	_height = static_cast<float>(CORE->GetCoreDesc().height);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	UpdateMatrix();
}

void Camera::UpdateMatrix()
{
	/*Vec3 eyePosition = GetTransform()->GetPosition();
	Vec3 focusPosition = eyePosition + GetTransform()->GetForward();
	Vec3 upDirection = GetTransform()->GetUp();

	View = ::XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);*/

	View = GetTransform()->GetWorld().Invert();
	//Projection = ::XMMatrixOrthographicLH(8, 6, 0.3f, 100.f);
	Projection = ::XMMatrixPerspectiveFovLH(_fov, _width/_height, _near, _far);

	//if (_type == ProjectionType::Perspective)
	//{
	//}
	//else
	//{
	//	Projection = ::XMMatrixOrthographicLH(8, 6, 0.3f, 100.f);
	//}
}
