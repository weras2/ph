#include "Player/PlayerManager.hpp"
#include "Item/ItemManager.hpp"

extern "C" void Copy16(const void *src, void *dst, u32 size);

THUMB void PlayerManager::Save(SaveItemManager *save) {
    save->inventory.unk_90 = mMaxHealth;
    save->inventory.unk_91 = mHealth < 12 ? 12 : mHealth;
    save->inventory.unk_92 = mSalvageArmHealth;
    save->inventory.unk_a6 = mFlags;
    Copy16(&mUnk_0c, &save->inventory.unk_7c, 4);
    gItemManager->Save(save);
}

THUMB void PlayerManager::IncreaseMaxHealth(s16 amount) {
    mMaxHealth += amount;
    if (mMaxHealth > 64) {
        mMaxHealth = 64;
    }
}

THUMB void PlayerManager::UpdateShipMaxHealth() {
    s32 typeCounts[ShipType_COUNT];
    for (s32 i = 0; i < ShipType_COUNT; i++) {
        typeCounts[i] = 0;
    }
    for (s32 i = 0; i < ShipPart_COUNT; i++) {
        typeCounts[gItemManager->GetEquippedShipPart(i)]++;
    }

    s32 health = 16;
    for (s32 i = 1; i < ShipType_COUNT - 1; i++) {
        s32 count = typeCounts[i];
        if (count >= 8) {
            health += 12;
        } else if (count >= 6) {
            health += 8;
        } else if (count >= 3) {
            health += 4;
        }
    }
    s32 count = typeCounts[ShipType_COUNT - 1];
    if (count >= 8) {
        health += 16;
    } else if (count >= 6) {
        health += 12;
    } else if (count >= 4) {
        health += 8;
    } else if (count >= 2) {
        health += 4;
    }
    mMaxShipHealth = health;
}
