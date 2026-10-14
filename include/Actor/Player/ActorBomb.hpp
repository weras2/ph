#pragma once

#include "global.h"
#include "nds/math.h"
#include "types.h"

#include "Actor/Actor.hpp"
#include "Actor/ActorType.hpp"
#include "Unknown/UnkStruct_ov000_020beba8.hpp"
#include "Unknown/UnkStruct_ov000_020c0c08.hpp"

class ActorBomb_Unk1 : public UnkStruct_ov000_020beba8 {
public:
    /* 00 (base) */
    /* 0c */ unk32 mUnk_0c;
    /* 10 */

    /* 00 */ virtual ~ActorBomb_Unk1() override;
    /* 08 */ virtual bool vfunc_0c(unk16 *param1) override;
    /* 0c */ virtual bool vfunc_10(s32 *param1) override;
    /* 18 */

    inline ActorBomb_Unk1() :
        UnkStruct_ov000_020beba8(2) {
        mUnk_0c = 0;
    }
};

class ActorBomb_Unk2 {
public:
    /* 0 */ unk32 mUnk_0;
    /* 4 */ unk32 mUnk_4;
    /* 8 */ unk32 mUnk_8;
    /* c */

    ActorBomb_Unk2();
    ~ActorBomb_Unk2();
};

// Animation player; its vtable is emitted where it is constructed
class UnkStruct_ov000_020a9b2c : public UnkStruct_ov000_020c0c08 {
public:
    inline UnkStruct_ov000_020a9b2c(UnkStruct_ov000_020c0c08_04 *param1, ItemModel *param2) :
        UnkStruct_ov000_020c0c08(param1, param2) {}
};

class ModelRender;

class ActorBomb : public Actor {
public:
    static ActorType gType;

    /* 000 (base) */
    /* 158 */ s32 mUnk_158; // fuse timer
    /* 15c */ unk32 mUnk_15c[0x1a]; // storage for the model render object
    /* 1c4 */ ModelRender *mUnk_1c4;
    /* 1c8 */ UnkStruct_ov000_020a9b2c mUnk_1c8;
    /* 1ec */ UnkStruct_ov000_020c0c08_04 mUnk_1ec;
    /* 20c */ unk8 mUnk_20c[0x20];
    /* 22c */ ActorBomb_Unk2 mUnk_22c[2];
    /* 244 */ const Vec3p *mUnk_244;
    /* 248 */ Vec3p mUnk_248;
    /* 254 */ Vec3p mUnk_254;
    /* 260 */ q20 mUnk_260;
    /* 264 */ s32 mUnk_264;
    /* 268 */ s16 mUnk_268;
    /* 26a */ bool mUnk_26a;
    /* 26b */ unk8 mUnk_26b;
    /* 26c */

    /* 00 */ virtual ~ActorBomb() override;
    /* 08 */ virtual bool Init() override;
    /* 14 */ virtual void vfunc_14(u32 param1) override;
    /* 18 */ virtual void vfunc_18(u32 param1) override;
    /* 20 */ virtual void vfunc_20(bool param1) override;
    /* 54 */ virtual void vfunc_54() override;
    /* 5c */ virtual bool Drop(Vec3p *vel) override;
    /* b4 */

    static ActorBomb *Create();
    ActorBomb();
    bool func_ov014_02122bb8(s32 state);
    void func_ov014_02122e48(unk32 *param1);
    bool func_ov014_02122e7c();
    void func_ov014_02122e98();
    bool func_ov014_02122eb8();
    bool func_ov014_02122ed4();
};
