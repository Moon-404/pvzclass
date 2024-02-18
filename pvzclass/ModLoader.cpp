#include "ModLoader.h"

void ModLoader::loadAll(EventHandler& handler)
{
    std::filesystem::path p = "mods";
    for (const auto& entry : std::filesystem::directory_iterator(p))
    {
        HMODULE dll = LoadLibrary(entry.path().c_str());
        if (dll == nullptr)
        {
            std::cout << "无法加载模组：" << entry.path().string() << std::endl;
            continue;
        }

        auto getMod = (Mod*(*)())GetProcAddress(dll, "getMod");
        if (getMod == nullptr)
        {
            std::cout << "找不到初始化函数：" << entry.path().string() << std::endl;
            FreeLibrary(dll);
            continue;
        }

        Mod* mod = getMod();
        if (mod != nullptr)
        {
            std::cout << "成功加载模组：" << entry.path().string() << std::endl;
            std::cout << "模组名与版本号：" << mod->MOD_TITLE << " " << mod->MOD_VERSION << std::endl;
            std::cout << "作者：" << mod->MOD_AUTHOR << std::endl;
            std::cout << "描述：" << mod->MOD_DESCRIPTION << std::endl;
            mod->onLoad(PVZ::Memory::processId, PVZ::Memory::hProcess, PVZ::Memory::mainwindowhandle,
                PVZ::Memory::Variable, PVZ::Memory::mainThreadId, PVZ::Memory::hThread, handler);
        }

        dlls.push_back(dll);
        mods.push_back(mod);
    }
}

void ModLoader::update()
{
    for (int i = 0; i < mods.size(); i++)
    {
        mods[i]->update();
    }
}

void ModLoader::freeAll()
{
    for (int i = 0; i < dlls.size(); i++)
    {
        FreeLibrary(dlls[i]);
        mods[i]->onFree();
    }
}
