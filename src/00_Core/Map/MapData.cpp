#include "Map/MapData.hpp"

extern "C" void Fill32(unk32 value, void *dst, unk32 size);

struct MapData_SaveData {
    /* 00 */ unk32 mFlags3[2];
    /* 08 */ unk32 mFlags4;
    /* 0c */
};

struct MapData_Flags3 {
    /* 0 */ unk32 mUnk_0[2];
    /* 8 */
};

extern MapData_SaveData data_ov000_020ea110[];

ARM MapData::MapData(u8 *map, unk8 x, unk8 y, unk32 param4, unk32 param5) {
    mUnk_00   = 0;
    mMap      = map[0];
    mUnk_02   = *(u16 *) (map + 4);
    mUnk_04   = *(u16 *) (map + 6);
    mUnk_08   = param4;
    mUnk_0c   = param5;
    mGridX    = x;
    mGridY    = y;
    mCenter.x = 0;
    mCenter.y = 0;
    mCenter.z = 0;
    Fill32(0, mFlags0, sizeof(mFlags0));
    Fill32(0, mFlags1, sizeof(mFlags1));
    Fill32(0, mFlags2, sizeof(mFlags2));
    Fill32(0, mFlags3, sizeof(mFlags3));
    Fill32(0, mFlags4, sizeof(mFlags4));
}

ARM MapData::~MapData() {}

ARM void MapData::func_ov000_020972e4(u16 *param1, unk32 *param2, bool param3) {
    *param1 = mUnk_02;
    if (param3) {
        param2[2] = mFlags4[0];
        if (mUnk_00) {
            param2[2] |= 0x80000000;
        } else {
            param2[2] &= ~0x80000000;
        }
    } else {
        *(MapData_Flags3 *) param2 = *(MapData_Flags3 *) mFlags3;
        param2[2]                  = mFlags4[0];
        if (mUnk_00) {
            param2[2] |= 0x80000000;
        } else {
            param2[2] &= ~0x80000000;
        }
    }
}

ARM void MapData::func_ov000_02097354() {
    if (mUnk_02 != 0xffff) {
        MapData_SaveData *save      = &data_ov000_020ea110[mUnk_02];
        *(MapData_Flags3 *) mFlags3 = *(MapData_Flags3 *) save->mFlags3;
        mFlags4[0]                  = save->mFlags4;
        mUnk_00                     = save->mFlags4 & 0x80000000 ? 1 : 0;
    } else {
        Fill32(0, mFlags3, sizeof(mFlags3));
        Fill32(0, mFlags4, sizeof(mFlags4));
        mUnk_00 = 0;
    }
    Fill32(0, mFlags2, sizeof(mFlags2));
    Fill32(0, mFlags0, sizeof(mFlags0));
    Fill32(0, mFlags1, sizeof(mFlags1));
}

ARM void MapData::SetFlag0(u32 index, bool value) {
    if (value) {
        mFlags0[index >> 5] |= 1 << (index & 0x1f);
    } else {
        mFlags0[index >> 5] &= ~(1 << (index & 0x1f));
    }
}

ARM bool MapData::GetFlag0(u32 index) {
    return mFlags0[index >> 5] & (1 << (index & 0x1f)) ? true : false;
}

ARM void MapData::SetFlag1(u32 index, bool value) {
    if (value) {
        mFlags1[index >> 5] |= 1 << (index & 0x1f);
    } else {
        mFlags1[index >> 5] &= ~(1 << (index & 0x1f));
    }
}

ARM bool MapData::GetFlag1(u32 index) {
    return mFlags1[index >> 5] & (1 << (index & 0x1f)) ? true : false;
}

ARM void MapData::SetFlag2(u32 index, bool value) {
    if (value) {
        mFlags2[index >> 5] |= 1 << (index & 0x1f);
    } else {
        mFlags2[index >> 5] &= ~(1 << (index & 0x1f));
    }
}

ARM bool MapData::GetFlag2(u32 index) {
    return mFlags2[index >> 5] & (1 << (index & 0x1f)) ? true : false;
}

ARM void MapData::SetFlag3(u32 index, bool value) {
    if (value) {
        mFlags3[index >> 5] |= 1 << (index & 0x1f);
    } else {
        mFlags3[index >> 5] &= ~(1 << (index & 0x1f));
    }
}

ARM bool MapData::GetFlag3(u32 index) {
    return mFlags3[index >> 5] & (1 << (index & 0x1f)) ? true : false;
}

ARM void MapData::SetFlag4(u32 index, bool value) {
    if (value) {
        mFlags4[index >> 5] |= 1 << (index & 0x1f);
    } else {
        mFlags4[index >> 5] &= ~(1 << (index & 0x1f));
    }
}

ARM bool MapData::GetFlag4(u32 index) {
    return mFlags4[index >> 5] & (1 << (index & 0x1f)) ? true : false;
}
