#pragma once

#include "global.h"
#include "types.h"

#include "Map/TriggerAABB.hpp"
#include "Map/TriggerAABB_Unk2.hpp"

class TriggerAABB_Unk1 : public TriggerAABB {
public:
    /* 00 (base) */
    /* 2c */ bool mUnk_2c;
    /* 2d */ unk8 mUnk_2d[3];
    /* 30 */ TriggerAABB_Unk2_Unk1 mUnk_30;
    /* 5c */

    /* 00 */ virtual ~TriggerAABB_Unk1() override;
    /* 08 */ virtual void vfunc_08() override;
    /* 1c */

    TriggerAABB_Unk1(TriggerParams *params);
};
