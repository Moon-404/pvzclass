#pragma once
/// @file Memory.hpp
/// @brief 包含读写 PVZ 本体内存，以及其他内存操作的若干函数和宏定义。

/// @brief 默认的一页内存的字节数
#define PAGE_SIZE 1024

namespace PVZ
{
	/// @brief 包含各种控制 PVZ 程序的函数和变量的类。所有成员均为静态。
	/// @note 在调用过 InitPVZ() 或 InitPVZNoLock() 之后才能使用此类的各种功能。
	class Memory
	{
	public:
		/*	 */
		/// @brief Init() 系函数申请的、PVZ 本体的内存的基址，供部分函数使用。
		/// @detail 000-100存放创建子弹的函数\n
		///		100 - 200存放字符串或者PlantEffect的伪造植物对象\n
		///		300 - 400存放__autocollect_set\n
		///		400 - 500存放__asm__Plant_memset\n
		///		500 - 600存放Execute的同步代码\n
		static int Variable;
		/// @brief PVZ 进程句柄
		static HANDLE hProcess;
		/// @brief PVZ 进程 ID
		static DWORD processId;
		/// @brief 主线程句柄
		static HANDLE hThread;
		/// @brief 主线程 ID
		static DWORD mainThreadId;
		/// @brief 主窗口句柄
		static HWND mainwindowhandle;
		/// @brief 如果为 true，则不会等待PVZ进程，立即执行远程代码
		/// @note 在 localExecute 为 true 时无效。
		static bool immediateExecute;
		/// @brief 如果为 true，则在当前进程执行代码。若在 dll 中，请将其设置为 true
		static bool localExecute;
		/// @brief 注入的 dll 所在的内存地址
		static int DLLAddress;
		/// @brief 读取 PVZ 程序指定地址上的数据
		/// @tparam T 数据类型
		/// @param address 数据的内存地址
		/// @return 读取的数值
		template <class T>
		inline static T ReadMemory(DWORD address)
		{
			if (localExecute)
			{
				T* buffer = (T*)address;
				return *buffer;
			}
			else
			{
				T buffer = (T)NULL;
				ReadProcessMemory(hProcess, (LPCVOID)address, &buffer, sizeof(T), NULL);
				return buffer;
			}
		};
		/// @brief 将数据写入 PVZ 程序指定地址
		/// @tparam T 数据类型
		/// @param address 写入数据的内存地址
		/// @param value 写入的数值
		/// @return 写入是否成功
		template <class T>
		inline static BOOL WriteMemory(DWORD address, T value)
		{
			if (localExecute)
			{
				AllAccess(address);
				T* buffer = (T*)address;
				*buffer = value;
				return true;
			}
			else
			{
				return WriteProcessMemory(hProcess, (LPVOID)address, &value, sizeof(T), NULL);
			}
		};
		/// @brief 读取 PVZ 程序指定地址上的一连串数据
		/// @tparam T 数据类型
		/// @param address 数据的内存地址
		/// @param result 存放结果的指针
		/// @param length 数组的长度（按字节计）
		/// @return 读取是否成功
		template <class T>
		inline static BOOL ReadArray(DWORD address, T* result, size_t length)
		{
			if (localExecute)
			{
				memcpy(result, (const void*)address, length);
				return true;
			}
			else
			{
				return ReadProcessMemory(hProcess, (LPCVOID)address, (LPVOID)result, length, NULL);
			}
		};
		/// @brief 将一连串数据写入 PVZ 程序指定地址
		/// @tparam T 数据类型
		/// @param address 数据的内存地址
		/// @param result 待写入数据的指针
		/// @param length 数组的长度（按字节计）
		/// @return 读取是否成功
		template <class T>
		inline static BOOL WriteArray(DWORD address, T* value, size_t length)
		{
			if (localExecute)
			{
				AllAccess(address);
				memcpy((void*)address, value, length);
				return true;
			}
			else
			{
				return WriteProcessMemory(hProcess, (LPVOID)address, value, length, NULL);
			}
		};
		static int ReadPointer(int baseaddress, int offset);
		static int ReadPointer(int baseaddress, int offset, int offset1);
		static int ReadPointer(int baseaddress, int offset, int offset1, int offset2);
		/// @brief 调整程序从指定位置开始，PAGE_SIZE 个字节的内存访问权限为可读写执行。
		/// @param address 被调整访问权限的首地址
		/// @return 操作是否成功
		static BOOL AllAccess(int address);
		/// @brief 申请一定大小的内存空间，访问权限为可读写执行。
		/// @param pages 内存页数，默认为 1。
		/// @param size 小于一页部分的内存字节数，默认为 0。
		/// @return 申请的内存的首地址
		static int AllocMemory(int pages = 1, int size = 0);
		/// @brief 在 PVZ 主程序创建一个线程。
		/// @attention 不要在 dll 中调用此函数。
		/// @param address 线程的起始地址
		static void CreateThread(int address);
		/// @brief 释放指定位置的内存空间
		/// @param address 被释放的内存的首地址
		static void FreeMemory(int address);
		/// @brief 在 PVZ 主程序中执行指定指令序列。
		/// @param asmcode 被执行的指令序列
		/// @param length 指令序列长度，按字节数计
		/// @return 指令执行完毕时，Variable 地址上的数值
		static int Execute(byte asmcode[], int length);
		/// @brief 在 PVZ 主程序中执行指定指令序列。
		/// @param builder 构建指令序列的 AsmBuilder
		/// @return 指令执行完毕时，Variable 地址上的数值
		static int Execute(AsmBuilder& builder);
		/// @brief 注入指定的 lib 或 dll 文件。
		/// @param dllname 注入的链接库的路径
		/// @return 是否注入成功
		static bool InjectDll(const char* dllname);
		/// @brief 获取已注入 dll 指定名称的函数的内存地址
		/// @param procname 函数名称
		/// @return 函数的内存地址
		static int GetProcAddress(const char* procname);
		/// @brief 执行注入的 dll 中，指定名称的函数
		/// @param procname 函数名称
		/// @return 指令执行完毕时，Variable 地址上的数值
		static int InvokeDllProc(const char* procname);
		/// @brief 等待PVZ到达更新前
		/// @note 不适用通过 InitPVZNoLock() 初始化的情况。
		static void WaitPVZ();
		/// @brief 恢复PVZ
		/// @note 不适用通过 InitPVZNoLock() 初始化的情况。
		static void ResumePVZ();
	};

}

