#pragma once

#include "types.h"

#include "Player/EquipItem.hpp"
#include "Render/ModelRender.hpp"

class EquipBow : public EquipItem {
public:
    static ModelRender gModelRenderBow;
    static ModelRender gModelRenderArrow;

    /* 00 (base) */
    /* 09 */ u8 mUnk_09;
    /* 0a */ bool mUnk_0a;
    /* 0b */ bool mUnk_0b;
    /* 0c */ bool mUnk_0c;
    /* 0d */ unk8 mUnk_0d[3];
    /* 10 */

    // The destructor is declared first so that the vtable is emitted with it (in ov014)
    /* 04 */ virtual ~EquipBow() override;
    /* 0c */ virtual ItemFlag GetId() const override;
    /* 00 */ virtual void vfunc_00() override;
    /* 14 */ virtual bool IsUsable(unk32 param1) const override;
    /* 18 */ virtual void vfunc_18() override;
    /* 30 */ virtual void vfunc_30() override;
    /* 38 */ virtual void vfunc_38(unk32 param1) override;
    /* 50 */

    EquipBow();

    bool func_ov056_02198ee8();
    void func_ov056_02198f48(u16 param1);
    bool func_ov056_021992f8();
};
