#pragma once
#include "../../Events/DLLEvent.h"

namespace PVZEvent
{
	/// @brief 僵尸检查下水上岸事件
	/// @param 触发事件的 Zombie
	/// @note 潜水僵尸和海豚僵尸有自己的下水结算流程。原版中它们不会通过检查。
	/// @return 由 ThreeState::ThreeState 表示的，是否检查下水上岸。
	class ZombieCheckForPoolEvent : public DLLEventTemplate<0x52F876, 5, REG_EBP>
	{
	public:
		ZombieCheckForPoolEvent(int address) : DLLEventTemplate() { Init(address); };
		ZombieCheckForPoolEvent(const char* name) : DLLEventTemplate() { Init(name); };
		ZombieCheckForPoolEvent() : ZombieCheckForPoolEvent("onZombieCheckForPool") {};

		static constexpr std::array<uint8_t, 21> compiled_special_bytes =
		{
			TEST_AL_AL,
			JS(17),
			POPAD,
			PUSH_ESI,
			PUSH_EDI,
			JE(6),

			PUSHDWORD(0x52F8F6),
			RET,

			PUSHDWORD(0x52F9AA),
			RET
		};
		virtual void InitExtra(AsmBuilder& builder)
		{
			builder.add_bytes(compiled_special_bytes.data(), 21);
		}
	};
}
