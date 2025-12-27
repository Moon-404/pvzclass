#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 在一切更新开始前的事件
	/// @note 没有参数，请用 GetBoard() 获取
	class BoardBeforeUpdateEvent : public DLLEventTemplate<0x415D40, 7>
	{
	public:
		BoardBeforeUpdateEvent(const char* str) : DLLEventTemplate() { Init(str); };
		BoardBeforeUpdateEvent(int address) : DLLEventTemplate() { Init(address); };
		BoardBeforeUpdateEvent() : DLLEventTemplate() { Init("beforeBoardUpdate"); };
	};

	/// @brief 因为游戏暂停而中止更新的事件
	/// @note 没有参数，请用 GetBoard() 获取
	class BoardPauseUpdateEvent : public DLLEventTemplate<0x415E27, 6>
	{
	public:
		BoardPauseUpdateEvent(const char* str) : DLLEventTemplate() { Init(str); };
		BoardPauseUpdateEvent(int address) : DLLEventTemplate() { Init(address); };
		BoardPauseUpdateEvent() : DLLEventTemplate() { Init("pauseBoardUpdate"); };
	};

	/// @brief 游戏正常更新结束的事件
	/// @note 没有参数，请用 GetBoard() 获取
	class BoardAfterUpdateEvent : public DLLEventTemplate<0x416076, 6>
	{
	public:
		BoardAfterUpdateEvent(const char* str) : DLLEventTemplate() { Init(str); };
		BoardAfterUpdateEvent(int address) : DLLEventTemplate() { Init(address); };
		BoardAfterUpdateEvent() : DLLEventTemplate() { Init("afterBoardUpdate"); };
	};
}
