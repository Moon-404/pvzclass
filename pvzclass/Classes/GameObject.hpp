#pragma once
#include "../PVZ.h"

namespace PVZ
{
	/// @brief 各种掉落物
	class Coin : public GameObject
	{
	public:
		/// @brief 掉落物的内存占用字节数。\n
		///		若派生类需要对应扩指针的对象，请在派生类中修改此数值。
		static const DWORD MemSize = 0x0D8;
		Coin(int indexoraddress);
		INT_READONLY_PROPERTY(ImageXVariation, __get_ImageXVariation, 8);
		INT_READONLY_PROPERTY(ImageYVariation, __get_ImageYVariation, 0xC);
		void GetCollision(Rect* collbox);
		void SetCollision(Rect* collbox);
		/// @brief 实际 X 坐标
		T_PROPERTY(FLOAT, X, __get_X, __set_X, 0x24);
		/// @brief 实际 Y 坐标
		T_PROPERTY(FLOAT, Y, __get_Y, __set_Y, 0x28);
		/// @brief 大小
		T_PROPERTY(FLOAT, Size, __get_Size, __set_Size, 0x34);
		/// @brief 是否已消失
		T_PROPERTY(BOOLEAN, NotExist, __get_NotExist, __set_NotExist, 0x38);
		/// @brief 已存在时间
		INT_READONLY_PROPERTY(ExistedTime, __get_ExistedTime, 0x4C);
		/// @brief 是否已被收集
		T_PROPERTY(BOOLEAN, Collected, __get_Collected, __set_Collected, 0x50);
		/// @brief 消失倒计时
		INT_PROPERTY(DisappearCounter, __get_DisappearCounter, __set_DisappearCounter, 0x54);
		/// @brief 物品类型
		T_PROPERTY(CoinType::CoinType, Type, __get_Type, __set_Type, 0x58);
		/// @brief 该物品的移动类型
		T_PROPERTY(CoinMotionType::CoinMotionType, Motion, __get_Motion, __set_Motion, 0x5C);
		/// @brief 获取该物品的附件
		/// @return 该物品的附件
		PVZ::Attachment GetAttachment();
		/// @brief 种子卡片的种子类型
		T_PROPERTY(SeedType::SeedType, ContentCard, __get_ContentCard, __set_ContentCard, 0x68);
		/// @brief 获取该掉落物对应的花园盆栽
		/// @return 该掉落物对应的花园盆栽
		PVZ::GardenPlant GetGardenPlant();
		/// @brief 是否有光环视觉效果
		T_PROPERTY(BOOLEAN, HasHalo, __get_HasHalo, __set_HasHalo, 0xC8);
		/// @brief 识别 ID.
		INT_READONLY_PROPERTY(Id, __get_Id, 0xD4);
		READONLY_PROPERTY_BINDING(int, __get_Index, Id & 0xFFFF) Index;
		void Collect();
		void Die();
	};
}