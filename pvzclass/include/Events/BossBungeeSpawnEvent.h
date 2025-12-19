#pragma once
#include "DLLEvent.h"

// 僵王生成蹦极事件
// 参数：僵王博士
// 无返回值
// 覆盖原来的蹦极生成代码，未对僵王状态进行修改
// 会覆盖额外代码，end不可用
class BossBungeeSpawnEvent : public DLLEvent
{
public:
	BossBungeeSpawnEvent()
	{
		int procAddress = PVZ::Memory::GetProcAddress("onBossBungeeSpawn");
		hookAddress = 0x535204;
		rawlen = 5;
		BYTE code0[] = { NOP, NOP, NOP, NOP, NOP };
		PVZ::Memory::WriteArray<BYTE>(hookAddress, STRING(code0));
		BYTE code1[] = { PUSH_EAX, INVOKE(procAddress), ADD_ESP(4) };
		start(STRING(code1));
		BYTE code2[] = { JMPFAR(0x8E) };
		PVZ::Memory::WriteArray<BYTE>(0x535209, STRING(code2));
	}
};