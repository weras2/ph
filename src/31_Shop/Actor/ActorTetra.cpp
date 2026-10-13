#include "Actor/Character/ActorTetra.hpp"
#include "Save/AdventureFlags.hpp"
#include "nds/math.h"

struct UnkStruct_027e0fec {
    /* 000 */ PAD(0x000, 0xc10);
    /* c10 */ ActorTetra_Palette *mUnk_c10;
};

extern "C" {
void func_ov014_02145ae8(ActorCharacter_1d8 *param1, unk32 param2, const void *param3, const void *param4);
void func_ov014_02146120(ActorCharacter_1d8 *param1, unk32 param2);
void CleanDataCacheLines(void *ptr, u32 size);
void func_02017d30(unk32 param1, u32 param2, void *param3, u32 param4);
}

extern u32 **data_027e0fe0[];
extern UnkStruct_027e0fec *data_027e0fec;
extern const unk32 data_ov031_02181b24[];
extern const unk32 data_ov031_02181b30[];
extern unk32 data_ov031_02183d68;
extern unk32 data_ov031_02183d6c;

ARM ActorTetra *ActorTetra::Create() {
    return new(*data_027e0fe0[0], 4) ActorTetra();
}

ARM bool ActorTetra::vfunc_f4() {
    if (gAdventureFlags->Get(AdventureFlag_Unk_328)) {
        return false;
    }
    mUnk_1d8.func_ov014_02145a74(0x37, 0x37);
    func_ov014_02145ae8(&mUnk_1d8, 0x37, &data_ov031_02183d68, &data_ov031_02183d6c);
    this->func_ov014_021451f0(data_ov031_02181b24);
    mUnk_448 = 4;
    if (mUnk_020.mUnk_00[0] == 0 && mUnk_020.mUnk_00[2] == 1) {
        mUnk_1d8.mUnk_18          = data_ov031_02181b30;
        mUnk_1d8.mUnk_020.mUnk_8e = 1;
        func_ov014_02146120(&mUnk_1d8, 0);
        mUnk_469            = true;
        mUnk_468            = true;
        mUnk_4b0.mPrevBlend = 0;
        mUnk_4b0.mBlend     = 0x1000;
    }
    mUnk_4b0.func_ov031_02181610(data_027e0fec->mUnk_c10, 0x800, 0x800, 0x800, 0x318c);
    return true;
}

ARM void ActorTetra::vfunc_c4() {
    if (mUnk_020.mUnk_00[0] == 0 && mUnk_020.mUnk_00[2] == 1) {
        mUnk_1d8.mUnk_10->mUnk_0c.mUnk_04 = 0;
    }
    ActorGenericCharacter::vfunc_c4();
}

ARM void ActorTetra::vfunc_20(bool param1) {
    if (param1 ? mUnk_0a4.mUnk_01 : mUnk_0a4.mUnk_00) {
        ActorCharacter::vfunc_20(param1);
        mUnk_4b0.func_ov031_02181798();
    }
}

static inline s32 GetColorFactor(s32 scale, s32 component) {
    return (scale * (s32) CoDivide64By32(0x1f000, (component + 31) << 12) + 0x800) >> 12;
}

ARM void ActorTetra_4b0::func_ov031_02181610(ActorTetra_Palette *palette, s32 redScale, s32 greenScale, s32 blueScale,
                                             u16 color) {
    mUnk_08 = (u16 *) ((u8 *) palette + palette->mColorsOffset);
    mUnk_18 = (u16) palette->mUnk_2c << 3;

    u32 size = palette->mNumColors << 3;
    if (mSize < size) {
        size = mSize;
    }
    if (size < mSize) {
        mSize = size;
    }

    s32 green = (color & 0x3e0) >> 5;
    s32 blue  = (color & 0x7c00) >> 10;
    s32 count = size >> 1;
    u16 *src  = mUnk_08;
    u16 *dst  = mUnk_0c->mColors;

    s32 redFactor   = GetColorFactor(redScale, color & 0x1f);
    s32 greenFactor = GetColorFactor(greenScale, green);
    s32 blueFactor  = GetColorFactor(blueScale, blue);

    for (s32 i = 0; i < count; i++) {
        u16 c = *src;
        src++;
        s32 sum = (c & 0x1f) + ((c >> 5) & 0x1f) + ((c >> 10) & 0x1f);
        s32 r   = (sum * redFactor + ((color & 0x1f) << 12)) >> 12;
        s32 g   = (sum * greenFactor + (green << 12)) >> 12;
        s32 b   = (sum * blueFactor + (blue << 12)) >> 12;
        if (r > 31) {
            r = 31;
        }
        if (g > 31) {
            g = 31;
        }
        if (b > 31) {
            b = 31;
        }
        *dst = r | (g << 5) | (b << 10);
        dst++;
    }
    CleanDataCacheLines(mUnk_0c, size);
}

ARM void ActorTetra_4b0::func_ov031_02181798() {
    if (mBlend == mPrevBlend) {
        return;
    }
    mPrevBlend = mBlend;

    s32 count = mSize >> 1;
    u16 *from = mUnk_08;
    u16 *to   = mUnk_0c->mColors;
    u16 *dst  = mUnk_10->mColors;
    for (s32 i = 0; i < count; i++) {
        u16 t = *to;
        to++;
        u16 f = *from;
        from++;
        s32 r = ((f & 0x1f) * (0x1000 - mBlend) + (t & 0x1f) * mBlend) >> 12;
        s32 g = (((f & 0x3e0) >> 5) * (0x1000 - mBlend) + ((t & 0x3e0) >> 5) * mBlend) >> 12;
        s32 b = (((f & 0x7c00) >> 10) * (0x1000 - mBlend) + ((t & 0x7c00) >> 10) * mBlend) >> 12;
        *dst  = r | (g << 5) | (b << 10);
        dst++;
    }
    CleanDataCacheLines(mUnk_10, mSize);
    func_02017d30(1, mUnk_18, mUnk_10, mSize);
}

ARM ActorTetra::~ActorTetra() {}

ARM void ActorTetra::vfunc_f8() {}
