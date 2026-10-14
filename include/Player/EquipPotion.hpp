#pragma once

#include "types.h"

#include "Player/EquipItem.hpp"

class EquipPotion : public EquipItem {
private:
    /* 00 (base) */
    /* 09 */ unk8 mUnk_09[3];
    /* 0c */ unk32 mUnk_0c;
    /* 10 */

public:
    /* 04 */ virtual ~EquipPotion() override;
    /* 00 */ virtual void vfunc_00() override;
    /* 14 */ virtual bool IsUsable(unk32 param1) const override;
    /* 18 */ virtual void vfunc_18() override;
    /* 1c */ virtual void vfunc_1c() override;
    /* 30 */ virtual void vfunc_30() override;
    /* 38 */ virtual void vfunc_38(unk32 param1) override;
    /* 50 */

    EquipPotion(s32 index);
};

class EquipPotionA : public EquipPotion {
public:
    /* 04 */ virtual ~EquipPotionA() override;
    /* 0c */ virtual ItemFlag GetId() const override;
    /* 50 */

    EquipPotionA();
};

class EquipPotionB : public EquipPotion {
public:
    /* 04 */ virtual ~EquipPotionB() override;
    /* 0c */ virtual ItemFlag GetId() const override;
    /* 50 */

    EquipPotionB();
};
