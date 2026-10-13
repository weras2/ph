#include "Unknown/UnkStruct_ov058_0219afb0.hpp"
#include "DTCM/UnkStruct_027e077c.hpp"
#include "DTCM/UnkStruct_027e0c38.hpp"
#include "DTCM/UnkStruct_027e0d38.hpp"
#include "DTCM/UnkStruct_027e103c.hpp"
#include "DTCM/UnkStruct_027e1098.hpp"
#include "Game/Game.hpp"
#include "Item/ItemManager.hpp"
#include "Message/MsgProc.hpp"
#include "Player/EquipBombchu.hpp"
#include "Player/PlayerBase.hpp"
#include "Player/PlayerControl.hpp"
#include "Player/TouchControl.hpp"
#include "Unknown/UnkStruct_020ee6f8.hpp"
#include "Unknown/UnkStruct_020eec9c.hpp"
#include "nds/math.h"

static char *gShipParts[8] = {"anc", "bow", "hul", "can", "dco", "pdl", "fnl", "brg"};

extern void *data_027e0d3c;

extern "C" {
void func_ov000_0207c0ac(unk32 *param1, s32 param2, unk32 param3);
void func_ov000_0207c0cc(unk32 *param1);
void func_ov000_020d00c4(UnkStruct_ov058_0219afb0_08 *param1, unk32 param2, s32 param3, UnkStruct_01ffbe34 *param4,
                         unk32 param5);
void func_ov000_020d054c(s16 *param1);
void func_ov000_020d0594(s16 *param1);
s32 func_ov000_020d03f8(s32 param1, s32 param2, s32 param3);
void func_ov000_0207914c(void *param1, Vec3p *param2, s32 *param3, s32 *param4, unk32 param5);
bool func_ov000_02078fd4(void *param1);
s32 func_ov000_02078fac(void *param1);
void func_ov000_020d61b0(UnkStruct_020ee6f8 *param1, s32 param2, s32 param3, s32 param4);
void func_ov000_020792a0(void *param1, unk32 param2, s32 param3, s32 param4, Vec3p *param5);
void func_ov000_020791dc(void *param1, Vec3p *param2, s32 *param3, unk32 param4);
void func_ov005_0210cc00(UnkStruct_027e1098 *param1, s32 *param2);
void func_ov000_02079b78(UnkStruct_027e1098 *param1);
}

EquipBombchu *GetEquipBombchu();

ARM void UnkStruct_ov058_0219afb0::func_ov058_0219a5c8() {
    s32 id = -1;
    switch (data_027e0cbc.mUnk_1c) {
        case 0:
            id = 0x22;
            break;
        case 1:
            id = 0x23;
            break;
        case 2:
            id = 0x24;
            break;
        case 3:
            id = 0x25;
            break;
    }
    func_ov000_0207c0ac(&mUnk_04, id, 0);

    mUnk_d8 = mUnk_da;
    mUnk_de = false;
    mUnk_df = false;
    mUnk_e0 = false;

    if (data_027e0c38.mUnk_10 == 0) {
        mUnk_50.func_020350b4(3, 4, 0, 0, 0);
    } else {
        mUnk_50.func_020350b4(3, 5, 0, 0, 0);
    }
    mUnk_50.func_020351b8(false, false, false, false);
}

ARM bool UnkStruct_ov058_0219afb0::vfunc_00() {
    bool result = false;

    if (data_027e077c.mUnk_0 == 13) {
        for (s32 i = 0; i < 3; i++) {
            if (!(mUnk_08[i].vfunc_00(0, 0, 0) & 8)) {
                continue;
            }
            if (i != 0 && i != 1) {
                if (i == 2 && mUnk_df) {
                    continue;
                }
            } else if (!mUnk_df) {
                continue;
            }
            result = result || this->func_ov058_0219a76c(mUnk_08[i].mUnk_0a);
        }
    }
    return result;
}

ARM bool UnkStruct_ov058_0219afb0::func_ov058_0219a76c(u16 param1) {
    switch (param1) {
        case 0x40:
            data_ov000_020eec9c.func_ov000_020d77e4(17);
            PlayerControl *control   = gPlayerControl;
            control->mUsingEquipItem = false;
            control->mUnk_7b         = false;
            return true;
        case 0x41:
            data_ov000_020eec9c.func_ov000_020d77e4(5);
            mUnk_df = false;
            data_027e1098->func_ov058_0219ad34();
            return true;
        case 0x42:
            data_ov000_020eec9c.func_ov000_020d77e4(4);
            mUnk_df = false;
            mUnk_e0 = true;
            func_ov000_0207c0cc(&mUnk_04);
            return true;
    }
    return false;
}

ARM void UnkStruct_ov058_0219afb0::vfunc_04(bool param1) {
    if (param1) {
        return;
    }

    mUnk_50.func_0203516c();

    if (!mUnk_df) {
        if (!mUnk_de && data_027e077c.mUnk_0 == 13 && (gTouchControl.mFlags & TouchFlag_TouchedNow)) {
            s32 x;
            s32 y;
            func_ov000_0207914c(data_027e0d3c, &gPlayerPos, &x, &y, 0);
            if (ABS(x - gTouchControl.mTouchX) <= 8 && ABS(y - gTouchControl.mTouchY) <= 8) {
                mUnk_de = true;
            }
        } else if (mUnk_de && !gTouchControl.mTouch) {
            mUnk_de = false;
        }
    }

    switch (data_027e077c.mUnk_0) {
        case 11:
        case 12:
            mUnk_d8 = mUnk_da;
            break;
        case 13:
            if (((EquipBombchu *) gItemManager->GetEquipItem(ItemFlag_BombchuBag))->mUnk_18 > 0 || mUnk_df) {
                func_ov000_020d0594(&mUnk_d8);
            } else {
                func_ov000_020d054c(&mUnk_d8);
            }
            break;
        case 14:
        case 15:
            func_ov000_020d0594(&mUnk_d8);
            break;
    }
}

