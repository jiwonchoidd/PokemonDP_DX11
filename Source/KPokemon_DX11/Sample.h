#pragma once
#define IP_DD		"192.168.0.56"
#define IP_KGCA2	"192.168.0.12"
#include "KCore.h"
#include "KSceneManager.h"
class Sample : public KCore
{
public:
	bool		Init()override;
	bool		Frame()override;
	bool		Render()override;
	bool		Release()override;
public:
	Sample();
	virtual ~Sample();
};

