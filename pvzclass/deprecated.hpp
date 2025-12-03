#pragma once
#include "PVZ.h"
#include "utils.h"

/// @deprecated 请使用 PVZEnum::ReanimLoopType 替代
#define APA_LOOP			(PVZEnum::ReanimLoopType)1
/// @deprecated 请使用 PVZEnum::ReanimLoopType 替代
#define APA_ONCE_DISAPPEAR	(PVZEnum::ReanimLoopType)2
/// @deprecated 请使用 PVZEnum::ReanimLoopType 替代
#define APA_ONCE_STOP		(PVZEnum::ReanimLoopType)3

/// @deprecated 请使用 PVZ::DamageRangeFlags 替代
#define HZC_COMMON 1
/// @deprecated 请使用 PVZ::DamageRangeFlags 替代
#define HZC_BALLOON_AIR 2
/// @deprecated 请使用 PVZ::DamageRangeFlags 替代
#define HZC_SNORKED_UNDER 4
/// @deprecated 请使用 PVZ::DamageRangeFlags 替代
#define HZC_NOT_GROUNDED 16
/// @deprecated 请使用 PVZ::DamageRangeFlags 替代
#define HZC_DYING 32
/// @deprecated 请使用 PVZ::DamageRangeFlags 替代
#define HZC_DIGGER_UNDER 64
/// @deprecated 请使用 PVZ::DamageRangeFlags 替代
#define HZC_HYPNOTIZED 128

/// @deprecated
#define VASE_OPEN INVOKE_DWORD_DWORD(0x429AC0,0,0)
/// @deprecated
#define GRIDITEM_REMOVE INVOKE(0x44D000)