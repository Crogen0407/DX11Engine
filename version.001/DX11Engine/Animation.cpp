#include "pch.h"
#include "Animation.h"
#include "Texture.h"

Animation::Animation() : ResourceBase(ResourceType::Animation)
{

}

Animation::~Animation()
{

}

void Animation::Load(const wstring& path)
{
}

void Animation::Save(const wstring& path)
{
}

Vec2 Animation::GetTextureSize()
{
	return _texture->GetSize();
}

const Keyframe& Animation::GetKeyframe(int index)
{
	return _keyframes[index];
}

int Animation::GetKeyframeCount()
{
	return static_cast<int>(_keyframes.size());
}

void Animation::AddKeyframe(const Keyframe& keyframe)
{
	_keyframes.push_back(keyframe);
}
