#pragma once
#include "Enums.h"
#include "Flags.h"
#include "AsmFunctions.h"
#include "AsmBuilder.hpp"
#include "Memory.hpp"
#include <ctime>
#include <memory>
#include <vector>
#include <type_traits>

using std::enable_if_t;
using std::is_base_of;

#pragma region definitions

#define STRING(str) str,sizeof(str)/sizeof(*str)
#define SETARG(asmfunction,index) *(int*)(asmfunction+index)
#define SETARGFLOAT(asmfunction,index) *(float*)(asmfunction+index)

#define LOGICALINCLUDE(c,v) (c&v)==v

#define SPT std::shared_ptr
#define UPT std::unique_ptr
#define MKU std::make_unique
#define MKS std::make_shared

#pragma endregion

#define AP_ZOMBIESPEED		1
#define AP_ZOMBIECOLOR		2
#define AP_ZOMBIESCALE		4
#define AP_PLANTCOLOR		8
#define AP_PLANTSCALE		16

#define GPD_RIGHT			0
#define GPD_LEFT			1

#define MINGAM_ENABLE		2
#define MINGAM_DISABLE		-1

#define MINGAME_STARTED		1
#define MINGAME_NOTSTARTED	-1

#define APA_LOOP			1
#define APA_ONCE_DISAPPEAR	2
#define APA_ONCE_STOP		3

#define ID_INDEX(id) ((id) & 0x0000FFFF)
#define ID_RANK(id) ((id) & 0xFFFF0000)

/// @deprecated
#define HZC_COMMON 1
/// @deprecated
#define HZC_BALLOON_AIR 2
/// @deprecated
#define HZC_SNORKED_UNDER 4
/// @deprecated
#define HZC_NOT_GROUNDED 16
/// @deprecated
#define HZC_DYING 32
/// @deprecated
#define HZC_DIGGER_UNDER 64
/// @deprecated
#define HZC_HYPNOTIZED 128

#define INVALID_BASEADDRESS 0x400000

/// @brief 包含大部分用于控制 PVZ 内部对象的类和方法。
/// @note Only version 1.0.0.1051 is fully supported
namespace PVZ
{
	/// @brief 初始化 PVZ 命名空间，且不在程序内附加钩子。Memory::immediateExecute 会设置为 true 。
	/// @param pid 进程 id
	void InitPVZNoLock(DWORD pid);

	void InitPVZ(DWORD pid);
	void QuitPVZ();

	#pragma region structs

	struct Color
	{
		int Red;
		int Green;
		int Blue;
		int Alpha;
	};

	#pragma endregion

	#pragma region classes
	/// @brief 所有对应 PVZ 内部对象的类的基类。
	/// @attention 你不应该直接构造 BaseClass！
	class BaseClass
	{
	protected:
		/// @brief 对应对象的基地址
		int BaseAddress;
	public:
		BaseClass() : BaseAddress(INVALID_BASEADDRESS) {};
		BaseClass(int address) : BaseAddress(address) {};
		/// @brief 返回基址
		/// @return 基址
		int GetBaseAddress() const
		{ return(this->BaseAddress); }
		/// @brief 对应的对象是否已经失效，或者构造不良。
		/// @return 是否已经失效或构造不良。
		const bool isValid()
		{ return(this->BaseAddress != INVALID_BASEADDRESS && this->BaseAddress != 0); }
	};

	class Rect
	{
	public:
		int X;
		int Y;
		int Width;
		int Height;
		// 判定坐标为 (X, Y)，半径为 radius 的圆与该矩阵是否有重叠部分。
		// 相切会视为有重叠部分。
		bool IsCircleOverlap(const int X, const int Y, const int radius);
	};
	// 取得两个矩形横向重叠部分的长度。
	// 若横向无重叠部分，返回两矩形横向间距的相反数。
	/// @param rect 计算重叠的另一个矩形。
	/// @return 矩形横向重叠的长度，或矩形横向间距的相反数。
	int GetXOverlap(const Rect& rect1, const Rect& rect2);

	typedef Rect CollisionBox;

