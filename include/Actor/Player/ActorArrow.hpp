#pragma once

#include "global.h"
#include "nds/math.h"
#include "types.h"

#include "Actor/Actor.hpp"
#include "Actor/ActorType.hpp"
#include "Player/EquipRope.hpp"

class ItemModel;
class ModelRender;

extern "C" void func_ov000_020bd618(void *param1, ItemModel *model, u16 param3, u16 param4);
extern "C" void func_ov000_020b3ea8(void *param1);

// Small render object (vtable compatible with ModelRender)
struct ActorArrow_Model {
    /* 00 */ unk32 mUnk_00[3];
    /* 0c */

    inline ActorArrow_Model(ItemModel *model, u16 param2, u16 param3) {
        func_ov000_020bd618(this, model, param2, param3);
    }
};

class ActorArrow : public Actor {
public:
    static ActorType gType;

    /* 000 (base) */
    /* 158 */ Vec3p mUnk_158;
    /* 164 */ ActorRef mUnk_164;
    /* 16c */ ActorArrow_Model mUnk_16c;
    /* 178 */ ActorArrow_Model mUnk_178;
    /* 184 */ ModelRender *mUnk_184;
    /* 188 */ Actor_UnkStruct_0a4 mUnk_188;
    /* 19c */ s32 mUnk_19c;
    /* 1a0 */ s32 mSpeed;
    /* 1a4 */ s32 mUnk_1a4;
    /* 1a8 */ s32 mUnk_1a8;
    /* 1ac */ s16 mUnk_1ac;
    /* 1ae */ s16 mUnk_1ae;
    /* 1b0 */ s16 mUnk_1b0;
    /* 1b2 */ s16 mUnk_1b2;
    /* 1b4 */ bool mUnk_1b4;
    /* 1b5 */ bool mUnk_1b5;
    /* 1b6 */ bool mUnk_1b6;
    /* 1b7 */ bool mUnk_1b7;
    /* 1b8 */

    /* 00 */ virtual ~ActorArrow() override;
    /* 08 */ virtual bool Init() override;
    /* 10 */ virtual void vfunc_10(u32 param1) override;
    /* 14 */ virtual void vfunc_14(u32 param1) override;
    /* 18 */ virtual void vfunc_18(u32 param1) override;
    /* 20 */ virtual void vfunc_20(bool param1) override;
    /* 44 */ virtual bool CollidesWith(Actor *other) override;
    /* 48 */ virtual bool vfunc_48(Knockback *param1) override;
    /* b4 */

    static ActorArrow *Create();
    static void func_ov014_0211fd80(unk32 param1);
    static void func_ov014_0211fd90();
    ActorArrow();
    void func_ov014_021200d4();
    void func_ov014_02120118();
    bool func_ov014_02120180();
    static EquipRope *GetEquipRope();
    void func_ov014_021207b8(ActorRef *ref, s32 param2, s32 param3);
    void func_ov014_02120998(ActorRef *ref, Vec3p pos, s16 param3);
    void func_ov014_02120ac4(s16 angle, bool param2);
    void func_ov014_02120c98(Vec3p *param1);
    void func_ov014_02120d58();
    void func_ov014_02120da8();
    bool func_ov014_02120dec(s32 state);
};
