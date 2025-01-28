#include "pch.h"
#include "Camera.h"

Matrix Camera::View = Matrix::Identity;
Matrix Camera::Projection = Matrix::Identity;

Camera::Camera() : Component(ComponentType::Camera)
{
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
	Projection = ::XMMatrixPerspectiveFovLH(_fov, _width/_height, _near, _far);

	//if (_type == ProjectionType::Perspective)
	//{
	//}
	//else
	//{
	//	Projection = ::XMMatrixOrthographicLH(8, 6, 0.3f, 100.f);
	//}
}
