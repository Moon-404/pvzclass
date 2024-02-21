#include "ModLoader.h"

void ModLoader::loadPath(std::filesystem::path p, EventHandler& handler, int stage)
{
    for (const auto& entry : std::filesystem::directory_iterator(p))
    {
        auto& path = entry.path();
        if (std::filesystem::is_directory(path))
        {
            loadPath(path, handler, stage);
        }
        else if (stage == 1 && path.filename() == "assets.json")
        {
            std::ifstream jsonFile(path);
            nlohmann::json jsonData = nlohmann::json::parse(jsonFile);
            jsonFile.close();
            std::string assetName = jsonData["name"];
            std::string assetVersion = jsonData["version"];
            std::string assetAuthor = jsonData["author"];
            std::string assetDescription = jsonData["description"];
            SetConsoleOutputCP(CP_UTF8);
            std::cout << u8"成功加载资源包：" << path << std::endl;
            std::cout << u8"模组名与版本号：" << assetName << " " << assetVersion << std::endl;
            std::cout << u8"作者：" << assetAuthor << std::endl;
            std::cout << u8"描述：" << assetDescription << std::endl;
            SetConsoleOutputCP(936);
            for (const auto& asset : jsonData["assets"])
            {
                std::filesystem::path source = asset["source"];
                std::filesystem::path target = asset["target"];
                std::filesystem::path backup = "ModBackupAssets" / target;
                nlohmann::json info;
                info["source"] = "";
                info["target"] = target;
                std::filesystem::create_directories(target.parent_path());
                std::filesystem::create_directories(backup.parent_path());
                if (std::filesystem::exists(target))
                {
                    std::filesystem::copy_file(target, backup, std::filesystem::copy_options::overwrite_existing);
                    info["source"] = backup;
                }
                std::filesystem::copy_file(path.parent_path() / source, target, std::filesystem::copy_options::overwrite_existing);
                assets.push_back(info);
            }
        }
        else if (stage == 2 && path.extension() == ".dll")
        {
            HMODULE dll = LoadLibrary(path.c_str());
            if (dll == nullptr)
            {
                std::cout << "无法加载模组：" << path << std::endl;
                continue;
            }

            auto getMod = (Mod * (*)())GetProcAddress(dll, "getMod");
            if (getMod == nullptr)
            {
                std::cout << "找不到初始化函数：" << path << std::endl;
                FreeLibrary(dll);
                continue;
            }

            Mod* mod = getMod();
            if (mod != nullptr)
            {
                std::cout << "成功加载模组：" << path << std::endl;
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
}

void ModLoader::loadAsset(EventHandler& handler)
{
    if (std::filesystem::exists("assets.json"))
    {
        std::ifstream infile("assets.json");
        nlohmann::json jsonData = nlohmann::json::parse(infile);
        infile.close();
        for (const auto& asset : jsonData)
        {
            std::filesystem::path source = asset["source"];
            std::filesystem::path target = asset["target"];
            if (source == "")
            {
                std::filesystem::remove(target);
            }
            else
            {
                std::filesystem::copy_file(source, target, std::filesystem::copy_options::overwrite_existing);
                std::filesystem::remove(source);
            }
        }
    }
    loadPath("mods", handler, 1);
    std::ofstream outfile("assets.json");
    outfile << assets;
    outfile.close();
}

void ModLoader::loadDll(EventHandler& handler)
{
    TCHAR path[1024] = { 0 };
    DWORD size = 0;
    GetModuleFileNameEx(PVZ::Memory::hProcess, NULL, path, 1024);
    std::filesystem::path exePath = path;
    PVZPath = exePath.parent_path();
    loadPath("mods", handler, 2);
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
