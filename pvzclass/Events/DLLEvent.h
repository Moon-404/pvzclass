#pragma once
#include "../PVZ.h"
#include <array>
#include <iostream>

using std::cout;
using std::hex;
using std::endl;

class DLLEvent
{
public:
	void end();

protected:
	int rawlen, hookAddress;
	void start(BYTE* code, int len);

private:
	BYTE* rawCode;
	static int newAddress;
};

int DLLEvent::newAddress = 0;

void DLLEvent::start(BYTE* code, int newlen)
{
	if (newAddress == 0) newAddress = PVZ::Memory::AllocMemory();
	rawCode = new BYTE[rawlen];
	PVZ::Memory::ReadArray<BYTE>(hookAddress, rawCode, rawlen);
	BYTE jmpto[] = { JMPFAR(newAddress - (hookAddress + 5)) };
	PVZ::Memory::WriteArray<BYTE>(hookAddress, jmpto, 5);
	for (int i = 5; i < rawlen; i++) PVZ::Memory::WriteMemory<BYTE>(hookAddress + i, NOP);
	BYTE jmpback[] = { JMPFAR(hookAddress - (newAddress + newlen + 7)) };
	PVZ::Memory::WriteMemory<BYTE>(newAddress, PUSHAD);
	PVZ::Memory::WriteArray<BYTE>(newAddress + 1, code, newlen);
	PVZ::Memory::WriteMemory<BYTE>(newAddress + newlen + 1, POPAD);
	PVZ::Memory::WriteArray<BYTE>(newAddress + newlen + 2, rawCode, rawlen);
	PVZ::Memory::WriteArray<BYTE>(newAddress + newlen + rawlen + 2, jmpback, 5);
	newAddress += newlen + rawlen + 0x10;
}

void DLLEvent::end()
{
	PVZ::Memory::WriteArray<BYTE>(hookAddress, rawCode, rawlen);
	PVZ::Memory::FreeMemory(newAddress);
}

template<DWORD _Hook_Address, DWORD _Raw_Len, uint8_t ...Regs>
class DLLEventTemplate : DLLEvent
{
protected:
	void Init(int proc_address);
	void InitExtra(AsmBuilder& builder)
	{
		return;
	}
public:
	static constexpr std::array<uint8_t, sizeof...(Regs)> regs = { Regs... };
};

template<DWORD _Hook_Address, DWORD _Raw_Len, uint8_t ...Regs>
inline void DLLEventTemplate<_Hook_Address, _Raw_Len, Regs...>::Init(int proc_address)
{
	hookAddress = _Hook_Address;
	rawlen = _Raw_Len;
	AsmBuilder builder = AsmBuilder(128);

	for (int i = 0, sz = this->regs.size(); i < sz; i++)
		if (this->regs[i] < 8)
			builder.push_reg(this->regs[i]);
		else
			builder.push_m32_esp_imm8(this->regs[i]);

	builder.invoke(proc_address).add_reg_imm(REG_ESP, this->regs.size() << 2);
	this->InitExtra(builder);
	
	start(builder.get_code() + 1, builder.get_length() - 1);
}
