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

	if (_type == ProjectionType::Perspective)
	{
		Projection = ::XMMatrixPerspectiveFovLH(PI / 4.f, static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT), 0.3f, 100.f);
	}
	else
	{
		Projection = ::XMMatrixOrthographicLH(8, 6, 0.3f, 100.f);
	}
}
