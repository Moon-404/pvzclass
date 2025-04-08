#pragma once
#include "../PVZ.h"

namespace PVZ
{
	class Widget;
	class Board;
	/// @brief 选卡界面控件
	class SeedChooserScreen : public Widget
	{
	public:
		SeedChooserScreen(int address) : Widget(address) {};
		/// @brief 每个可选的卡牌
		class ChosenSeed : public BaseClass
		{
		public:
			ChosenSeed(int address) : BaseClass(address) {};
			INT_PROPERTY(X, __get_X, __set_X, 0);
			INT_PROPERTY(Y, __get_Y, __set_Y, 4);
			T_PROPERTY(SeedType::SeedType, Type, __get_Type, __set_Type, 0x20);
			T_PROPERTY(SeedState::SeedState, State, __get_State, __set_State, 0x24);
			INT_PROPERTY(IndexInSlot, __get_IndexInSlot, __set_IndexInSlot, 0x28);
			T_PROPERTY(BOOLEAN, Refreshing, __get_Refreshing, __set_Refreshing, 0x2C);
			INT_PROPERTY(RefreshCounter, __get_RefreshCounter, __set_RefreshCounter, 0x30);
			T_PROPERTY(SeedType::SeedType, ImitaterType, __get_ImitaterType, __set_ImitaterType, 0x34);
			T_PROPERTY(BOOLEAN, CrazyDavePick, __get_CrazyDavePick, __set_CrazyDavePick, 0x38);
		};
		/// @brief 
		/// @return 
		Board GetBoard();
		ChosenSeed GetChosenSeed(int num);
		T_PROPERTY(BOOLEAN, IsViewingLawn, __get_IsViewingLawn, __set_IsViewingLawn, 0x0D38);
	};
	//若 BaseAddress 为 0，返回空指针
	SeedChooserScreen GetSeedChooserScreen();
}