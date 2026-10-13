#include "Player/EquipScoop.hpp"
#include "Actor/ActorManager.hpp"
#include "Actor/FilterActorBase.hpp"
#include "Actor/Navi/ActorNaviBase.hpp"
#include "DTCM/UnkStruct_027e0d38.hpp"
#include "DTCM/UnkStruct_027e0e58.hpp"
#include "DTCM/UnkStruct_027e0fd4.hpp"
#include "Item/ItemManager.hpp"
#include "Map/MapManager.hpp"
#include "Player/LinkStateItem.hpp"
#include "Player/PlayerControl.hpp"
#include "Player/PlayerControlData.hpp"
#include "Unknown/UnkStruct_020eec9c.hpp"
#include "nds/g3d/sbc.h"

struct UnkStruct_02054654 {
    /* 00 */ unk8 mUnk_00[0x1c];
    /* 1c */ s16 mUnk_1c;
    /* 1e */ s16 mUnk_1e;
    /* 20 */
};

struct ScoopFollowObject {
    /* 00 */ unk32 mUnk_00;
    /* 04 */ u32 mFlags;
    /* 08 */ unk8 mUnk_08[0xa];
    /* 12 */ s8 mUnk_12;
    /* 13 */
};

class ScoopActorFilter : public FilterActorBase {
public:
    /* 00 (base) */
    /* 04 */ Vec3p mPos;
    /* 10 */

    /* 0 */ virtual bool Filter(Actor *actor) override;
    /* 4 */
};

extern UnkStruct_02054654 data_02054654;
extern void func_ov000_020b7e6c(s32 *param1);

extern "C" {
void func_ov000_020b41c4(ModelRender *param1);
bool func_ov000_020b1940(s32 param1);
void func_ov000_0207c2e8(UnkStruct_027e0e58 *param1, s32 *param2, unk32 param3, unk32 param4, Vec3p *param5, unk32 param6);
bool func_ov014_021383c0(Actor *param1);
void Vec3p_RotateY(s32 angle, Vec3p *vec);
}

ModelRender EquipScoop::gModelRender(0);

static char *gShipParts[8] = {"anc", "bow", "hul", "can", "dco", "pdl", "fnl", "brg"};

ARM void EquipScoop::vfunc_00() {
    gModelRender.Init_RenderObject(gItemManager->GetItemModel(ItemModelId_Scoop));
}

ARM void EquipScoop::vfunc_18() {}

ARM unk32 EquipScoop::vfunc_40() const {
    return 1;
}

ARM unk32 EquipScoop::vfunc_44(unk32 param1) const {
    return param1 != 0;
}

ARM unk32 EquipScoop::vfunc_48(unk32 param1) const {
    switch (param1) {
        case 0:
        case 1:
        case 11:
            return false;
    }
    return true;
}

ARM bool EquipScoop::IsUsable(unk32 param1) const {
    if (data_027e0fd4->mUnk_05a != 0) {
        return false;
    }
    Actor *followActor           = gPlayerControl->GetFollowActor();
    ScoopFollowObject *followObj = (ScoopFollowObject *) gPlayerControl->mFollowObject;
    if (param1 != 0) {
        if (followActor != NULL || (followObj != NULL && (followObj->mFlags & 4) && this->vfunc_48(followObj->mUnk_12))) {
            return false;
        }
    }
    return EquipItem::IsUsable(1);
}

ARM void EquipScoop::vfunc_30() {}

ARM s32 EquipScoop::func_ov054_02198e08(Vec3p *param1) {
    return gMapManager->func_ov00_02085a34(param1, 1);
}

ARM bool EquipScoop::func_ov054_021980e24(Vec3p *param1) {
    return gMapManager->func_ov00_02085a34(param1, 2) > 0;
}

ARM void EquipScoop::vfunc_38(unk32 param1) {
    if (!this->IsInUse()) {
        return;
    }
    G3d_RestoreMtx_inline(29);
    s32 state = gPlayerControlData->mUnk_100;
    if (!(state != 36 && state != 37 && state != 38)) {
        Mat3p rot;
        Mat3p_InitZRotation(&rot, data_02054654.mUnk_1c, data_02054654.mUnk_1e);
        G3d_MtxMult33_inline(&rot);
    }
    func_ov000_020b41c4(&gModelRender);
}

ARM void func_ov054_02198ee0(s32 param1, s32 *param2) {
    *(s32 *) (param1 + 0x78) = *param2;
}

ARM void LinkStateItem::func_ov054_02198eec() {
    this->func_ov005_0211058c(0);
}

// Animation frames
static s32 data_ov054_021999a0[10] = {0x12000, 0x7b33, 0x7000, 0x1c000, 0x17000, 0x13000, 0x11000, 0x1b000, 0x23000, 0x26000};
static LinkStateBase_UnkStruct1 data_ov054_021999c8 = {0x36, {FLOAT_TO_Q20(1.0), 0, FLOAT_TO_Q20(39.0)}};
static LinkStateBase_UnkStruct1 data_ov054_021999d8 = {0x37, {FLOAT_TO_Q20(1.0), 0, FLOAT_TO_Q20(30.0)}};
static LinkStateBase_UnkStruct1 data_ov054_021999e8 = {0x38, {FLOAT_TO_Q20(1.0), 0, FLOAT_TO_Q20(48.0)}};

