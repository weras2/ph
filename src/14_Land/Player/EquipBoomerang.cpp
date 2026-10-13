#include "Player/EquipBoomerang.hpp"
#include "Actor/ActorManager.hpp"
#include "Item/ItemManager.hpp"
#include "Player/PlayerLinkBase.hpp"
#include "System/OverlayManager.hpp"

static char *gShipParts[8] = {"anc", "bow", "hul", "can", "dco", "pdl", "fnl", "brg"};

extern "C" void func_ov000_020bd944(unk32 *param1);

THUMB EquipBoomerang::EquipBoomerang() {
    mUnk_18 = 0;
    mUnk_1c = 0;
    func_ov000_020bd944(&mUnk_20);
    mUnk_2c = 0;
    mUnk_0c = new(data_027e0ce0[1], 4) ModelRender(NULL);
}

THUMB EquipBoomerang::~EquipBoomerang() {
    if (mUnk_0c != NULL) {
        delete mUnk_0c;
    }
    this->func_ov014_0213d098();
}

ARM bool EquipBoomerang::UpdateInUse(unk32 param1) {
    return EquipItem::UpdateInUse(param1);
}

THUMB void EquipBoomerang::vfunc_10() {
    mUnk_0c->Init_RenderObject(gItemManager->GetItemModel(ItemModelId_Boomerang));
}

ARM void EquipBoomerang::func_ov014_0213d098() {
    if (mRef.id == -1) {
        return;
    }
    mRef.Reset();
    mUnk_20 = 0;
}

ARM void EquipBoomerang::func_ov014_0213d0bc(Vec3p *param1) {
    if (gPlayerLink->GetCurrentCharacter() == PlayerCharacter_Gongoron) {
        ActorRef ref = gActorManager->FindActorByType(ActorTypeId_PlayerDummy);
        Actor *actor = gActorManager->GetActor(&ref);
        param1->x    = actor->mPos.x;
        param1->y    = actor->mPos.y;
        param1->z    = actor->mPos.z;
    } else {
        Vec3p *pos = this->GetPlayerPos();
        param1->x  = pos->x;
        param1->y  = pos->y;
        param1->z  = pos->z;
    }
    param1->y += FLOAT_TO_Q20(0.5);
}

ARM Actor *EquipBoomerang::GetActor() {
    return gActorManager->GetActor(&mRef);
}

ARM ItemFlag EquipBoomerang::GetId() const {
    return ItemFlag_Boomerang;
}

ARM bool EquipBoomerang::func_ov014_0213d184(s32 *param1) {
    if (OverlayId_PlayerBoomerang != gOverlayManager.mLoadedOverlays[OverlayIndex_EquipItem]) {
        return false;
    }
    return this->func_ov053_02199128(param1);
}

ARM void EquipBoomerang::func_ov014_0213d1b0() {
    mUnk_18 = 0;
    mUnk_1c = 0;
    mUnk_20 = 0;
}