	class PVZutil
	{
	public:
		/// @brief 获取 PVZClass 版本
		READONLY_PROPERTY(const char*,	__get_Version)	Version;
		/// @brief 判断 PVZ 主程序是哪一个发布版本。
		/// @see PVZVersion
		READONLY_PROPERTY(PVZVersion::PVZVersion,	__get_GameVersion)	GameVersion;
	};

	/// @brief 游戏程序主类（原 LawnApp）。
	class PVZApp : public BaseClass
	{
	public:
		PVZApp(DWORD address) : BaseClass(address) {};
		/// @brief 音乐音量大小，数值应当在 [0,1] 范围内。
		PROPERTY(double,						__get_MusicVolume,	__set_MusicVolume)			aMusicVolume;
		/// @brief 音效音量大小，数值应当在 [0,1] 范围内。
		PROPERTY(double,						__get_SoundFXVolume,__set_SoundFXVolume)		SoundFXVolume;
		/// @brief 主线程 ID
		T_PROPERTY(DWORD,						PrimaryThreadId,	__get_PrimaryThreadId,		__set_PrimaryThreadId,		0x33C);
		/// @brief 是否关闭
		T_PROPERTY(BOOLEAN,						Shutdown,			__get_Shutdown,				__set_Shutdown,				0x341);
		/// @brief 窗口句柄
		T_PROPERTY(HWND,						HWnd,				__get_HWnd,					__set_HWnd,					0x350);
		/// @brief 当前模式类型
		T_PROPERTY(PVZLevel::PVZLevel,			LevelId,			__get_LevelId,				__set_LevelId,				0x7F8);
		/// @brief 游戏状态
		/// @see PVZGameState
		T_PROPERTY(PVZGameState::PVZGameState,	GameState,			__get_GameState,			__set_GameState,			0x7FC);
		/// @brief 是否开启自由种植
		T_PROPERTY(BOOLEAN,						FreePlantingCheat,	__get_FreePlantingCheat,	__set_FreePlantingCheat,	0x814);
		/// @brief 是否在玩完整版。部分 PVZ 主程序反转了它的效果。
		T_PROPERTY(BOOLEAN,						FullVersion,		__get_FullVersion,			__set_FullVersion,			0x8C0);
	};
	/// @brief 获取游戏程序主对象
	/// @return 游戏程序主对象
	PVZApp GetPVZApp();

	/// @brief 图片类
	class Image : public BaseClass
	{
	public:
		Image(int address) : BaseClass(address) {};
	};

	class Attachment;
	class AttachmentID;
	class Zombie;
	class Plant;
	class Projectile;
	class Coin;
	class LawnMower;
	class Griditem;
	class MousePointer;
	class Caption;
	class CardSlot;
	class Challenge;
	class Lawn;
	class Icetrace;
	class Wave;
	class Widget;

	class WidgetContainer : public BaseClass
	{
	public:
		WidgetContainer(int address) : BaseClass(address) {};
		INT_PROPERTY(ViewX,			__get_ViewX,		__set_ViewX,		0x30);
		INT_PROPERTY(ViewY,			__get_ViewY,		__set_ViewY,		0x34);
		INT_PROPERTY(ViewLength,	__get_ViewLength,	__set_ViewLength,	0x38);
		INT_PROPERTY(ViewHeight,	__get_ViewHeight,	__set_ViewHeight,	0x3C);

		/// @brief 将指定控件设定为容器的子控件。
		/// @param widget 子控件
		void AddWidget(Widget widget);
		/// @brief 将指定控件移出容器的子控件列表。
		/// @param widget 子控件
		void RemoveWidget(Widget widget);
	};
	/// @brief 控件
	class Widget : public WidgetContainer
	{
	public:
		Widget(int address) : WidgetContainer(address) {};
	};
	/// @brief 三行三列矩阵
	class Matrix3 : public BaseClass
	{
	public:
		Matrix3(DWORD address) : BaseClass(address) {};

