#include "Player/EquipBow.hpp"

THUMB EquipBow::EquipBow() {
    mUnk_09 = 0;
    mUnk_0a = 0;
}

THUMB EquipBow::~EquipBow() {}

ARM ItemFlag EquipBow::GetId() const {
    return ItemFlag_Bow;
}
