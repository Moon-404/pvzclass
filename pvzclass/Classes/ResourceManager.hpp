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
		PVZApp GetPVZApp();
		//@brief 尝试解析指定的资源描述文件。
		//@param fileName 文件名
		//@return 是否解析成功。
		bool ParseResourcesFile(const char* fileName);
	};
	ResourceManager GetResourceManager();
}