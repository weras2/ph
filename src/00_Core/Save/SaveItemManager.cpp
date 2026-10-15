#include "Save/SaveItemManager.hpp"

extern "C" void Fill(void *dst, int value, int size);

THUMB void SaveInventory::Init() {
    Fill256(0, this, 0xa8);
    Fill(this->shipParts, 0xff, sizeof(this->shipParts));
    Fill(this->treasure, 0xff, sizeof(this->treasure));
    this->hourglassSeconds = 600;
    this->unk_90           = 12;
    this->unk_91           = 12;
    this->unk_92           = 5;
    this->equippedFairy    = 3;
    this->equippedItem     = -1;
}
