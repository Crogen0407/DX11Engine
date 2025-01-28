#pragma once

#define DECLARE_SINGLE(className)		\
private:								\
	className() {}						\
public:									\
	static className* GetInstance()		\
	{									\
		static className instance;		\
		return &instance;				\
	}									\

#define GET_SINGLE(className)	className::GetInstance()
