#include "System.h"

#include <sstream>
#include <iomanip>

System::System()
	:
	wnd(800,600,"Fuck Box!")
{}

int System::Run()
{

	while (true)
	{
		if (const auto ecode = ShadowWindow::ProcessMessages())
		{
			return *ecode;
		}

		StartFrame();
	}
}

void System::StartFrame()
{
	const float t = timer.Peek();
	std::ostringstream oss;
	oss << "Time elapsed: " << std::setprecision(1) << std::fixed << t << "s";
	wnd.SetTitle(oss.str());
}