ARM void UnkStruct_ov058_0219afb0::func_ov058_0219a998() {
    if (gGame.mUnk_101 != 0) {
        return;
    }

    s32 state = data_027e077c.mUnk_0;
    if (state != 12 && state != 13 && state != 14) {
        return;
    }

    func_ov000_020d00c4(&mUnk_08[2], 0, this->func_ov058_0219aad0(), NULL, 0);

    if (mUnk_df) {
        UnkStruct_01ffbe34 local;
        func_01ffbe34(&local);
        local.mUnk_04 = 0;
        func_ov000_020d00c4(&mUnk_08[0], 0, 0, &local, 0);
        func_ov000_020d00c4(&mUnk_08[1], 0, 0, &local, 0);
        return;
    }

    if (state != 13) {
        return;
    }
    UnkStruct_027e1098 *unk = data_027e1098;
    if (mUnk_de) {
        return;
    }
    if (unk->mUnk_34 > 0) {
        return;
    }

    s32 x = 0;
    s32 y = 0;
    func_ov000_0207914c(data_027e0d3c, &gPlayerPos, &x, &y, 0);
    mUnk_50.func_02034a1c(x, y, NULL);
}

ARM s32 UnkStruct_ov058_0219afb0::func_ov058_0219aad0() {
    s32 t;
    if (mUnk_d8 == mUnk_da) {
        t = 0;
    } else if (mUnk_d8 == mUnk_dc) {
        t = 0x1000;
    } else {
        t = CoDivide64By32((mUnk_d8 - mUnk_da) << 12, (mUnk_dc - mUnk_da) << 12);
    }
    return (func_ov000_020d03f8(0x20000, 0, t) + 0x800) >> 12;
}

THUMB void UnkStruct_027e1098::func_ov058_0219ab28() {
    switch (data_027e077c.mUnk_0) {
        case 51:
            if (func_ov000_02078fd4(data_027e0d3c)) {
                break;
            }
            if (mUnk_4a <= 1) {
                mUnk_4a = 0;
                data_027e077c.func_0202e740(11);
            } else {
                mUnk_4a--;
            }
            break;
        case 12:
            if (!func_ov000_02078fd4(data_027e0d3c) && func_ov000_02078fac(data_027e0d3c) == 1) {
                data_027e077c.func_0202e740(13);
            }
            break;
        case 13: {
            if (!gTouchControl.mTouch) {
                break;
            }
            if (!mUnk_38->mUnk_de) {
                break;
            }
            if (gItemManager->mEquippedItem != ItemFlag_BombchuBag) {
                break;
            }
            if ((s16) data_027e103c->mUnk_1c == 64) {
                break;
            }
            if (mUnk_34 >= mUnk_2c) {
                break;
            }
            EquipBombchu *bombchu = (EquipBombchu *) gItemManager->GetEquipItem(ItemFlag_BombchuBag);
            if (bombchu == NULL) {
                break;
            }
            s32 touchX = gTouchControl.mTouchX;
            s32 touchY = gTouchControl.mTouchY;
            func_ov000_020d61b0(&data_ov000_020ee6f8, touchX, touchY, 30);
            Vec3p pos;
            Vec3p touchPos;
            func_ov000_020792a0(data_027e0d3c, 1, touchX, touchY, &touchPos);
            pos.x = touchPos.x;
            pos.y = touchPos.y;
            pos.z = touchPos.z;
            while (mUnk_34 < mUnk_2c && bombchu->func_ov058_02199498(&pos)) {
                s32 tile[2];
                tile[0] = -1;
                tile[1] = -1;
                func_ov000_020791dc(data_027e0d3c, &pos, tile, 0);
                func_ov005_0210cc00(this, tile);
                pos.x = touchPos.x;
                pos.y = touchPos.y;
                pos.z = touchPos.z;
            }
            break;
        }
        case 14:
            if (!func_ov000_02078fd4(data_027e0d3c)) {
                data_027e077c.func_0202e740(15);
            }
            break;
        case 52:
            if (!func_ov000_02078fd4(data_027e0d3c)) {
                data_027e077c.func_0202e740(1);
            }
            break;
    }
}

THUMB void UnkStruct_027e1098::func_ov058_0219acac() {
    if (func_ov000_02078fac(data_027e0d3c) == 2) {
        if (data_027e0d38->mUnk_0c.func_ov000_020a5e9c() == 46) {
            mUnk_49 = 0;
        } else {
            mUnk_49 = 2;
        }
    } else {
        mUnk_49 = 1;
    }
    mUnk_4a = 0;

    if (data_027e077c.mUnk_0 == 1) {
        data_027e077c.func_0202e740(mUnk_49 == 2 ? 51 : 11);
        func_ov000_02079b78(this);
    }

    UnkStruct_ov058_0219afb0 *ui = mUnk_38;
    ui->mUnk_de                  = false;
    ui->mUnk_df                  = false;
    ui->mUnk_e0                  = false;
}

THUMB void UnkStruct_027e1098::func_ov058_0219ad34() {
    func_ov000_02079b78(this);
    mUnk_48 = 0;
    mUnk_3c = 0x1000;
    mUnk_40 = 0x80000;
    mUnk_44 = 0x60000;
    GetEquipBombchu()->func_ov014_0213eda0();
    GetEquipBombchu()->func_ov014_0213ec64();
}
