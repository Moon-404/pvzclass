#include "../PVZ.h"

HANDLE PVZ::Memory::hProcess = NULL;
DWORD PVZ::Memory::processId = 0;
HANDLE PVZ::Memory::hThread = NULL;
DWORD PVZ::Memory::mainThreadId = 0;
int PVZ::Memory::Variable = 0;
HWND PVZ::Memory::mainwindowhandle = NULL;
bool PVZ::Memory::immediateExecute = false;
int PVZ::Memory::DLLAddress = 0;

int PVZ::Memory::ReadPointerLocal(int baseaddress, int offset)
{
	return ReadMemoryLocal<int>(ReadMemoryLocal<int>(baseaddress) + offset);
}

int PVZ::Memory::ReadPointerLocal(int baseaddress, int offset, int offset1)
{
	return ReadMemoryLocal<int>(ReadPointerLocal(baseaddress, offset) + offset1);
}

int PVZ::Memory::ReadPointerLocal(int baseaddress, int offset, int offset1, int offset2)
{
	return ReadMemoryLocal<int>(ReadPointerLocal(baseaddress, offset, offset1) + offset2);
}

int PVZ::Memory::ReadPointerRemote(int baseaddress, int offset)
{
	return ReadMemoryRemote<int>(ReadMemoryRemote<int>(baseaddress) + offset);
}

int PVZ::Memory::ReadPointerRemote(int baseaddress, int offset, int offset1)
{
	return ReadMemoryRemote<int>(ReadPointerRemote(baseaddress, offset) + offset1);
}

int PVZ::Memory::ReadPointerRemote(int baseaddress, int offset, int offset1, int offset2)
{
	return ReadMemoryRemote<int>(ReadPointerRemote(baseaddress, offset, offset1) + offset2);
}

BOOL PVZ::Memory::AllAccessLocal(int address)
{
	DWORD op = PAGE_READONLY;
	return VirtualProtect((LPVOID)address, PAGE_SIZE, PAGE_EXECUTE_READWRITE, &op);
}

BOOL PVZ::Memory::AllAccessRemote(int address)
{
	DWORD op = PAGE_READONLY;
	return VirtualProtectEx(hProcess, (LPVOID)address, PAGE_SIZE, PAGE_EXECUTE_READWRITE, &op);
}

int PVZ::Memory::AllocMemoryLocal(int pages, int size)
{
	BYTE* page = new BYTE[PAGE_SIZE * pages + size];
	AllAccessLocal((int)page);
	return (int)page;
}

int PVZ::Memory::AllocMemoryRemote(int pages, int size)
{
	return (int)VirtualAllocEx(hProcess, 0, PAGE_SIZE * pages + size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
}

void PVZ::Memory::CreateThread(int address)
{
	HANDLE hThread;
	DWORD ret;
	hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)address, NULL, 0, NULL);
	if (hThread)
	{
		do 
			ret = WaitForSingleObject(hThread, 100);
		while (ret == WAIT_TIMEOUT);
		CloseHandle(hThread);
	}
}

void PVZ::Memory::FreeMemoryLocal(int address)
{
	delete (void*)address;
}

void PVZ::Memory::FreeMemoryRemote(int address)
{
	VirtualFreeEx(hProcess, (LPVOID)address, 0, MEM_RELEASE);
}

int PVZ::Memory::ExecuteLocal(byte asmCode[], int length)
{
	byte* code = new byte[length + 2];
	code[0] = PUSHAD;
	memcpy(code + 1, asmCode, length);
	code[length] = POPAD;
	code[length + 1] = RET;
	void (*func)() = (void (*)())code;
	func();

	delete[](code);
	return ReadMemoryLocal<int>(Variable);
}

int PVZ::Memory::ExecuteLocal(const AsmBuilder& builder)
{
	byte* ori_code = builder.get_code();
	DWORD length = builder.get_length();
	byte* code = new byte[length + 2];

	code[0] = PUSHAD;
	memcpy(code + 1, ori_code, length - 1);
	code[length] = POPAD;
	code[length + 1] = RET;
	void (*func)() = (void (*)())code;
	func();

	delete[](code);
	return ReadMemoryLocal<int>(Variable);
}

int PVZ::Memory::ExecuteRemote(byte asmCode[], int length)
{
	int Address = AllocMemoryRemote();
	WriteArrayRemote<byte>(Address, asmCode, length);
	if (!immediateExecute) WaitPVZ();
	CreateThread(Address);
	if (!immediateExecute) ResumePVZ();
	FreeMemoryRemote(Address);
	return ReadMemoryRemote<int>(Variable);
}

int PVZ::Memory::ExecuteRemote(const AsmBuilder& builder)
{
	int Address = AllocMemoryRemote();
	WriteArrayRemote<byte>(Address, builder.get_code(), builder.get_length());
	if (!immediateExecute) WaitPVZ();
	CreateThread(Address);
	if (!immediateExecute) ResumePVZ();
	FreeMemoryRemote(Address);
	return ReadMemoryRemote<int>(Variable);
}

void PVZ::Memory::WaitPVZ()
{
	WriteMemoryRemote<BYTE>(Variable + 0x530, 1);
	while (ReadMemoryRemote<BYTE>(Variable + 0x540) == 0);
}

void PVZ::Memory::ResumePVZ()
{
	WriteMemoryRemote<BYTE>(Variable + 0x530, 0);
}