#define PVZ_BASE PVZ::Memory::ReadMemory<int>(0x6A9EC0)
#define PVZBASEADDRESS PVZ::Memory::ReadMemory<int>(PVZ_BASE + 0x768)

/// @brief 用来替代成员变量声明的类型部分，将其转化为属性。\n
///		转化后对该变量的读写操作分别会转化为调用 getmethod 和 setmethod。
/// @note getmethod 和 setmethod 仅有声明，需要自己另行定义。
/// @param type 变量类型
/// @param getmethod 读成员变量的方法名
/// @param setmethod 写成员变量的方法名
#define PROPERTY(type,getmethod,setmethod) type getmethod();void setmethod(type value);__declspec(property(get=getmethod,put=setmethod)) type
/// @brief PROPERTY 宏的只读版本，不允许写操作。
/// @see PROPERTY
#define READONLY_PROPERTY(type,getmethod) type getmethod();__declspec(property(get=getmethod)) type
/// @brief PROPERTY 宏的只写版本，不允许读操作。
/// @see PROPERTY
#define WRITEONLY_PROPERTY(type,setmethod) void setmethod(type value);__declspec(property(put=setmethod)) type

#define PROPERTY_BINDING(type,getmethod,getter,setmethod,setter) inline type getmethod(){return getter;}; \
	inline void setmethod(type value){setter;}; \
	__declspec(property(get=getmethod,put=setmethod)) type
#define READONLY_PROPERTY_BINDING(type,getmethod,getter) inline type getmethod(){return getter;};\
	__declspec(property(get=getmethod)) type
#define WRITEONLY_PROPERTY_BINDING(type,setmethod,setter) inline void setmethod(type value){setter;};\
	__declspec(property(put=setmethod)) type