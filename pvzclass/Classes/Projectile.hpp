#pragma once
#include "../PVZ.h"

namespace PVZ
{
	/// @brief 子弹
	class Projectile : public GameObject
	{
	public:
		/// @brief 子弹的内存占用字节数。\n
		///		若派生类需要对应扩指针的对象，请在派生类中修改此数值。
		static const DWORD MemSize = 0x94;
		Projectile(int indexoraddress);
		/// @brief 实际 X 坐标
		T_PROPERTY(FLOAT, X, __get_X, __set_X, 0x30);
		/// @brief 子弹本体的 Y 坐标
		T_PROPERTY(FLOAT, Y, __get_Y, __set_Y, 0x34);
		/// @brief 子弹 Z 坐标
		T_PROPERTY(FLOAT, Height, __get_Height, __set_Height, 0x38);
		/// @brief X 方向坐标
		T_PROPERTY(FLOAT, XSpeed, __get_XSpeed, __set_XSpeed, 0x3C);
		T_PROPERTY(FLOAT, YSpeed, __get_YSpeed, __set_YSpeed, 0x40);
		T_PROPERTY(FLOAT, HeightSpeed, __get_HeightSpeed, __set_HeightSpeed, 0x44);
		T_PROPERTY(FLOAT, HeightAcceleration, __get_HeightAcceleration, __set_HeightAcceleration, 0x48);
		/// @brief 影子 Y 坐标
		T_PROPERTY(FLOAT, ShadowY, __get_ShadowY, __ShadowY, 0x4C);
		/// @brief 是否已移除
		T_PROPERTY(BOOLEAN, NotExist, __get_NotExist, __set_NotExist, 0x50);
		/// @brief 子弹运动类型
		T_PROPERTY(MotionType::MotionType, Motion, __get_Motion, __set_Motion, 0x58);
		/// @brief 子弹类型
		T_PROPERTY(ProjectileType::ProjectileType, Type, __get_Type, __set_Type, 0x5C);
		/// @brief 存在时间
		INT_READONLY_PROPERTY(ExistedTime, __get_ExistedTime, 0x60);
		/// @brief 旋转大小，暂不确定单位是否为弧度。
		T_PROPERTY(FLOAT, RotationAngle, __get_RotationAngle, __set_RotationAngle, 0x68);
		/// @brief 旋转速度，尚不确认是否是角速度。
		T_PROPERTY(FLOAT, RotationSpeed, __get_RotationSpeed, __set_RotationSpeed, 0x6C);
		/// @brief 子弹索敌标签
		T_PROPERTY(DamageRangeFlags, DamageAbility, __get_DamageAbility, __set_DamageAbility, 0x74);
		/// @brief 对于跟踪弹道，表示跟踪目标僵尸的 ID 。
		INT_PROPERTY(TracktargetId, __get_TracktargetId, __set_TracktargetId, 0x88);
		/// @brief 识别 ID
		INT_READONLY_PROPERTY(Id, __get_Id, 0x90);
		READONLY_PROPERTY_BINDING(int, __get_Index, Id & 0xFFFF) Index;
		/// @brief 子弹过火，转化为火球
		void OnFire();
		/// @brief 移除该子弹。
		void Remove();
	};
}