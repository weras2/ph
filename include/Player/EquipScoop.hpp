#pragma once

#include "types.h"

#include "Player/EquipItem.hpp"
#include "Render/ModelRender.hpp"

class LinkStateItem;

class EquipScoop : public EquipItem {
public:
    static ModelRender gModelRender;

    /* 0 (base) */
    /* 9 */ unk8 mUnk_9[3];
    /* c */

    /* 04 */ virtual ~EquipScoop() override;
    /* 00 */ virtual void vfunc_00() override;
    /* 0c */ virtual ItemFlag GetId() const override;
    /* 14 */ virtual bool IsUsable(unk32 param1) const override;
    /* 18 */ virtual void vfunc_18() override;
    /* 30 */ virtual void vfunc_30() override;
    /* 38 */ virtual void vfunc_38(unk32 param1) override;
    /* 40 */ virtual unk32 vfunc_40() const override;
    /* 44 */ virtual unk32 vfunc_44(unk32 param1) const override;
    /* 48 */ virtual unk32 vfunc_48(unk32 param1) const override;
    /* 50 */

    EquipScoop();

    s32 func_ov054_02198e08(Vec3p *param1);
    bool func_ov054_021980e24(Vec3p *param1);
};
