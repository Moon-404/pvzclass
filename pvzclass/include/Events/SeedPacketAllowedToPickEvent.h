#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 判定是否允许使用该卡槽
	/// @param SeedType
	/// @return true 可以使用 false 不可以使用
	class SeedPacketAllowedToPickEvent
	{
	private:
		class Part1 : public DiversionEventTemplate<0x482E0F, 7, 0x482E31, 0x482E3C, REG_EAX>
		{
		public:
			Part1(int address) : DiversionEventTemplate() { Init(address); };
		} *p1;
		class Part2 : public DiversionEventTemplate<0x482F5E, 5, 0x482F79, 0x482FA8, REG_ESI>
		{
		public:
			Part2(int address) : DiversionEventTemplate() { Init(address); };
		} *p2;
		class Part3 : public DiversionEventTemplate<0x4830F6, 9, 0x48311B, 0x483103, REG_EBP>
		{
		public:
			Part3(int address) : DiversionEventTemplate() { Init(address); };
		} *p3;
		class Part4 : public DiversionEventTemplate<0x48329F, 7, 0x4832D5, 0x483369, REG_EAX>
		{
		public:
			Part4(int address) : DiversionEventTemplate() { Init(address); };
		} *p4;
		class Part5 : public DiversionEventTemplate<0x484018, 7, 0x48403A, 0x48407B, REG_ESI>
		{
		public:
			Part5(int address) : DiversionEventTemplate() { Init(address); };
		} *p5;
		class Part6 : public DiversionEventTemplate<0x484A32, 7, 0x484A5A, 0x484A54, REG_ESI>
		{
		public:
			Part6(int address) : DiversionEventTemplate() { Init(address); };
		} *p6;
		class Part7 : public DiversionEventTemplate<0x4850F4, 7, 0x485181, 0x48510A, REG_EAX>
		{
		public:
			Part7(int address) : DiversionEventTemplate() { Init(address); };
		} *p7;
		class Part8 : public DiversionEventTemplate<0x486372, 9, 0x4863AD, 0x48637F, REG_EDI>
		{
		public:
			Part8(int address) : DiversionEventTemplate() { Init(address); };
		} *p8;
		class Part9 : public DiversionEventTemplate<0x486B81, 7, 0x486BB7, 0x486CC5, REG_EBX>
		{
		public:
			Part9(int address) : DiversionEventTemplate() { Init(address); };
		} *p9;
	public:
		SeedPacketAllowedToPickEvent() : SeedPacketAllowedToPickEvent("onSeedPacketAllowedToPick") {};
		SeedPacketAllowedToPickEvent(const char* name) : SeedPacketAllowedToPickEvent(PVZ::Memory::GetProcAddress(name)) {};
		SeedPacketAllowedToPickEvent(int address)
		{
			p1 = new Part1(address);
			p2 = new Part2(address);
			p3 = new Part3(address);
			p4 = new Part4(address);
			p5 = new Part5(address);
			p6 = new Part6(address);
			p7 = new Part7(address);
			p8 = new Part8(address);
			p9 = new Part9(address);
		}
		void end()
		{
			p1->end();
			p2->end();
			p3->end();
			p4->end();
			p5->end();
			p6->end();
			p7->end();
			p8->end();
			p9->end();
		}
	};
}
