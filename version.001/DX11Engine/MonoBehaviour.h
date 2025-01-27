#pragma once
#include "Component.h"
class MonoBehaviour : public Component
{
public:
	MonoBehaviour();
	~MonoBehaviour();

	virtual void Awake() override;
	virtual void Update() override;
};

