#include "Player/EquipBomb.hpp"
#include "Actor/ActorManager.hpp"
#include "Actor/ActorSpawner.hpp"
#include "Item/ItemManager.hpp"
#include "Player/LinkStateInteract.hpp"
#include "Player/LinkStateItem.hpp"
#include "Player/PlayerControl.hpp"
#include "Unknown/UnkStruct_02037750.hpp"

ModelRender EquipBomb::gModelRender(0);

ARM void EquipBomb::vfunc_00() {
    gModelRender.Init_RenderObject(gItemManager->GetItemModel(ItemModelId_Bomb));
}

ARM bool EquipBomb::IsUsable(unk32 param1) const {
    if (this->GetAmmo() > 0) {
        for (const ActorRef *bomb = mBombs; bomb != &mBombs[MAX_BOMB_ACTORS]; bomb++) {
            if (bomb->id == -1) {
                return true;
            }
        }
        return param1 == 0;
    }
    return false;
}

ARM void EquipBomb::vfunc_18() {
    this->UpdateInUse(1);
}

ARM void EquipBomb::vfunc_30() {
    for (ActorRef *bomb = mBombs; bomb != &mBombs[MAX_BOMB_ACTORS]; bomb++) {
        if (bomb->id != -1 && gActorManager->GetActor(bomb) == NULL) {
            bomb->Reset();
        }
    }
}

ARM void EquipBomb::vfunc_38(unk32 param1) {
    if (!this->IsInUse()) {
        return;
    }
    Vec3p pos;
    this->func_ov000_020be99c(&pos);
    pos.y += 0xb85;
    pos.z += 0x200;
    gModelRender.func_ov000_020b413c(mUnk_04, &pos);
}

ARM Actor *EquipBomb::func_ov055_02198e60() {
    if (this->GetAmmo() <= 0) {
        return NULL;
    }

    Vec3p pos = *this->GetPlayerPos();
    pos.y += FLOAT_TO_Q20(1.0);
    ActorSpawnOptions options;
    options.mUnk_1c.id         = 1;
    options.mAngle             = mUnk_04;
    options.mUnk_00.mUnk_00[0] = 0;

    ActorRef *bomb;
    for (bomb = mBombs; bomb != &mBombs[MAX_BOMB_ACTORS]; bomb++) {
        if (bomb->id == -1) {
            gActorSpawner->Spawn(ActorTypeId_Bomb, &pos, &options, bomb);
            break;
        }
    }
    if (bomb->id != -1) {
        this->GiveAmmo(-1);
    }
    this->UpdateInUse(0);
    return gActorManager->GetActor(bomb);
}

static LinkStateBase_UnkStruct1 data_ov055_02199840 = {0x1e, {FLOAT_TO_Q20(1.6), FLOAT_TO_Q20(2.0), FLOAT_TO_Q20(10.0)}};

ARM void LinkStateItem::func_ov055_02198f78() {
    this->func_ov00_020a89bc(&data_ov055_02199840, 1);
}

EquipBomb *GetEquipBomb();

ARM void LinkStateItem::StopUsingBomb(s32 param1) {
    if (param1 != 0 && param1 != 5) {
        return;
    }
    if (this->GetGrabActor() != NULL) {
        return;
    }
    if (!gPlayerControl->mUsingEquipItem) {
        return;
    }
    Actor *bomb              = GetEquipBomb()->func_ov055_02198e60();
    *this->GetGrabActorRef() = bomb->mRef;
    bomb->Grab();
    gPlayerControl->UpdateUsingEquipItem();
}

ARM EquipBomb *GetEquipBomb() {
    return (EquipBomb *) ItemManager::GetEquipItemUnchecked(ItemFlag_BombBag);
}

ARM void LinkStateItem::func_ov055_02199020() {
    if (data_ov055_02199840.mUnk_00 == this->Get_PlayerControlData_Unk100() && this->func_ov00_020a8b3c(0)) {
        this->func_ov005_02110228(0, 0, 0, 1, 0);
        return;
    }

    Actor *bomb = NULL;
    if (this->func_ov00_020a8b80()) {
        Vec3p offset;
        if (gPlayerControl->func_ov00_020b05e8(&offset)) {
            bomb = GetEquipBomb()->func_ov055_02198e60();
            Vec3p_Add(&offset, this->GetPlayerPos(), &mUnk_38);
            UnkStruct_02037750::GetLinkStateInteract()->SetNormalizedThrowOffset(&mUnk_38);
        } else if (gPlayerControl->func_ov00_020b049c(&offset, false)) {
            bomb = GetEquipBomb()->func_ov055_02198e60();
            Vec3p_Add(&offset, this->GetPlayerPos(), &mUnk_38);
            UnkStruct_02037750::GetLinkStateInteract()->SetThrowOffset(&mUnk_38);
        }
    }

    if (bomb != NULL) {
        *this->GetGrabActorRef() = bomb->mRef;
        bomb->Grab();
        gPlayerControl->UpdateUsingEquipItem();
        this->ChangeLinkState(LinkStateId_Interact);
        return;
    }
    this->func_ov005_0210f808(gPlayerControl->func_ov00_020b034c(), NULL, 1);
}
