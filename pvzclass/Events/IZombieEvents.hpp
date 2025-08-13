#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief IZE 关主题植物初始化事件
	/// @param 触发事件的 Challenge
	/// @return 是否初始化植物
	class IZESetupThemeEvent : public BoolDLLEventTemplate<0x42B041, 5, 0x42B277, REG_EDI>
	{
	public:
		IZESetupThemeEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		IZESetupThemeEvent(const char* name) : BoolDLLEventTemplate() { Init(name); };
		IZESetupThemeEvent() : IZESetupThemeEvent("onIZESetupTheme") {};
	};

	/// @brief 判断当前关卡是否为 IZ 关卡的事件
	/// @param 触发事件的 PVZApp
	/// @return 若为负数，则按原版处理；若为 0，则为非 IZ 关卡；若为正数，则为 IZ 关卡。
	class IsIZEvent
	{
	private:
		class Part1 : public IntDLLEventTemplate<0x4537DC, 6, 0, 0, 0, REG_EAX, true, REG_EAX>
		{
		public:
			Part1(int address) : IntDLLEventTemplate() { Init(address); };
		} *part1;
		class Part2 : public DLLEventTemplate<0x41F5AB, 6, REG_EAX>
		{
		public:
			Part2(int address) : DLLEventTemplate() { Init(address); };
			virtual void InitExtra(AsmBuilder& builder)
			{
				builder.test_al_al().js_rel(16).je_rel(7);
				builder.popad().push_imm32(0x41F5E3).ret();
				builder.popad().push_imm32(0x41F5E9).ret();
			}
		} *part2;
		class Part3 : public DLLEventTemplate<0x4200D6, 6, REG_EAX>
		{
		public:
			Part3(int address) : DLLEventTemplate() { Init(address); };
			virtual void InitExtra(AsmBuilder& builder)
			{
				builder.test_al_al().js_rel(20).je_rel(7);
				builder.popad().push_imm32(0x42010E).ret();
				builder.popad().push_imm32(0x420114).ret();
			}
		} *part3;
		class Part4 : public ThreeStateEventTemplate<0x461E81, 6, 0x461EB9, 0x461F07, REG_ECX>
		{
		public:
			Part4(int address) : ThreeStateEventTemplate() { Init(address); };
		} *part4;
	public:
		IsIZEvent() : IsIZEvent("IsIZ") {};
		IsIZEvent(const char* name) : IsIZEvent(PVZ::Memory::GetProcAddress(name)) {};
		IsIZEvent(int address)
		{
			part1 = new Part1(address);
			part2 = new Part2(address);
			part3 = new Part3(address);
			part4 = new Part4(address);
		}
		void end()
		{
			part1->end();
			part2->end();
			part3->end();
			part4->end();
		}
	};
}
