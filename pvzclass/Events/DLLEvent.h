#pragma once
#include "../PVZ.h"
#include <array>
#include <iostream>

#define MEM_ESP_ADD_MASK 8
#define MEM_ESP_ADD(offset) (offset)
#define CONST_VAL_MASK 0x0FF
#define CONST_VAL(v) (CONST_VAL_MASK + (v))

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
	if (rawCode[0] == 0xE8 || rawCode[0] == 0xE9)
		SETARG(rawCode, 1) = SETARG(rawCode, 1) + hookAddress - newAddress - newlen - 2;
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

template<DWORD _Hook_Address, DWORD _Raw_Len, DWORD ...Params>
class DLLEventTemplate : public DLLEvent
{
protected:
	void Init(int address)
	{
		hookAddress = _Hook_Address;
		rawlen = _Raw_Len;
		AsmBuilder builder = AsmBuilder(128);

		for (int i = 0, sz = this->regs.size(); i < sz; i++)
			if (this->regs[i] < MEM_ESP_ADD_MASK)
				builder.push_reg((uint8_t)this->regs[i]);
			else if (this->regs[i] <= CONST_VAL_MASK)
				builder.push_m32_esp_imm8((uint8_t)this->regs[i]);
			else
				builder.push_imm32(this->regs[i] - CONST_VAL_MASK);

		builder.invoke(address).add_reg_imm(REG_ESP, this->regs.size() << 2);
		this->InitExtra(builder);

		start(builder.get_code() + 1, builder.get_length() - 1);
	}
	void Init(const char* str)
	{
		Init(PVZ::Memory::GetProcAddress(str));
	}
	virtual void InitExtra(AsmBuilder& builder)
	{
		return;
	}
public:
	static constexpr std::array<DWORD, sizeof...(Params)> regs = { Params... };
};

template<DWORD _Hook_Address, DWORD _Raw_Len, DWORD _Cancel_Addr, DWORD ...Params>
class BoolDLLEventTemplate : public DLLEventTemplate<_Hook_Address, _Raw_Len, Params...>
{
protected:
	virtual void InitExtra(AsmBuilder& builder)
	{
		builder.test_al_al().jnz_rel(7).popad().push_imm32(_Cancel_Addr).ret();
	}
};

template<DWORD _Hook_Address, DWORD _Raw_Len, DWORD _Cancel_Addr, DWORD ...Params>
class TrueDLLEventTemplate : public DLLEventTemplate<_Hook_Address, _Raw_Len, Params...>
{
protected:
	virtual void InitExtra(AsmBuilder& builder)
	{
		builder.test_al_al().jz_rel(7).popad().push_imm32(_Cancel_Addr).ret();
	}
};

template<DWORD _Hook_Address, DWORD _Raw_Len, DWORD _Cancel_Addr, int _Cancel_val,
	int _Lower_Bound, DWORD _Out_Param, bool _Exit, DWORD ...Params>
class IntDLLEventTemplate : public DLLEventTemplate<_Hook_Address, _Raw_Len, Params...>
{
protected:
	virtual void InitExtra(AsmBuilder& builder)
	{
		if (_Cancel_Addr)
			builder.cmp_reg_imm(REG_EAX, _Cancel_val).jne_rel(7).popad().push_imm32(_Cancel_Addr).ret();


		if (_Out_Param < MEM_ESP_ADD_MASK)
		{
			if (_Lower_Bound > INT32_MIN)
				builder.cmp_reg_imm(REG_EAX, _Lower_Bound).jl_rel(5 + (_Exit ? 1 : 2));
			builder.mov_mem_esp_add_imm8_reg(0x1C - (_Out_Param << 2), REG_EAX).popad();
		}
		else if (_Out_Param <= CONST_VAL_MASK)
		{
			if (_Lower_Bound > INT32_MIN)
				builder.cmp_reg_imm(REG_EAX, _Lower_Bound).jl_rel(5 + (_Exit ? 1 : 2));
			builder.mov_mem_esp_add_imm8_reg(_Out_Param, REG_EAX).popad();
		}
		else
		{
			if (_Lower_Bound > INT32_MIN)
				builder.cmp_reg_imm(REG_EAX, _Lower_Bound).jl_rel(7 + (_Exit ? 1 : 2));
			builder.mov_mem_reg(_Out_Param - CONST_VAL_MASK, REG_EAX).popad();
		}

		if (_Exit)
			builder.ret();
		else
			builder.jmp_rel8((uint8_t)_Raw_Len + 1);
	}
};