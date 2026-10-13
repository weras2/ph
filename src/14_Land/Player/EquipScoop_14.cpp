#include "Player/EquipScoop.hpp"

THUMB EquipScoop::EquipScoop() {}

THUMB EquipScoop::~EquipScoop() {}

ARM ItemFlag EquipScoop::GetId() const {
    return ItemFlag_Shovel;
}
