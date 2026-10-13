#include "DTCM/UnkStruct_027e077c.hpp"
#include "DTCM/UnkStruct_027e103c.hpp"
#include "DTCM/UnkStruct_027e1098.hpp"
#include "Item/ItemManager.hpp"
#include "Map/MapManager.hpp"
#include "Player/EquipBombchu.hpp"
#include "Player/LinkStateInteract.hpp"
#include "Player/LinkStateItem.hpp"
#include "Player/PlayerControl.hpp"
#include "Unknown/UnkStruct_02037750.hpp"

static char *gShipParts[8] = {"anc", "bow", "hul", "can", "dco", "pdl", "fnl", "brg"};

EquipBombchu *GetEquipBombchu();
extern LinkStateBase_UnkStruct1 data_ov058_0219af58;

ARM void LinkStateItem::func_ov058_0219a454() {
    this->func_ov00_020a89bc(&data_ov058_0219af58, 1);
    data_027e1098->func_ov058_0219acac();
}

LinkStateBase_UnkStruct1 data_ov058_0219af58 = {0x1e, {0x1999, FLOAT_TO_Q20(2.0), FLOAT_TO_Q20(10.0)}};

ARM void LinkStateItem::func_ov058_0219a47c() {
    if (data_027e077c.mUnk_0 != 13) {
        return;
    }
    if (*(u8 *) (data_027e103c->func_ov000_020cf01c() + 0xe0) == 0) {
        return;
    }

    mUnk_24        = 0;
    Actor *bombchu = ::GetEquipBombchu()->func_ov058_02199400();
    if (bombchu != NULL) {
        *this->GetGrabActorRef() = bombchu->mRef;
        bombchu->Grab();
        TilePos tile = *(TilePos *) ::GetEquipBombchu()->func_ov014_0213ed94(0);
        Vec3p pos    = bombchu->mPos;
        gMapManager->func_ov00_02083c7c(&pos, tile);
        UnkStruct_02037750::GetLinkStateInteract()->SetNormalizedThrowOffset(&pos);
        this->LookAt(&pos);
        PlayerControl *control   = gPlayerControl;
        control->mUsingEquipItem = false;
        control->mUnk_7b         = false;
        this->ChangeLinkState(LinkStateId_Interact);
        bombchu->mAngle = *(s16 *) this->GetPlayerAngle();
        ::GetEquipBombchu()->func_ov014_0213ec40();
    } else {
        this->func_ov005_02105d94();
    }
}

ARM EquipBombchu *GetEquipBombchu() {
    return (EquipBombchu *) ItemManager::GetEquipItemUnchecked(ItemFlag_BombchuBag);
}
