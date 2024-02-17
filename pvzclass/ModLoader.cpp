#include "ModLoader.h"

void ModLoader::loadAll()
{
    std::filesystem::path p = "mods";
    for (const auto& entry : std::filesystem::directory_iterator(p))
    {
        HMODULE dll = LoadLibrary(entry.path().c_str());
        if (dll == nullptr)
        {
            std::cout << "�޷�����ģ�飺" << entry.path().string() << std::endl;
            continue;
        }

        auto getMod = (Mod*(*)())GetProcAddress(dll, "getMod");
        if (getMod == nullptr)
        {
            std::cout << "�Ҳ�����ʼ��������" << entry.path().string() << std::endl;
            FreeLibrary(dll);
            continue;
        }

        Mod* mod = getMod();
        if (mod != nullptr)
        {
            std::cout << "�ɹ�����ģ�飺" << entry.path().string() << std::endl;
            std::cout << "ģ������汾�ţ�" << mod->MOD_TITLE << " " << mod->MOD_VERSION << std::endl;
            std::cout << "���ߣ�" << mod->MOD_AUTHOR << std::endl;
            std::cout << "������" << mod->MOD_DESCRIPTION << std::endl;
            mod->onLoad();
        }

        // ȷ���ڳ����˳�ʱж��DLL
        FreeLibrary(dll);
    }
}
