#include "ModLoader.h"

void ModLoader::loadPath(std::filesystem::path p, EventHandler& handler)
{
    for (const auto& entry : std::filesystem::directory_iterator(p))
    {
        if (std::filesystem::is_directory(entry.path()))
        {
            loadPath(entry.path(), handler);
        }
        else if (entry.path().extension() == ".dll")
        {
            HMODULE dll = LoadLibrary(entry.path().c_str());
            if (dll == nullptr)
            {
                std::cout << "�޷�����ģ�飺" << entry.path() << std::endl;
                continue;
            }

            auto getMod = (Mod * (*)())GetProcAddress(dll, "getMod");
            if (getMod == nullptr)
            {
                std::cout << "�Ҳ�����ʼ��������" << entry.path() << std::endl;
                FreeLibrary(dll);
                continue;
            }

            Mod* mod = getMod();
            if (mod != nullptr)
            {
                std::cout << "�ɹ�����ģ�飺" << entry.path() << std::endl;
                std::cout << "ģ������汾�ţ�" << mod->MOD_TITLE << " " << mod->MOD_VERSION << std::endl;
                std::cout << "���ߣ�" << mod->MOD_AUTHOR << std::endl;
                std::cout << "������" << mod->MOD_DESCRIPTION << std::endl;
                mod->PVZPath = PVZPath;
                mod->ModPath = PVZPath / entry.path();
                mod->onLoad(PVZ::Memory::processId, PVZ::Memory::hProcess, PVZ::Memory::mainwindowhandle,
                    PVZ::Memory::Variable, PVZ::Memory::mainThreadId, PVZ::Memory::hThread, handler);
            }

            dlls.push_back(dll);
            mods.push_back(mod);
        }
    }
}

void ModLoader::loadAll(EventHandler& handler)
{
    TCHAR path[1024] = { 0 };
    DWORD size = 0;
    GetModuleFileNameEx(PVZ::Memory::hProcess, NULL, path, 1024);
    std::filesystem::path exePath = path;
    PVZPath = exePath.parent_path();
    loadPath("mods", handler);
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
