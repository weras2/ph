#include "Cutscene/CutsceneHandler.hpp"
#include "Game/Game.hpp"
#include "Render/FadeController.hpp"

extern "C" void Fill32(unk32, u32 *, unk32);
extern FadeControl data_027e06e4;

THUMB CutsceneHandler::CutsceneHandler() {
    Fill32(0, &mFlags1, sizeof(mFlags1));
    Fill32(0, &mFlags2, sizeof(mFlags2));
    mCutsceneActive = false;
    mSkipping       = false;
    mUnk_0a         = false;
    mUnk_0b         = 0;
    mCutsceneTimer1 = 0;
    mCutsceneTimer2 = 0;
    mCutsceneEnd    = 0;
    mFreeze         = 0;
    mUnk_1c         = 2;
    mUnk_20         = 0;
    mUnk_21         = 0;
    mUnk_22         = 0;
    mUnk_24         = 0;
    mUnk_28         = -1;
    mUnk_2c         = -1;
    mUnk_30         = 0;
    mUnk_34         = 0;
    mUnk_38         = 0;
    mUnk_3c         = 0;
    mUnk_40         = 0;
    mUnk_44         = 0;
    mUnk_48         = 0;
    mFadeControl    = new(data_027e0ce0[1], 4) FadeControl_Derived1();
    mUnk_80         = NULL;
    Mat4x3p_InitIdentity(&mUnk_4c);
    mUnk_84[0] = NULL;
    mUnk_84[1] = NULL;
    Fill32(0, &mFlags1, sizeof(mFlags1));
    Fill32(0, &mFlags2, sizeof(mFlags2));
    mFadeControl->Register();
}

THUMB CutsceneHandler::~CutsceneHandler() {
    for (s32 i = 0; i < 2; i++) {
        if (mUnk_84[i] != NULL) {
            delete mUnk_84[i];
            mUnk_84[i] = NULL;
        }
    }
    if (mUnk_80 != NULL) {
        delete mUnk_80;
        mUnk_80 = NULL;
    }
    gFadeController.func_0202d77c(&data_027e06e4);
    if (mFadeControl != NULL) {
        delete mFadeControl;
        mFadeControl = NULL;
    }
}

THUMB void CutsceneHandler::func_ov004_0210f3e4(s32 param1) {
    s32 *flags = (s32 *) param1;
    if (flags[2] == 1 && mUnk_80 == NULL) {
        mUnk_80 = new(data_027e0ce0[1], 4) CutsceneHandler_Unk80();
    }
    if (mUnk_84[0] == NULL) {
        mUnk_84[0] = new(data_027e0ce0[1], 4) CutsceneHandler_Unk84(this);
    }
    if (flags[2] == 1 && mUnk_84[1] == NULL) {
        mUnk_84[1] = new(data_027e0ce0[1], 4) CutsceneHandler_Unk88(this);
    }
}

THUMB void CutsceneHandler::func_ov004_0210f46c() {
    func_ov000_020985c4();
    SetFlags(~1);
    for (s32 i = 0; i < 2; i++) {
        if (mUnk_84[i] != NULL) {
            delete mUnk_84[i];
            mUnk_84[i] = NULL;
        }
    }
    if (mUnk_80 != NULL) {
        delete mUnk_80;
        mUnk_80 = NULL;
    }
}
