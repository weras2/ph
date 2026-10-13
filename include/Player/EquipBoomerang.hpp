#pragma once

#include "global.h"
#include "types.h"

#include "Actor/ActorRef.hpp"
#include "Map/TilePos.hpp"
#include "Player/EquipItem.hpp"
#include "Render/ModelRender.hpp"

class Actor;

struct EquipBoomerang_Point {
    /* 00 */ Vec3p mPos;
    /* 0c */ unk32 mUnk_0c;
    /* 10 */
};

class EquipBoomerang : public EquipItem {
public:
    /* 00 (base) */
    /* 09 */ u8 mUnk_09[3];
    /* 0c */ ModelRender *mUnk_0c;
    /* 10 */ ActorRef mRef;
    /* 18 */ s32 mUnk_18;
    /* 1c */ s32 mUnk_1c;
    /* 20 */ unk32 mUnk_20;
    /* 24 */ unk32 mUnk_24;
    /* 28 */ EquipBoomerang_Point *mUnk_28;
    /* 2c */ s16 mUnk_2c;
    /* 2e */ unk8 mUnk_2e[2];
    /* 30 */

public:
    /* 04 */ virtual ~EquipBoomerang() override;
    /* 0c */ virtual ItemFlag GetId() const override;
    /* 10 */ virtual void vfunc_10() override;
    /* 14 */ virtual bool IsUsable(unk32 param1) const override;
    /* 18 */ virtual void vfunc_18() override;
    /* 1c */ virtual void vfunc_1c() override;
    /* 28 */ virtual bool UpdateInUse(unk32 param1) override;
    /* 30 */ virtual void vfunc_30() override;
    /* 38 */ virtual void vfunc_38(unk32 param1) override;
    /* 50 */

    EquipBoomerang();
    void func_ov014_0213d098();
    void func_ov014_0213d0bc(Vec3p *param1);
    Actor *GetActor();
    bool func_ov014_0213d184(s32 *param1);
    void func_ov014_0213d1b0();

    static void func_ov053_02199014(void *param1);
    static void func_ov053_02199020(void *param1);
    EquipBoomerang_Point *func_ov053_0219902c(s32 param1);
    void func_ov053_02199038();
    void func_ov053_021990f0(TilePos param1);
    bool func_ov053_02199128(s32 *param1);
    void func_ov053_02199168();
    void func_ov053_021991ec();
    void func_ov053_02199410(s32 param1);
    bool func_ov053_021994cc(Vec3p *param1);
};