ARM bool LinkStateItem::func_ov054_02198efc(s32 param1) {
    if (this->func_ov00_020a8d40()->mUnk_05c <= 0 && this->func_ov005_02106bbc(&mUnk_38) && this->func_ov00_020a8b80()) {
        s32 id        = this->func_ov00_020a8d40()->mUnk_0c0;
        bool isDug    = false;
        bool sameTile = false;
        if (id != -1) {
            TilePos tile = gMapManager->func_ov00_02083a1c(&mUnk_38);
            if (this->func_ov00_020a8d40()->mUnk_0c4 == tile) {
                sameTile = true;
            }
        }
        if (sameTile && !func_ov000_020b1940(id)) {
            isDug = true;
        }

        Vec3p diff = {0, 0, 0};
        diff.x     = mUnk_38.x - this->GetPlayerPos()->x;
        diff.z     = mUnk_38.z - this->GetPlayerPos()->z;
        bool close = Vec3p_Length(&diff) <= FLOAT_TO_Q20(0.2);
        if (isDug || close || Vec3p_Distance(&mUnk_38, this->GetPlayerPos()) < FLOAT_TO_Q20(1.0)) {
            this->LookAt(&mUnk_38);
            this->func_ov00_020a82ac();
            s32 groundType = 0;
            if (!isDug && !close) {
                ScoopActorFilter filter;
                filter.mPos = mUnk_38;
                if (gActorManager->FilterActors(&filter, NULL) <= 0) {
                    groundType = gMapManager->func_ov00_02085594(&mUnk_38);
                }
            }

            if (groundType == 1 || groundType == 3) {
                this->func_ov00_020a89bc(&data_ov054_021999c8, 1);
                s32 y = mUnk_38.y + 0x199;
                data_027e0e58->func_ov000_0207c1b0(0x257, &mUnk_38, 1, (unk32) &y, (unk32) func_ov054_02198ee0);
                data_027e0e58->func_ov000_0207c1b0(0x258, &mUnk_38, 1, (unk32) &y, (unk32) func_ov054_02198ee0);
            } else if (groundType == 2) {
                this->func_ov00_020a89bc(&data_ov054_021999e8, 1);
                func_ov000_0207c2e8(data_027e0e58, mUnk_50, 0x216, 0x217, &mUnk_38, 1);
                data_ov000_020eec9c.func_ov000_020d7a84(0xde, this->GetPlayerPos());
            } else {
                this->func_ov00_020a89bc(&data_ov054_021999d8, 1);
            }

            gPlayerControl->mUnk_7a = false;
            gPlayerControl->mUnk_7b = gPlayerControl->mUsingEquipItem;
            gPlayerControl->StopFollowing();
            ItemManager *itemManager = gItemManager;
            ActorNaviBase *fairy     = itemManager->GetFairy(itemManager->GetEquippedFairy());
            if (fairy != NULL) {
                fairy->func_ov000_020ba3b4();
            }
        } else {
            this->func_ov005_0210f808(FLOAT_TO_Q20(1.0), &mUnk_38, 0);
        }
        return true;
    }

    if (gPlayerControl->GetFollowActor() != NULL) {
        gPlayerControl->UpdateUsingEquipItem();
        return true;
    }
    if ((s32) gPlayerControl->func_ov00_020b034c() >= param1 && mUnk_58 == 0) {
        this->func_ov005_0210f808(gPlayerControl->func_ov00_020b034c(), NULL, 0);
    }
    return false;
}

EquipScoop *GetEquipScoop();

struct UnkStruct_ov054_02199914 {
    /* 00 */ Vec3p mOffset;
    /* 0c */ q20 mUnk_0c;
    /* 10 */
};
static const UnkStruct_ov054_02199914 data_ov054_02199914 = {{0, 0, 0x7ae}, 0x800};

