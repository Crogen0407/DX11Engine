#pragma once
#include "Component.h"

enum class ProjectionType
{
	Perspective,
	Orthographic
};

class Camera : public Component
{
public:
	Camera();
	virtual ~Camera();

	virtual void Update() override;

	/*void SetProjectionType(ProjectionType type) { _type = type; }
	ProjectionType GetProjectionType() { return _type; }*/

	void UpdateMatrix();

private:
	//ProjectionType _type = ProjectionType::Orthographic;

	float _near		= 1.f;
	float _far		= 1000.f;
	float _fov		= XM_PI/4.f;
	float _width	= 0;
	float _height	= 0;

public:
	static Matrix View;
	static Matrix Projection;
};

