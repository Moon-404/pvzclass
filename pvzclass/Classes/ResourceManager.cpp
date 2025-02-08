#include "ResourceManager.hpp"

namespace PVZ
{
	ResourceManager GetResourceManager()
	{
		return ResourceManager(Memory::ReadPointer(0x6A9EC0, 0x634));
	}
	PVZApp ResourceManager::GetPVZApp()
	{
		return PVZApp(Memory::ReadMemory<DWORD>(BaseAddress + 0x58));
	}
}

AsmBuilder ParseResourcesFile_builder = AsmBuilder(128);
bool PVZ::ResourceManager::ParseResourcesFile(const char* fileName)
{
	PVZ::Memory::WriteArray<const char>(PVZ::Memory::Variable + 100, fileName, std::strlen(fileName) + 1);
	ParseResourcesFile_builder.clear()
		.mov_reg_imm(REG_ECX, PVZ::Memory::Variable + 100)
		.push(0)
		.push_reg(REG_ESP)
		.invoke(0x404450)
		.mov_reg_reg(REG_ECX, REG_ESP)
		.push_imm32(this->GetBaseAddress())
		.invoke(0x5B6A20)
		.ret();

	return PVZ::Memory::Execute(ParseResourcesFile_builder);
}