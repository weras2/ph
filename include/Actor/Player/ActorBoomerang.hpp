#pragma once

#include "global.h"
#include "nds/math.h"
#include "types.h"

#include "Actor/Actor.hpp"
#include "Unknown/UnkStruct_ov000_020beba8.hpp"

class ActorBoomerang_Unk_0219a15c : public UnkStruct_ov000_020beba8 {
public:
    /* 0 (base) */
    /* c */ unk32 mUnk_c;
    /* 10 */

    /* 18 */ virtual bool vfunc_18(s32 *param1) override;
    /* 1c */

    inline ActorBoomerang_Unk_0219a15c() :
        UnkStruct_ov000_020beba8(1) {
        mUnk_c = 0;
    }
};

extern "C" void func_ov000_020bd618(void *param1, ItemModel *param2, unk32 param3, unk32 param4);

struct ActorBoomerang_158 {
    /* 0 */ unk8 mUnk_0[0xc];
    /* c */

    inline ActorBoomerang_158(ItemModel *model) {
        func_ov000_020bd618(this, model, 0, 0);
    }
};

struct ActorBoomerang_170 {
    /* 0 */ unk32 mUnk_0;
    /* 4 */ s32 mUnk_4;
    /* 8 */ unk32 mUnk_8;
    /* c */

    ActorBoomerang_170();
    ~ActorBoomerang_170();
};

class ActorBoomerang : public Actor {
public:
    /* 000 (base) */
    /* 158 */ ActorBoomerang_158 mUnk_158;
    /* 164 */ u16 mUnk_164;
    /* 166 */ s16 mUnk_166;
    /* 168 */ bool mUnk_168;
    /* 169 */ unk8 mUnk_169[3];
    /* 16c */ unk32 mUnk_16c;
    /* 170 */ ActorBoomerang_170 mUnk_170[1];
    /* 17c */

    /* 00 */ virtual ~ActorBoomerang() override;
    /* 08 */ virtual bool Init() override;

    ActorBoomerang();
    bool func_ov053_02199c48(u16 param1);
    void func_ov053_02199cc8(Vec3p *param1);

    void func_ov014_021230a8(Vec3p *param1);
    void func_ov014_0212322c();
    void func_ov014_0212357c(s32 param1);
    void func_ov014_021235bc(Vec3p *param1, s32 param2);
};
