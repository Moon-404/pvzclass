#pragma once
#include "../PVZ.h"

namespace PVZ
{
	class BaseClass;
	class PVZApp;
	//选关界面。
	class ResourceManager : public BaseClass
	{
	public:
		ResourceManager(int address) : BaseClass(address) {};
		T_PROPERTY(BOOLEAN, AllowAlreadyDefinedResources, __get_AllowAlreadyDefinedResources, __set_AllowAlreadyDefinedResources, 0x0B1);
		PVZApp GetPVZApp();
		//@brief 加载指定资源包文件。
		//@param fileName 文件名
		void AddPAKFile(const char* fileName);
		//@brief 尝试解析指定的资源描述文件。
		//@param fileName 文件名
		//@return 是否解析成功。
		bool ParseResourcesFile(const char* fileName);
		//@brief 加载指定的资源组。
		//@param groupName 资源组名称。
		//@return 是否加载成功。
		bool TodLoadResources(const char* groupName);
		//@brief 获取指定音效的编号。
		//@param soundName 音效在资源描述文件中的名称。
		//@return 音效编号。
		SoundID GetSoundThrow(const char* soundName);
		//@brief 获取指定的图片。
		//@param imageName 图片在资源描述文件中的名称。
		//@return 对应的图片。
		Image GetImage(const char* imageName);
	};
	ResourceManager GetResourceManager();
}