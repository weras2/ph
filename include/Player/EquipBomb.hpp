#pragma once

#include "types.h"

#include "Actor/Actor.hpp"
#include "Actor/ActorRef.hpp"
#include "Player/EquipItem.hpp"
#include "Render/ModelRender.hpp"

#define MAX_BOMB_ACTORS 3

class LinkStateItem;

class EquipBomb : public EquipItem {
public:
    static ModelRender gModelRender;

    /* 00 (base) */
    /* 09 */ unk8 mUnk_09[0x3];
    /* 0c */ ActorRef mBombs[MAX_BOMB_ACTORS];
    /* 24 */

    // The destructor is declared first so that the vtable is emitted with it (in ov014)
    /* 04 */ virtual ~EquipBomb() override;
    /* 0c */ virtual ItemFlag GetId() const override;
    /* 00 */ virtual void vfunc_00() override;
    /* 14 */ virtual bool IsUsable(unk32 param1) const override;
    /* 18 */ virtual void vfunc_18() override;
    /* 30 */ virtual void vfunc_30() override;
    /* 38 */ virtual void vfunc_38(unk32 param1) override;
    /* 50 */ virtual unk32 vfunc_50();
    /* 54 */

    EquipBomb();

    Actor *func_ov055_02198e60();
};
