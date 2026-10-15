#include "DTCM/UnkStruct_027e0fe0.hpp"
#include "System/SysNew.hpp"

extern "C" {
void func_0202d108(unk32 param1, unk32 param2, unk32 param3, UnkStruct_027e0fe0 *param4, unk32 *param5);
void func_0202d140(UnkStruct_027e0fe0 *param1, unk32 *param2);
void func_0202ec18(UnkStruct_027e0fe0_Unk10 *param1, unk32 param2, u32 *param3, unk32 param4);
void func_0202ec3c(UnkStruct_027e0fe0_Unk10 *param1);
}

THUMB void UnkStruct_027e0fe0::Init() {
    mUnk_00        = NULL;
    mUnk_04        = 0;
    mUnk_08        = 0;
    mUnk_0c        = 0;
    mUnk_10.mUnk_0 = 0;
    mUnk_10.mUnk_4 = 0;
}

THUMB UnkStruct_027e0fe0 *UnkStruct_027e0fe0::Dispose() {
    if (mUnk_00 != NULL) {
        func_0202ea98();
    }
    func_0202ec3c(&mUnk_10);
    return this;
}

THUMB void UnkStruct_027e0fe0::func_0202ea50(unk32 param1, unk32 param2, unk32 param3) {
    func_0202d108(param1, param2, param3, this, &mUnk_04);
    mUnk_00->mMagic = 'UNSH';
    mUnk_00->mOwner = this;
    mUnk_08         = param2;
    mUnk_0c         = mUnk_00->mUnk_28;
    func_0202ec18(&mUnk_10, param1, data_027e0ce0[1], param2);
}

THUMB void UnkStruct_027e0fe0::func_0202ea98() {
    func_0202ec3c(&mUnk_10);
    mUnk_0c         = 0;
    mUnk_08         = 0;
    mUnk_00->mMagic = 'UNTH';
    func_0202d140(this, &mUnk_04);
}
