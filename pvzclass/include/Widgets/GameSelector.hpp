#pragma once
#include "../../PVZ.h"

namespace PVZ
{
	/// @brief 主菜单界面
	class GameSelector : public Widget
	{
	public:
		GameSelector(int address) : Widget(address) {};

		/// @brief 调整该类在 PVZ 中对象的大小。
		/// @note 请在派生类中调用这个函数。
		/// @note 额外的空间未经初始化，使用前请设法初始化。
		/// @param MemSize 更改后的大小。
		static void SetMemSize(uint32_t NewSize);
	};

	/// @brief 获取主菜单界面
	GameSelector GetGameSelector();
}