		/// @brief 根据指定的平移坐标、旋转弧度和拉伸比例，设定矩阵每个项的数值。
		void ScaleRotateTransformMatrix(float x, float y, float rad, float ScaleX, float ScaleY);
	};
	class TrackInstance;
	class AttachEffect : public BaseClass
	{
	public:
		AttachEffect(int address) : BaseClass(address) {};
		Matrix3 GetOffset();
	};
	/// @brief 动画部件。相当于其他游戏的模型。
	class Animation : public BaseClass
	{
	public:
		Animation(int idoraddress);
		//support muiti-animprop(AP_XXXXXX)
		static void UnLock(int animprop);
		static void Lock();
		int GetBaseAddress();
		/// @brief 动画类型
		T_READONLY_PROPERTY(AnimationType::AnimationType, Type, __get_Type, 0);
		/// @brief 动画时长
		T_PROPERTY(FLOAT, CycleRate, __get_CycleRate, __set_CycleRate, 4);
		/// @brief 播放速率
		T_PROPERTY(FLOAT, Speed, __get_Speed, __set_Speed, 8);
		/// @brief 是否已移除
		T_PROPERTY(BOOLEAN, NotExist, __get_NotExist, __set_NotExist, 0x14);
		/// @brief 起始帧
		INT_PROPERTY(StartFrame, __get_StartFrame, __set_StartFrame, 0x18);
		/// @brief 帧数
		INT_PROPERTY(FrameCount, __get_FrameCount, __set_FrameCount, 0x1C);
		INT_PROPERTY(FrameBasePose, __get_FrameBasePose, __set_FrameBasePose, 0x20);
		T_PROPERTY(FLOAT, XScale, __get_XScale, __set_XScale, 0x24);
		T_PROPERTY(FLOAT, XSlant, __get_XSlant, __set_XSlant, 0x28);
		T_PROPERTY(FLOAT, XOffset, __get_XOffset, __set_XOffset, 0x2C);
		T_PROPERTY(FLOAT, YScale, __get_YScale, __set_YScale, 0x30);
		T_PROPERTY(FLOAT, YSlant, __get_YSlant, __set_YSlant, 0x34);
		T_PROPERTY(FLOAT, YOffset, __get_YOffset, __set_YOffset, 0x38);
		/// @brief 获取该动画的颜色重载。
		/// @return 颜色
		Color GetColor(); // 0x48-0x54，基础颜色
		/// @brief 设置该动画的颜色重载
		/// @param color 设置后的颜色
		void SetColor(Color color);
		/// @brief 获取指定名称的轨道
		/// @param trackName 轨道名称
		/// @return 轨道实例
		TrackInstance GetTrackInstance(const char* trackName);
		/// @brief 循环播放次数
		INT_PROPERTY(CycleCount, __get_CycleCount, __set_CycleCount, 0x5C);
		/// @brief 获取该动画的加色
		/// @return 加色
		Color GetAdditiveColor();
		/// @brief 设置该动画的加色
		/// @param color 设置后动画的加色
		void SetAdditiveColor(Color color);
		/// @brief 是否启用加色模式
		T_PROPERTY(BOOLEAN, DrawAdditiveColor, __get_DrawAdditiveColor, __set_DrawAdditiveColor, 0x7C);
		/// @brief 获取该动画的覆盖色
		/// @return 覆盖色
		Color GetOverlayColor();
		/// @brief 设置该动画的覆盖色
		/// @param color 设置后动画的覆盖色
		void SetOverlayColor(Color color);
		/// @brief 是否启用覆盖颜色模式
		T_PROPERTY(BOOLEAN, DrawOverlayColor, __get_DrawOverlayColor, __set_DrawOverlayColor, 0x90);
		/// @brief 设置染色模式，主要实现模仿者的染色
		T_PROPERTY(PaintState::PaintState, Paint, __get_Paint, __set_Paint, 0x98);
		/// @brief 识别 ID
		INT_READONLY_PROPERTY(Id, __get_Id, 0x9C);
		READONLY_PROPERTY_BINDING(int, __get_Index, Id & 0xFFFF) Index;
		/// @brief 将该模型附加在指定识别 ID 的附件上。
		/// @param attachmentID 附件的识别 ID
		/// @param OffsetX X 坐标偏移
		/// @param OffsetY Y 坐标偏移
		/// @return 附加后的效果，可以用于设置变换矩阵
		AttachEffect AttachTo(AttachmentID attachmentID, float OffsetX, float OffsetY);
		/// @brief 移除该动画部件
		void Die();
		/// @brief 播放指定动画
		/// @param TrackName 动画轨道名称
		/// @param blendType 混合类型
		/// @param loopType 循环类型
		/// @param rate 播放帧频
		void Play(const char* TrackName, int blendType, int loopType, float rate);
		/// @brief 设置指定前缀的所有轨道在绘制时的分组。通常情况下，分组为 -1 时表示隐藏该轨道。
		/// @param trackName 动作轨道的名称前缀
		/// @param renderGroup 分组大小
		void AssignRenderGroupToPrefix(byte RenderGroup, const char* TrackName);
		/// @brief 设置指定动画轨道在绘制时的分组。通常情况下，分组为 -1 时表示隐藏该轨道。
		/// @param trackName 执行的动作轨道名称
		/// @param renderGroup 分组大小
		void AssignRenderGroupToTrack(const char* trackName, byte renderGroup);
		int FindTrackIndex(const char* trackName);

