#pragma once

#include "types.h"

#include "Player/EquipItem.hpp"
#include "Player/EquipRope.hpp"
#include "Render/ModelRender.hpp"

struct EquipSword_Effect {
    /* 00 */ unk8 mUnk_00[0x24];
    /* 24 */ u32 mUnk_24_0 : 1;
    /* 24 */ u32 mUnk_24_1 : 1;
    /* 24 */ u32 mUnk_24_2 : 1;
    /* 24 */ u32 mUnk_24_3 : 29;
    /* 28 */ unk8 mUnk_28[0x28];
    /* 50 */ s16 mUnk_50[3];
    /* 56 */ s16 mUnk_56;
};

class EquipSword : public EquipItem {
public:
    /* 00 (base) */
    /* 09 */ unk8 mUnk_09[3]; // padding?
    /* 0c */ ModelRender *mUnk_0c;
    /* 10 */ ModelRender *mUnk_10;
    /* 14 */ ModelRender *mUnk_14;
    /* 18 */ ModelRender *mUnk_18;
    /* 1c */ void *mUnk_1c;
    /* 20 */ void *mUnk_20;
    /* 24 */ void *mUnk_24;
    /* 28 */ void *mUnk_28;
    /* 2c */ EquipSword_Effect *mUnk_2c;
    /* 30 */ EquipSword_Effect *mUnk_30;
    /* 34 */ EquipSword_Effect *mUnk_34;
    /* 38 */ unk8 mUnk_38[8];
    /* 40 */ s32 mUnk_40;
    /* 44 */ s32 mUnk_44;
    /* 48 */ s32 mUnk_48;
    /* 4c */ s32 mUnk_4c;
    /* 50 */ s32 mUnk_50;
    /* 54 */ s16 mUnk_54;
    /* 56 */ s16 mUnk_56;
    /* 58 */ s16 mUnk_58;
    /* 5a */ s16 mUnk_5a;
    /* 5c */ s16 mUnk_5c;
    /* 5e */ unk8 mUnk_5e[2];
    /* 60 */ Vec3p mUnk_60;
    /* 6c */ bool mUnk_6c;
    /* 6d */ bool mUnk_6d;
    /* 6e */ bool mUnk_6e;
    /* 6f */ unk8 mUnk_6f;
    /* 70 */

public:
    EquipSword();

    /* 00 */ virtual void vfunc_00() override;
    /* 04 */ virtual ~EquipSword() override;
    /* 0c */ virtual ItemFlag GetId() const override;
    /* 10 */ virtual void vfunc_10() override;

    /* 18 */ virtual void vfunc_18() override;
    /* 1c */ virtual void vfunc_1c() override;

    /* 28 */ virtual bool UpdateInUse(unk32 param1) override;
    /* 2c */ virtual u32 vfunc_2c() override;
    /* 30 */ virtual void vfunc_30() override;
    /* 38 */ virtual void vfunc_38(unk32 param1) override;
    /* 3c */ virtual bool GetHitbox(Cylinder *hitbox) const override;
    /* 50 */

    void func_ov000_020bf008(s16 param1, s16 param2);
    bool func_ov000_020bf028();
    void func_ov000_020bf088();
    void func_ov000_020bf330();
    bool func_ov000_020bf4f4();
    static EquipRope *GetEquipRope();
    void func_ov000_020c024c(Vec3p *param1, s32 param2);
    void func_ov000_020c0318(Vec3p *param1, s32 param2);
    void func_ov000_020c0550(Vec3p *param1, s32 param2);
    void func_ov000_020c05ec(s32 param1);
    void func_ov000_020c0648();
    void func_ov000_020c06b0(s32 param1);
};
