#include "TodParticleSystem.hpp"

PVZ::TodParticleSystem::TodParticleSystem(DWORD indexoraddress) : BaseClass(0)
{
	if (indexoraddress < 65536)
		BaseAddress = Memory::ReadPointer(0x6A9EC0, 0x820, 0, 0) + indexoraddress * 0x2C;
	else
		BaseAddress = indexoraddress;
}

AsmBuilder color_builder = AsmBuilder();
void PVZ::TodParticleSystem::OverrideColor(const char* emitter_name, const Color color)
{
	PVZ::Memory::WriteArray<const char>(PVZ::Memory::Variable + 100, emitter_name, std::strlen(emitter_name) + 1);
	color_builder.clear()
		.mov_reg_imm(REG_EBX, PVZ::Memory::Variable + 100)
		.push(color.Alpha)
		.push(color.Blue)
		.push(color.Green)
		.push(color.Red)
		.push_reg(REG_ESP)
		.push(this->BaseAddress)
		.invoke(0x518560)
		.add_reg_imm(REG_ESP, 16)
		.ret();

	PVZ::Memory::Execute(color_builder);
}

AsmBuilder additive_builder = AsmBuilder();
void PVZ::TodParticleSystem::OverrideExtraAdditiveDraw(boolean isEnable)
{
	additive_builder.clear()
		.mov_reg_imm(REG_EDX, isEnable)
		.mov_reg_imm(REG_ESI, this->BaseAddress)
		.invoke(0x5185D0)
		.ret();

	PVZ::Memory::Execute(additive_builder);
}

std::vector<PVZ::TodParticleSystem> PVZ::GetAllParticleSystem()
{
	std::vector<PVZ::TodParticleSystem> particle_syss;
	DWORD holder = PVZ::Memory::ReadPointer(0x6A9EC0, 0x820, 0);
	DWORD maxnum = Memory::ReadMemory<DWORD>(holder + 4), address = Memory::ReadMemory<DWORD>(holder);

	for (int i = 0; i < maxnum; i++)
	{
		PVZ::TodParticleSystem sys = PVZ::TodParticleSystem(address + i * 0x2C);
		if (!sys.Dead)
			particle_syss.push_back(sys);
	}

	return particle_syss;
}


PVZ::TodParticleSystem PVZ::CreateParticleSystem(float X, float Y, int render_order, EffectType::EffectType type)
{
	AsmBuilder builder = AsmBuilder()
		.mov_reg_imm(REG_EAX, type)
		.mov_reg_imm(REG_ECX, render_order)
		.push_float(Y)
		.push_float(X)
		.mov_reg_imm(REG_EDX, PVZ_BASE)
		.invoke(0x453C80)
		.mov_mem_reg(PVZ::Memory::Variable, REG_EAX)
		.ret();

	return PVZ::TodParticleSystem(PVZ::Memory::Execute(builder));
}
