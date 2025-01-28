#pragma once
#include "Component.h"
#include "Animation.h"

class Animator :
    public Component
{
public:
    Animator();
    virtual ~Animator();

    void Awake() override;
    void Update() override;

    shared_ptr<Animation> GetCurrentAnimation();
    const Keyframe& GetCurrentKeyframe();

    void SetAnimation(shared_ptr<Animation> animation) { _currentAnimation = animation; }

private:
    float _sumTime = 0.f;

    int _currentKeyframeIndex = 0;
    shared_ptr<Animation> _currentAnimation;
};

