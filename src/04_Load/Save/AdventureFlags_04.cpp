#include "Map/Exit.hpp"
#include "Map/MapManager.hpp"
#include "Save/AdventureFlags.hpp"

struct UnkStruct_ov000_020eab04 {
    /* 0 */ UnkStruct_027e0d38_UnkC mUnk_0;
    /* 4 */ u8 mUnk_4;
    /* 5 */ u8 mUnk_5;
};
extern UnkStruct_ov000_020eab04 data_ov000_020eab04;

extern "C" void Fill32(unk32, u32 *, unk32);
extern "C" void func_ov000_020a01c4(s32 param1, s32 param2);
extern "C" void func_ov000_020a021c();

#define INIT_FLAGS_UNK2(s)      \
    s.mUnk_00.mUnk_00   = 0x47; \
    s.mUnk_04.mUnk_00.x = 0;    \
    s.mUnk_04.mUnk_00.y = 0;    \
    s.mUnk_04.mUnk_00.z = -2;   \
    s.mUnk_04.mUnk_0c   = 0;    \
    s.mUnk_04.mUnk_0e   = -1;   \
    s.mUnk_04.mUnk_0f   = 0;    \
    s.mUnk_04.mUnk_10   = 0;    \
    s.mUnk_04.mUnk_11   = 0;

THUMB AdventureFlags::AdventureFlags() {
    Fill32(0, mFlags.data, sizeof(mFlags));
    mCutsceneHandler = new(data_027e0ce0[1], 4) CutsceneHandler();
    mUnk_44          = new(data_027e0ce0[1], 4) AdventureFlags_44(mCutsceneHandler);
    Load();
}

THUMB AdventureFlags::~AdventureFlags() {
    if (mUnk_44 != NULL) {
        delete mUnk_44;
        mUnk_44 = NULL;
    }
    if (mCutsceneHandler != NULL) {
        delete mCutsceneHandler;
        mCutsceneHandler = NULL;
    }
    func_ov004_021046d4();
}

THUMB void AdventureFlags::Create() {
    if (gAdventureFlags == NULL) {
        gAdventureFlags = new(data_027e0ce0[1], 4) AdventureFlags();
    }
}

THUMB void AdventureFlags::Destroy() {
    if (gAdventureFlags != NULL) {
        delete gAdventureFlags;
        gAdventureFlags = NULL;
    }
}

THUMB void AdventureFlags::func_ov004_021044f8(s32 param1) {
    FlagsUnk2 *flags = (FlagsUnk2 *) param1;
    if (flags->mUnk_04.mUnk_00.y == 1) {
        func_ov004_021046c8((u16) (Get_FlagsUnk_40(flags->mUnk_04.mUnk_00.z) + 0x200));
    } else {
        func_ov004_021046c8(0x20);
    }
    mCutsceneHandler->func_ov004_0210f3e4(param1);
    mUnk_44->func_ov000_0209906c();
    func_ov00_020976c8();
}

THUMB void AdventureFlags::func_ov004_0210453c() {
    mCutsceneHandler->func_ov000_02098618(1, 0, NULL);
    mCutsceneHandler->func_ov004_0210f46c();
    mUnk_44->func_ov000_02099070();
    func_ov004_021046d4();
}

THUMB bool AdventureFlags::func_ov004_0210455c(s32 param1) {
    FlagsUnk2 *flags = (FlagsUnk2 *) param1;
    if (flags->mUnk_04.mUnk_00.y != 1) {
        return false;
    }
    s32 index = flags->mUnk_04.mUnk_00.z;
    if (index < 0 || index >= 33) {
        return false;
    }
    if (Get_FlagsUnk_30_Flag(index)) {
        return false;
    }

    FlagsUnk2 saved;
    INIT_FLAGS_UNK2(saved);
    if (!Get_FlagsUnk_00(index, &saved)) {
        return false;
    }
    if (flags->mUnk_00.func_ov000_020a5e9c() == saved.mUnk_00.func_ov000_020a5e9c() &&
        flags->mUnk_04.mUnk_0e == saved.mUnk_04.mUnk_0e && flags->mUnk_04.mUnk_00.y == saved.mUnk_04.mUnk_00.y) {
        UnkStruct_ov000_0209a50c params;
        params.mUnk_09 = 15;
        params.mUnk_0a = 0;
        params.mUnk_0b = 0;
        Vec3p center;
        gMapManager->GetMapCenter(&center);
        params.mUnk_20 = center.x;
        params.mUnk_24 = center.y;
        params.mUnk_28 = center.z;

        FlagsUnk2 exit;
        INIT_FLAGS_UNK2(exit);
        Get_FlagsUnk_18(index, &exit);
        if (exit.mUnk_00.func_ov000_020a5e9c() == 0x47) {
            FlagsUnk2 fallback;
            INIT_FLAGS_UNK2(fallback);
            fallback.mUnk_00         = data_ov000_020eab04.mUnk_0;
            fallback.mUnk_04.mUnk_0e = data_ov000_020eab04.mUnk_4;
            fallback.mUnk_04.mUnk_0f = data_ov000_020eab04.mUnk_5;
            exit                     = fallback;
        }
        params.mUnk_0f           = gMapManager->func_ov00_020838f8((Exit *) &exit);
        CutsceneHandler *handler = mCutsceneHandler;
        handler->mFlags1 |= 1;
        handler->mFlags2 |= 1;
        gAdventureFlags->func_ov00_02097a44(index, (s32) &params);
        return true;
    }
    return false;
}

THUMB void AdventureFlags::func_ov004_021046c8(s32 param1) {
    func_ov000_020a01c4(param1, 0x40);
}

THUMB void AdventureFlags::func_ov004_021046d4() {
    func_ov000_020a021c();
}
