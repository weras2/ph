#pragma once

#include "Game/GameModePlay.hpp"

class GameModeBattle_0d8 {
public:
    /* 00 (vtable) */
    /* 04 */ unk32 mUnk_04;
    /* 08 */

    /* 00 */ virtual void vfunc_00();
    /* 04 */ virtual void vfunc_04();
    /* 08 */ virtual void vfunc_08();
    /* 0c */ virtual void vfunc_0c();
    /* 10 */ virtual void vfunc_10();
    /* 14 */ virtual void vfunc_14();
    /* 18 */ virtual void vfunc_18();
    /* 1c */ virtual void vfunc_1c();
    /* 20 */
};

class GameModeBattle : public GameModePlay {
public:
    /* 000 (base) */
    /* 008 */ unk8 mUnk_008[0xcc];
    /* 0d4 */ unk32 mUnk_0d4;
    /* 0d8 */ GameModeBattle_0d8 *mUnk_0d8;
    /* 0dc */ unk8 mUnk_0dc[0x714];
    /* 7f0 */ unk8 mUnk_7f0[0x74];
    /* 864 */ s32 mUnk_864;
    /* 868 */ unk8 mUnk_868[0x18];
    /* 880 */ u16 mUnk_880[6];
    /* 88c */ u16 mUnk_88c[0xb];
    /* 8a2 */ unk8 mUnk_8a2[0x22];
    /* 8c4 */ unk8 mUnk_8c4[0x56];
    /* 91a */ unk8 mUnk_91a[0x56];
    /* 970 */ unk8 mUnk_970[0x20];
    /* 990 */ unk32 mUnk_990;
    /* 994 */ unk32 mUnk_994;
    /* 998 */ unk32 mUnk_998;
    /* 99c */ bool mUnk_99c;
    /* 99d */ bool mUnk_99d;
    /* 99e */ bool mUnk_99e;
    /* 99f */ unk8 mUnk_99f;
    /* 9a0 */

    /* 00 */ virtual ~GameModeBattle() override;
    /* 08 */ virtual unk32 vfunc_08(bool param1) override;
    /* 0c */ virtual void vfunc_0c(u16 *param1) override;
    /* 10 */ virtual void vfunc_10(u16 *param1) override;
    /* 14 */ virtual void vfunc_14(u16 *param1) override;
    /* 18 */ virtual void vfunc_18() override;
    /* 24 */ virtual void vfunc_24();
    /* 28 */

    GameModeBattle(unk32 param1);
    static GameModeBattle *Create(unk32 param1);
};