ARM void LinkStateItem::func_ov054_021992c8() {
    Vec3p actorPos;

    if (data_ov054_021999c8.mUnk_00 == this->Get_PlayerControlData_Unk120()) {
        if (this->func_ov00_020a8b3c(0)) {
            this->func_ov005_0211058c(0);
            return;
        }
        if (this->func_ov00_020a8d50() >= data_ov054_021999a0[3]) {
            this->func_ov054_02198efc(FLOAT_TO_Q20(0.8));
            gPlayerControl->mUsingEquipItem = gPlayerControl->mUnk_7b;
            gPlayerControl->mUnk_7a         = true;
        } else if (this->func_ov00_020a8b04(data_ov054_021999a0[0], false)) {
            if (GetEquipScoop()->func_ov054_02198e08(&mUnk_38) != -1) {
                data_ov000_020eec9c.func_ov000_020d7a84(0xdb, &mUnk_38);
            }
        } else if (this->func_ov00_020a8b04(data_ov054_021999a0[1], false)) {
            data_ov000_020eec9c.func_ov000_020d7a84(0xdc, &mUnk_38);
            if (data_027e0d38->mUnk_0c.func_ov000_020a5e9c() == 24) {
                ActorRef ref = gActorManager->FindNearestActorOfType(ActorTypeId_DigSpot, &mUnk_38);
                Actor *actor = gActorManager->GetActor(&ref);
                if (actor != NULL && func_ov014_021383c0(actor)) {
                    actorPos.x = actor->mPos.x;
                    actorPos.y = actor->mPos.y;
                    actorPos.z = actor->mPos.z;
                    if (Vec3p_Distance(&actorPos, &mUnk_38) <= FLOAT_TO_Q20(0.5)) {
                        data_ov000_020eec9c.func_ov000_020d7a84(0x406, &mUnk_38);
                    }
                }
            }
        }
    } else if (data_ov054_021999d8.mUnk_00 == this->Get_PlayerControlData_Unk120()) {
        if (this->func_ov00_020a8b3c(0)) {
            this->func_ov005_0211058c(0);
            return;
        }
        if (this->func_ov00_020a8d50() >= data_ov054_021999a0[4]) {
            this->func_ov054_02198efc(FLOAT_TO_Q20(0.8));
            gPlayerControl->mUsingEquipItem = gPlayerControl->mUnk_7b;
            gPlayerControl->mUnk_7a         = true;
        } else if (this->func_ov00_020a8b04(data_ov054_021999a0[2], false)) {
            data_ov000_020eec9c.func_ov000_020d7a84(0xdd, this->GetPlayerPos());
            Vec3p pos = *this->GetPlayerPos();
            u16 angle = *this->GetPlayerAngle();
            pos.x += MUL_Q20(SIN(angle), FLOAT_TO_Q20(0.5));
            pos.z += MUL_Q20(COS(angle), FLOAT_TO_Q20(0.5));
            data_027e0e58->func_ov000_0207c1b0(0x254, &pos, 1, 0, 0);
            data_027e0e58->func_ov000_0207c1b0(0x255, &pos, 1, 0, 0);
            data_027e0e58->func_ov000_0207c1b0(0x256, &pos, 1, 0, 0);
        }
    } else if (data_ov054_021999e8.mUnk_00 == this->Get_PlayerControlData_Unk120()) {
        if (this->func_ov00_020a8b3c(0)) {
            this->func_ov005_0211058c(0);
            return;
        }
        if (this->func_ov00_020a8d50() >= data_ov054_021999a0[9]) {
            this->func_ov054_02198efc(FLOAT_TO_Q20(0.8));
            gPlayerControl->mUsingEquipItem = gPlayerControl->mUnk_7b;
            gPlayerControl->mUnk_7a         = true;
        } else if (this->func_ov00_020a8b04(data_ov054_021999a0[6], false)) {
            for (s32 *it = mUnk_50; it != &mUnk_50[2]; it++) {
                func_ov000_020b7e6c(it);
            }
        } else if (this->func_ov00_020a8b04(data_ov054_021999a0[7], false) ||
                   this->func_ov00_020a8b04(data_ov054_021999a0[8], false)) {
            Vec3p offset = data_ov054_02199914.mOffset;
            Vec3p_RotateY(*(s16 *) this->GetPlayerAngle(), &offset);
            Vec3p_Add(&offset, this->GetPlayerPos(), &offset);
            data_027e0e58->func_ov000_0207c1b0(0x218, &offset, 1, 0, 0);
        } else if (this->func_ov00_020a8b04(data_ov054_021999a0[5], false)) {
            GetEquipScoop()->func_ov054_021980e24(&mUnk_38);
        }
    } else {
        this->func_ov054_02198efc(0);
    }

    u8 unk                                  = gPlayerControl->mUnk_7a;
    this->func_ov00_020a8d40()->mUnk_0bb[0] = unk;
}

ARM EquipScoop *GetEquipScoop() {
    return (EquipScoop *) ItemManager::GetEquipItemUnchecked(ItemFlag_Shovel);
}

ARM void LinkStateItem::StopUsingScoop() {
    void *followObj = gPlayerControl->mFollowObject;
    TilePos tile;
    if (gPlayerControl->func_ov00_020af01c(&tile)) {
        Vec3p pos;
        gMapManager->func_ov00_02083c7c(&pos, tile);
        bool stop = true;
        if (followObj != NULL) {
            Vec3p tilePos;
            tilePos.x = pos.x;
            tilePos.y = pos.y;
            tilePos.z = pos.z;
            if (!gMapManager->func_ov00_02084ebc(&tilePos)) {
                stop = false;
            }
        }
        if (stop) {
            gPlayerControl->StopFollowing();
        }
    }
    if (!gPlayerControl->mUnk_7a) {
        gPlayerControl->mUsingEquipItem = gPlayerControl->mUnk_7b;
        gPlayerControl->mUnk_7a         = true;
    }
}

ARM bool ScoopActorFilter::Filter(Actor *actor) {
    if (actor->mUnk_12c != 5 && actor->mType != ActorTypeId_Mailbox) {
        return false;
    }
    return Vec3p_Distance(&mPos, &actor->mPos) <= FLOAT_TO_Q20(0.5);
}
