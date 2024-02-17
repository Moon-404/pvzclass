#include "ModLoader.h"

void ModLoader::loadAll()
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
            mod->onLoad();
        }

        // 确保在程序退出时卸载DLL
        FreeLibrary(dll);
    }
}
