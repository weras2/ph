#include "Player/EquipBomb.hpp"

THUMB EquipBomb::EquipBomb() {}

ARM ItemFlag EquipBomb::GetId() const {
    return ItemFlag_BombBag;
}

ARM EquipBomb::~EquipBomb() {}

ARM unk32 EquipBomb::vfunc_50() {
    return 99;
}
