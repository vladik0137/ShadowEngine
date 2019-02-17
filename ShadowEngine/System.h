#pragma once

#include "ShadowWindow.h"
#include "GameTimer.h"

class System
{
public:
	System();
	int Run();
private:
	void StartFrame();
private:
	ShadowWindow wnd;
	GameTimer timer;
};