		/// @brief 令动画部件执行 trackName 动作。
		/// @param trackName 执行的动作轨道名称。
		void SetFramesForLayer(const char* theTrackName);
		/// @brief 设置指定轨道的重载图片
		/// @param theTrackName 轨道名称
		/// @param theImage 图片
		void SetImageOverride(const char* theTrackName, Image theImage);
	};
	class Attachment : public BaseClass
	{
	public:
		Attachment(int idoraddress);
		// TODO: check whether this function works properly.
		PVZ::Animation GetAnimation();
		INT_READONLY_PROPERTY(Id, __get_Id, 0x308);
	};
	class AttachmentID : public BaseClass
	{
	public:
		AttachmentID(DWORD address) : BaseClass(address) {};
	};
	class TrackInstance : public BaseClass
	{
	public:
		TrackInstance(int idoraddress);
		AttachmentID GetAttachmentID();
		Attachment GetAttachment();
	};
	/// @brief 控制行地形类型和每个格位地形类型的类
	class Lawn : public BaseClass
	{
	public:
		Lawn(int baseaddress);
		/// @brief 获取指定格位的地形类型
		/// @param row 行
		/// @param column 列
		/// @return 地形类型
		LawnType::LawnType GetGridType(int row, int column);
		/// @brief 设置指定格位的地形类型
		/// @param row 行
		/// @param column 列
		/// @param type 设置后的地形类型
		void SetGridType(int row, int column, LawnType::LawnType type);
		/// @brief 获取指定行的地形类型
		/// @param route 行
		/// @return 地形类型
		RouteType::RouteType GetRouteType(int route);
		/// @brief 设置指定行的地形类型
		/// @note 该函数不会影响该行任何格位的地形类型，需要用 SetGridType() 另行改动。
		/// @param route 行
		/// @param type 设置后的地形类型
		void SetRouteType(int route, RouteType::RouteType type);
		/// @brief 判断指定类型卡牌是否可以在指定位置上使用。
		/// @param row 行
		/// @param column 列
		/// @param type 卡牌类型
		/// @return 是否可以使用
		bool Plantable(int row, int column, SeedType::SeedType type);
	};
	/// @brief 冰道
	class Icetrace : public BaseClass
	{
	public:
		Icetrace(int baseaddress);
		/// @brief 获取指定行的冰道最左侧 X 坐标
		/// @param route 行
		/// @return 冰道最左侧 X 坐标
		int GetX(int route);
		/// @brief 设置指定行的冰道最左侧 X 坐标
		/// @param route 行
		/// @param x 设置后的 X 坐标
		void SetX(int route, int x);
		/// @brief 获取指定行的冰道消失倒计时
		/// @param route 行
		/// @return 消失倒计时
		int GetDisappearCountdown(int route);
		/// @brief 设置指定行的冰道消失倒计时
		/// @param route 行
		/// @param cs 设置的消失倒计时，单位为厘秒。
		void SetDisappearCountdown(int route, int cs);
	};
	/// @brief 一波僵尸的出怪列表
	class Wave : public BaseClass
	{
	public:
		Wave(int baseaddress);
		/// @brief 此波的总僵尸数
		READONLY_PROPERTY(int, __get_Count) Count;
		/// @brief 获取此波所有僵尸
		/// @param ztypes 存储返回值的数组
		void GetAll(ZombieType::ZombieType* ztypes);
		/// @brief 设置此波僵尸。若不足 50 个，应当用 ZombieType::None 结尾。
		/// @param ztypes 僵尸列表
		/// @param length 僵尸列表长度
		void SetAll(ZombieType::ZombieType* ztypes, size_t length);
		/// @brief 获取出怪列表指定编号的僵尸
		/// @param index 僵尸在出怪列表中的编号
		/// @return 僵尸类型
		ZombieType::ZombieType Get(int index);
		/// @brief 设置指定编号上的僵尸。
		/// @note 不能以此法增加僵尸数量。若要增加，请使用 Add()
		/// @param index
		/// @param ztype
		void Set(int index, ZombieType::ZombieType ztype);
		/// @brief 删除指定编号上的僵尸
		/// @param index 编号
		void Del(int index);
		/// @brief 将指定类型的僵尸添加到列表末尾。
		/// @param ztype 僵尸类型
		void Add(ZombieType::ZombieType ztype);
		/// @brief 将指定数组的全部僵尸加到本波出怪列表中。溢出的部分会被忽略。
		/// @param ztypes 僵尸类型数组
		/// @param length 数组长度
		void AddAll(ZombieType::ZombieType* ztypes, int length);
	};
	// 鼠标对象(控制层面的鼠标)
	class Mouse : public BaseClass
	{
	public:
		Mouse(int baseaddress) : BaseClass(baseaddress) {};
		T_READONLY_PROPERTY(BOOLEAN, InGameArea, __get_InGameArea, 0xDC);
		INT_PROPERTY(X, __get_X, __set_X, 0xE0);
		INT_PROPERTY(Y, __get_Y, __set_Y, 0xE4);
		T_READONLY_PROPERTY(MouseClickState::MouseClickState, ClickState, __get_ClickState, 0xE8);
		void WMClick(short x, short y);
		void GameClick(int x, int y);
		void MoveTo(int x, int y);
	};
	class GardenPlant : public BaseClass
	{
	public:
		GardenPlant(int address);
		T_PROPERTY(SeedType::SeedType, Type, __get_Type, __set_Type, 8);
		T_PROPERTY(GardenScene::GardenScene, Location, __get_Location, __set_Location, 0xC);
		INT_PROPERTY(Column, __get_Column, __set_Column, 0x10);
		INT_PROPERTY(Row, __get_Row, __set_Row, 0x14);
		//GPD_LEFT or GPD_RIGTHT
		INT_PROPERTY(Direction, __get_Direction, __set_Direction, 0x18);
		T_PROPERTY(std::time_t, LastWateredTime, __get_LastWateredTime, __set_LastWateredTime, 0x20);
		INT_PROPERTY(Colour, __get_Colour, __set_Colour, 0x28);
		T_PROPERTY(GardenPlantState::GardenPlantState, State, __get_State, __set_State, 0x2C);
		INT_PROPERTY(WateredCount, __get_WateredCount, __set_WateredCount, 0x30);
		INT_PROPERTY(LevelUpWaterNeed, __get_LevelUpWaterNeed, __set_LevelUpWaterNeed, 0x34);
		T_PROPERTY(GardenPlantNeed::GardenPlantNeed, LevelUpNeed, __get_LevelUpNeed, __set_LevelUpNeed, 0x38);
		T_PROPERTY(std::time_t, LastGoldTime, __get_LastGoldTime, __set_LastGoldTime, 0x40);
		T_PROPERTY(std::time_t, LastGrowthTime, __get_LastGrowthTime, __set_LastGrowthTime, 0x48);
	};

	#pragma endregion

	#pragma region methods

	void InitImages();
	Mouse GetMouse();

	#pragma endregion

	#pragma region Images

	class Resource
	{
	public:
		static Image* IMAGE_BLANK;
	};

	#pragma endregion
};