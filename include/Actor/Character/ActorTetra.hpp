#pragma once

#include "global.h"
#include "types.h"

#include "Actor/ActorType.hpp"
#include "Actor/Character/ActorCharacter.hpp"

// Palette resource, colors are stored as RGB555
struct ActorTetra_Palette {
    /* 00 */ PAD(0x00, 0x2c);
    /* 2c */ u32 mUnk_2c;
    /* 30 */ u16 mNumColors;
    /* 32 */ PAD(0x32, 0x38);
    /* 38 */ u32 mColorsOffset;
    /* 3c */
};

struct ActorTetra_4cc {
    /* 000 */ u16 mColors[0x4e0];
    /* 9c0 */
};

struct ActorTetra_4b0 {
    /* 00 */ s32 mBlend; // 0x1000 = fully mUnk_0c, 0 = fully mUnk_08
    /* 04 */ s32 mPrevBlend;
    /* 08 */ u16 *mUnk_08;
    /* 0c */ ActorTetra_4cc *mUnk_0c;
    /* 10 */ ActorTetra_4cc *mUnk_10;
    /* 14 */ u32 mSize;
    /* 18 */ u32 mUnk_18;
    /* 1c */

    inline ActorTetra_4b0(ActorTetra_4cc *unk_0c, ActorTetra_4cc *unk_10, u32 size) :
        mBlend(0),
        mPrevBlend(0),
        mUnk_0c(unk_0c),
        mUnk_10(unk_10),
        mSize(size) {}

    void func_ov031_02181610(ActorTetra_Palette *palette, s32 redScale, s32 greenScale, s32 blueScale, u16 color);
    void func_ov031_02181798();
};

class ActorTetra : public ActorGenericCharacter {
public:
    static ActorType gType;

    /* 0000 (base) */
    /* 049c */ PAD(0x49c, 0x4b0);
    /* 04b0 */ ActorTetra_4b0 mUnk_4b0;
    /* 04cc */ ActorTetra_4cc mUnk_4cc;
    /* 0e8c */ ActorTetra_4cc mUnk_e8c;
    /* 184c */

    /* 00 */ virtual ~ActorTetra() override;
    /* 20 */ virtual void vfunc_20(bool param1) override;
    /* c4 */ virtual void vfunc_c4() override;
    /* f4 */ virtual bool vfunc_f4() override;
    /* f8 */ virtual void vfunc_f8() override;
    /* fc */

    static ActorTetra *Create();
    inline ActorTetra() :
        mUnk_4b0(&mUnk_4cc, &mUnk_e8c, sizeof(mUnk_4cc)) {}
};
