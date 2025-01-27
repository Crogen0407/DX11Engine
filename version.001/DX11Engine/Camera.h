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

	void SetProjectionType(ProjectionType type) { _type = type; }
	ProjectionType GetProjectionType() { return _type; }

	void UpdateMatrix();

private:
	ProjectionType _type = ProjectionType::Orthographic;

public:
	static Matrix View;
	static Matrix Projection;
};

