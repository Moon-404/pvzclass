#pragma once
#include "../PVZ.h"

namespace PVZ
{
	class PVZApp;
	class Widget;
	//选关界面。
	class ChallengeScreen : public Widget
	{
	public:
		ChallengeScreen(int address) : Widget(address) {};
		PVZApp GetPVZApp();
		PROPERTY(ChallengePage::ChallengePage, __get_Page, __set_Page) Page;
	};
	ChallengeScreen GetChallengeScreen();
}