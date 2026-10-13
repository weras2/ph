#pragma once

#include "global.h"
#include "types.h"

#include "nds/math.h"

#include "System/SysNew.hpp"

class MapData : public SysObject {
public:
    /* 00 */ u8 mUnk_00;
    /* 01 */ s8 mMap;
    /* 02 */ u16 mUnk_02;
    /* 04 */ u16 mUnk_04;
    /* 06 */ unk8 mUnk_06[2];
    /* 08 */ unk32 mUnk_08;
    /* 0c */ unk32 mUnk_0c;
    /* 10 */ unk8 mGridX;
    /* 11 */ unk8 mGridY;
    /* 12 */ unk8 mUnk_12[2];
    /* 14 */ Vec3p mCenter;
    /* 20 */ unk32 mFlags0[1];
    /* 24 */ unk32 mFlags1[8];
    /* 44 */ unk32 mFlags2[2];
    /* 4c */ unk32 mFlags3[2];
    /* 54 */ unk32 mFlags4[1];
    /* 58 */

    MapData(u8 *map, unk8 x, unk8 y, unk32 param4, unk32 param5);
    ~MapData();
    void func_ov000_020972e4(u16 *param1, unk32 *param2, bool param3);
    void func_ov000_02097354();
    void SetFlag0(u32 index, bool value);
    bool GetFlag0(u32 index);
    void SetFlag1(u32 index, bool value);
    bool GetFlag1(u32 index);
    void SetFlag2(u32 index, bool value);
    bool GetFlag2(u32 index);
    void SetFlag3(u32 index, bool value);
    bool GetFlag3(u32 index);
    void SetFlag4(u32 index, bool value);
    bool GetFlag4(u32 index);
};
