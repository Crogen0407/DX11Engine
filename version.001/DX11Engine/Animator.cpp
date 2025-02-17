#include "pch.h"
#include "Animator.h"
#include "TimeManager.h"

Animator::Animator() : Component(ComponentType::Animator)
{
}

Animator::~Animator()
{
}

void Animator::Awake()
{
}

void Animator::Update()
{
	shared_ptr<Animation> animation = GetCurrentAnimation();
	if (animation == nullptr) return;

	const Keyframe& keyframe = animation->GetKeyframe(_currentKeyframeIndex);
	_sumTime += DELTA_TIME;

	if (_sumTime > keyframe.time)
	{
		_currentKeyframeIndex++;
		int totalCount = animation->GetKeyframeCount();
		
		if (_currentKeyframeIndex >= totalCount)
		{
			if (animation->IsLoop())
				_currentKeyframeIndex = 0;
			else
				_currentKeyframeIndex = totalCount - 1;
		}

		_sumTime = 0.f;
	}
}

shared_ptr<Animation> Animator::GetCurrentAnimation()
{
	return _currentAnimation;
}

const Keyframe& Animator::GetCurrentKeyframe()
{
	return _currentAnimation->GetKeyframe(_currentKeyframeIndex);
}
