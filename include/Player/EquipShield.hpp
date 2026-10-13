#pragma once

#include "types.h"

#include "Player/EquipItem.hpp"
#include "Render/ModelRender.hpp"
#include "Unknown/UnkStruct_ov000_020c0c08.hpp"

class EquipShield : public EquipItem {
public:
    /* 00 (base) */
    /* 09 */ bool mUnk_09;
    /* 0a */ bool mUnk_0a;
    /* 0b */ bool mUnk_0b;
    /* 0c */ bool mUnk_0c;
    /* 0d */ bool mUnk_0d;
    /* 0e */ s16 mUnk_0e;
    /* 10 */ ModelRender *mUnk_10;
    /* 14 */ UnkStruct_ov000_020c0c08 *mUnk_14;
    /* 18 */ unk32 mUnk_18;
    /* 1c */ ModelRender *mUnk_1c;
    /* 20 */ UnkStruct_ov000_020c0c08 *mUnk_20;
    /* 24 */ UnkStruct_ov000_020c0c08 *mUnk_24;
    /* 28 */ UnkStruct_ov000_020c0c08 *mUnk_28;
    /* 2c */

public:
    EquipShield();

    /* 00 */ virtual void vfunc_00() override;
    /* 04 */ virtual ~EquipShield() override;
    /* 0c */ virtual ItemFlag GetId() const override;
    /* 10 */ virtual void vfunc_10() override;
    /* 14 */ virtual bool IsUsable(unk32 param1) const override;
    /* 18 */ virtual void vfunc_18() override;
    /* 1c */ virtual void vfunc_1c();
    /* 30 */ virtual void vfunc_30() override;
    /* 38 */ virtual void vfunc_38(unk32 param1) override;
    /* 3c */ virtual bool GetHitbox(Cylinder *hitbox) const;
    /* 50 */

    void func_ov000_020c070c(u32 param1, Vec3p *param2, unk32 param3);
};
