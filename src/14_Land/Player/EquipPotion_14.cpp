#include "Item/ItemManager.hpp"
#include "Player/EquipPotion.hpp"
#include "Player/PlayerLinkBase.hpp"

static char *gShipParts[8] = {"anc", "bow", "hul", "can", "dco", "pdl", "fnl", "brg"};

THUMB EquipPotion::EquipPotion(s32 index) {
    mUnk_0c = index;
}

THUMB EquipPotion::~EquipPotion() {}

THUMB EquipPotionA::EquipPotionA() :
    EquipPotion(0) {}

THUMB EquipPotionA::~EquipPotionA() {}

ARM ItemFlag EquipPotionA::GetId() const {
    return ItemFlag_PotionA;
}

THUMB EquipPotionB::EquipPotionB() :
    EquipPotion(1) {}

THUMB EquipPotionB::~EquipPotionB() {}

ARM ItemFlag EquipPotionB::GetId() const {
    return ItemFlag_PotionB;
}

ARM bool EquipPotion::IsUsable(unk32 param1) const {
    if (!gPlayerLink->func_ov000_020bba28() || ((u16) gPlayerLink->mUnk_48 & 0x3f) != 0) {
        return false;
    }
    switch (gItemManager->HasPotion(mUnk_0c)) {
        case 1:
        case 2:
        case 3:
            return true;
        case 0:
        default:
            return false;
    }
}
