#include "Game/GameModeBattle.hpp"
#include "Game/Game.hpp"
#include "System/SysNew.hpp"
#include "Unknown/UnkStruct_020ee698.hpp"
#include "nds/heap.h"

struct UnkStruct_ov012_02137c60 {
    /* 0 */ void *mUnk_0;
    /* 4 */ GameModeBattle *mUnk_4;
    /* 8 */
};

extern UnkStruct_ov012_02137c60 data_ov012_02137c60;

extern "C" {
void Fill16(int value, unsigned short *dst, int size);
void func_0202f194(void *param1, unk32 param2, unk32 param3);
void func_0202f1f0(void *param1);
void func_ov012_0211bce8(void *param1);
void func_ov012_0211bf34(void *param1);
void func_ov012_0211f824(void *param1);
void func_ov012_0211fa34(void *param1);
void func_ov012_0211fa8c(void *param1, unk32 param2);
void func_ov012_0211fa98(void *param1);
void func_ov000_0207a4f0(void *param1);
void func_ov001_020f8434(void *param1);
void func_ov012_0212dcd8(void *param1);
void func_ov012_0212dd04(void *param1);
bool func_0202d0cc(u32 *heap, u32 *pSize);
void *func_ov061_021792ec();
void func_ov012_02112ca8();
void func_02004b94();
void func_02004ba8();
void func_02004bbc();
void func_02004be0();
void func_02004c68();
void func_02004c7c();
void func_02004c90();
void func_02004cb8();
void func_ov012_021132d4(GameModeBattle *param1);
void func_ov012_0211c4dc(void *param1, bool param2);
bool func_ov012_0211c1c4(void *param1);
void func_ov012_0212c434(unk32 param1);
void func_ov012_0212003c(void *param1, unk32 param2);
void func_ov012_0211fed4(void *param1, unk32 param2, unk32 param3);
bool func_ov012_0211cc60(void *param1);
unk32 func_ov012_0211fad0(void *param1, bool param2);
void func_ov012_0211c778(void *param1);
void func_0202bac4();
void func_ov012_0211fe08(void *param1, u16 *param2);
void func_ov012_0211fe30(void *param1, u16 *param2);
void func_ov012_0211ce44(void *param1);
void func_ov012_0211feac(void *param1, u16 *param2);
}

ARM GameModeBattle *GameModeBattle::Create(unk32 param1) {
    return new(data_027e0ce0[1], 4) GameModeBattle(param1);
}

ARM GameModeBattle::GameModeBattle(unk32 param1) :
    GameModePlay(param1) {
    func_0202f194(&mUnk_008, 0x800, 0x200);
    func_ov012_0211bce8(&mUnk_0d4);
    func_ov012_0211f824(&mUnk_7f0);
    Fill16(0, mUnk_88c, sizeof(mUnk_88c));
    func_ov000_0207a4f0(&mUnk_8a2);
    Fill16(0, mUnk_880, 0x44);
    func_ov001_020f8434(&mUnk_8c4);
    func_ov001_020f8434(&mUnk_91a);
    func_ov012_0212dcd8(&mUnk_970);
    mUnk_994 = 1;
    mUnk_998 = 1;
    mUnk_99c = 0;
    mUnk_99d = 0;
    mUnk_99e = 0;

    data_ov012_02137c60.mUnk_4 = this;
    mUnk_990                   = 0x3e;

    u32 size;
    if (func_0202d0cc(data_027e0ce0[1], &size)) {
        data_ov012_02137c60.mUnk_0 = Heap_EXPHNew((Heap_Header *) data_027e0ce0[1], size, 4);
    }

    switch (data_ov000_020ee698.mUnk_0c.mUnk_2c) {
        case 2:
            *(void (**)())((u8 *) func_ov061_021792ec() + 0xe1c) = func_ov012_02112ca8;
            func_ov012_0211fa8c(&mUnk_7f0, 7);
            break;
        case 1:
            func_ov012_0211fa8c(&mUnk_7f0, 6);
            break;
        case 0:
            func_ov012_0211fa8c(&mUnk_7f0, 0);
            break;
        case 3:
            func_ov012_0211fa8c(&mUnk_7f0, 8);
            break;
        default:
            func_ov012_0211fa8c(&mUnk_7f0, 8);
            break;
    }
}

ARM GameModeBattle::~GameModeBattle() {
    func_ov012_0211fa98(&mUnk_7f0);
    this->vfunc_18();
    if (data_ov000_020ee698.mUnk_0c.mUnk_2c == 2) {
        *(void **) ((u8 *) func_ov061_021792ec() + 0xe1c) = NULL;
    }
    if (data_ov012_02137c60.mUnk_0 != NULL) {
        Heap_EXPHFreeBlock((Heap_Header *) data_027e0ce0[1], data_ov012_02137c60.mUnk_0);
        data_ov012_02137c60.mUnk_0 = NULL;
    }
    data_ov000_020ee698.mUnk_02         = 0;
    data_ov000_020ee698.mUnk_0c.mUnk_2c = 4;
    func_02004b94();
    func_02004ba8();
    func_02004bbc();
    func_02004be0();
    func_02004c68();
    func_02004c7c();
    func_02004c90();
    func_02004cb8();
    data_ov012_02137c60.mUnk_4 = NULL;
    func_ov012_0212dd04(&mUnk_970);
    func_ov012_0211fa34(&mUnk_7f0);
    func_ov012_0211bf34(&mUnk_0d4);
    func_0202f1f0(&mUnk_008);
}

ARM void GameModeBattle::vfunc_24() {
    func_ov012_021132d4(data_ov012_02137c60.mUnk_4);
}

ARM unk32 GameModeBattle::vfunc_08(bool param1) {
    unk32 result;
    s32 retries = 0;

    while (true) {
        func_ov012_0211c4dc(&mUnk_0d4, mUnk_864 == 3 || mUnk_864 == 8);
        if (func_ov012_0211c1c4(&mUnk_0d4)) {
            func_ov012_0212c434(mUnk_0d8->mUnk_04);
            func_ov012_0212003c(&mUnk_7f0, 2);
            if (mUnk_99e) {
                func_ov012_0211fed4(&mUnk_7f0, 5, 1);
            }
        }
        if (retries == 0) {
            if (!func_ov012_0211cc60(&mUnk_0d4)) {
                retries = 1;
            } else {
                result = func_ov012_0211fad0(&mUnk_7f0, param1);
            }
        }
        func_ov012_0211c778(&mUnk_0d4);
        if (retries == 0) {
            break;
        }
        retries--;
        for (u16 i = gGame.mUnk_0f2; i != 0; i--) {
            func_0202bac4();
        }
    }
    return result;
}

ARM void GameModeBattle::vfunc_0c(u16 *param1) {
    func_ov012_0211fe08(&mUnk_7f0, param1);
}

ARM void GameModeBattle::vfunc_10(u16 *param1) {
    func_ov012_0211fe30(&mUnk_7f0, param1);
    func_ov012_0211ce44(&mUnk_0d4);
}

ARM void GameModeBattle::vfunc_14(u16 *param1) {
    func_ov012_0211feac(&mUnk_7f0, param1);
}

ARM void GameModeBattle::vfunc_18() {
    mUnk_0d8->vfunc_1c();
}
