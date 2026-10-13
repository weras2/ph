#include "Cutscene/CutsceneHandler.hpp"
#include "DTCM/UnkStruct_027e0c54.hpp"
#include "DTCM/UnkStruct_027e0d38.hpp"
#include "DTCM/UnkStruct_027e0f64.hpp"
#include "Map/MapManager.hpp"
#include "Message/MsgProc.hpp"
#include "Player/PlayerBase.hpp"
#include "Render/FadeController.hpp"
#include "Save/AdventureFlags.hpp"

extern "C" {
void func_ov040_021833c4(s32 **param1, unk32 param2, unk32 param3, void **param4);
bool func_ov040_02182970(CutsceneHandler_Player *param1);
void func_ov040_02182980(CutsceneHandler_Player *param1, s32 param2);
void func_ov000_0208949c(UnkStruct_027e0f64_04 *param1, Vec3p *param2, s32 param3, unk32 param4, unk32 param5, unk32 param6,
                         unk32 param7);
void func_ov000_02089318(UnkStruct_027e0f64_04 *param1, Vec3p *param2, unk32 param3, void *param4, unk32 param5, unk32 param6);
void func_ov000_02089168(UnkStruct_027e0f64_04 *param1, Vec3p *param2, unk32 param3, unk32 param4, unk32 param5);
void func_ov000_02087d98(UnkStruct_027e0f64_04 *param1, unk32 param2);
void func_ov000_0207b5bc(UnkStruct_027e0d38_Unk28 *param1, Exit *param2, unk32 param3);
void func_ov005_02100ae0(UnkStruct_027e0d38 *param1, Exit *param2, unk32 param3);
}

class CutsceneHandler_Callback {
public:
    /* 00 */ virtual void vfunc_00();
    /* 04 */ virtual void vfunc_04();
    /* 08 */ virtual void vfunc_08();
};

ARM void CutsceneHandler::func_ov000_020980f8() {}

ARM s32 CutsceneHandler::func_ov000_020980fc(unk32 param1, unk32 param2, void **param3) {
    if (mUnk_80 != NULL) {
        func_ov040_021833c4(mUnk_80, param1, param2, param3);
    }
}

ARM bool CutsceneHandler::func_ov000_02098114() {
    if (mSkipping) {
        return false;
    }
    if (gFadeController.func_0202d7ac()) {
        return false;
    }
    return func_ov040_02182970(mPlayers[1]);
}

ARM bool CutsceneHandler::SkipCutscene(s32 param1) {
    if (!(mFlags1 & 1)) {
        return false;
    }
    if (mUnk_1c != 1) {
        return false;
    }
    if (!this->func_ov000_02098114()) {
        return false;
    }
    data_027e0d04.func_0203fe60(2);
    mSkipping = true;
    func_ov040_02182980(mPlayers[1], param1);
    return true;
}

ARM unk32 CutsceneHandler::func_ov000_020981b8(unk32 *param1) {
    UnkStruct_ov000_0209a50c *cutscene = (UnkStruct_ov000_0209a50c *) param1;

    this->func_ov000_02098658();
    mFlags1 |= 1;
    mFlags2 |= 1;
    mCutsceneActive = true;
    mUnk_0a         = false;
    mSkipping       = false;
    mUnk_1c         = cutscene->mUnk_08;
    mCutsceneEnd    = cutscene->mUnk_04;

    if (cutscene->mUnk_14) {
        if (cutscene->mUnk_94 != 92) {
            func_ov000_0208949c(data_027e0f64->mUnk_4, &cutscene->mUnk_20, cutscene->mUnk_1c, cutscene->mUnk_0a,
                                cutscene->mUnk_94, 0, 0);
        } else {
            func_ov000_02089318(data_027e0f64->mUnk_4, &cutscene->mUnk_20, cutscene->mUnk_0a, &cutscene->mUnk_2c, 0, 0);
        }
    } else {
        func_ov000_02089168(data_027e0f64->mUnk_4, &cutscene->mUnk_20, cutscene->mUnk_0a, 0, 0);
    }

    if (cutscene->mUnk_12) {
        gPlayer->SetUpdatePos(false);
    }
    if (cutscene->mUnk_11 || cutscene->mUnk_13) {
        mUnk_21 = cutscene->mUnk_11;
        mUnk_22 = cutscene->mUnk_13;
        mUnk_2c = cutscene->mUnk_9c;
    }
    if (cutscene->mUnk_18) {
        mUnk_20 = 1;
        mUnk_28 = cutscene->mUnk_98;
        mUnk_30 = cutscene->mUnk_a0.x;
        mUnk_34 = cutscene->mUnk_a0.y;
        mUnk_38 = cutscene->mUnk_a0.z;
        mUnk_24 = cutscene->mUnk_9a;
    }
    if (cutscene->mUnk_15) {
        func_ov000_02087d98(data_027e0f64->mUnk_4, 1);
    }
    if (cutscene->mUnk_16) {
        mFlags1 |= 2;
        mFlags2 |= 2;
        data_027e0db0.func_ov000_0207b2f0(0, cutscene->mUnk_17 && data_027e0c54.mUnk_0);
    } else {
        mFlags1 &= ~2;
        mFlags2 &= ~2;
        data_027e0db0.func_ov000_0207b334(0);
    }
    this->func_ov000_02098694(cutscene->mUnk_0c);
    if (cutscene->mUnk_ac != 0) {
        ((CutsceneHandler_Callback *) cutscene->mUnk_ac)->vfunc_08();
    }

    UnkStruct_ov000_0209a50c local = *cutscene;
    if (cutscene->mUnk_0e != 0) {
        FlagsUnk2 exit;
        exit.mUnk_00.mUnk_00   = 0x47;
        exit.mUnk_04.mUnk_00.x = 0;
        exit.mUnk_04.mUnk_00.y = 0;
        exit.mUnk_04.mUnk_00.z = -2;
        exit.mUnk_04.mUnk_0c   = 0;
        exit.mUnk_04.mUnk_0f   = 0;
        exit.mUnk_04.mUnk_10   = 0;
        exit.mUnk_04.mUnk_11   = 0;
        exit.mUnk_04.mUnk_0e   = -1;
        gMapManager->FindExit(cutscene->mUnk_0e, (Exit *) &exit);
        if (data_027e0d38->mUnk_14 == 1) {
            func_ov000_0207b5bc(data_027e0d38->mUnk_28, (Exit *) &exit, 1);
        } else {
            func_ov005_02100ae0(data_027e0d38, (Exit *) &exit, 1);
        }
        local.mUnk_04 = -1;
        mCutsceneEnd  = -1;
        local.mUnk_08 = 0;
        mUnk_1c       = 0;
    }
    return mPlayers[mUnk_1c]->Start(cutscene);
}

ARM void CutsceneHandler::func_ov000_020985c0() {}

ARM bool CutsceneHandler::func_ov000_020985c4() {
    mCutsceneActive = false;
    mUnk_0a         = false;
    data_027e0d04.func_0203fe60(2);
    if (mUnk_1c == 2) {
        return true;
    }
    bool result = mPlayers[mUnk_1c]->Stop();
    mUnk_1c     = 2;
    return result;
}

ARM void CutsceneHandler::func_ov000_02098618(s32 param1, unk32 param2, void **param3) {
    if (mUnk_1c != 2) {
        mPlayers[mUnk_1c]->vfunc_18();
    }
    if (param1 != 0) {
        this->func_ov000_020980fc(param1, param2, param3);
    }
}

ARM void CutsceneHandler::func_ov000_02098658() {
    mFreeze         = 0;
    mCutsceneTimer1 = 0;
    mCutsceneTimer2 = 0;
    if (mUnk_1c != 2 && mPlayers[mUnk_1c] != NULL) {
        mPlayers[mUnk_1c]->Reset();
    }
}

ARM bool CutsceneHandler::func_ov000_02098694(unk32 param1) {
    unk32 type = 2;
    if (data_027e0d38->mUnk_14 == 1) {
        type = 0;
    }
    switch (param1) {
        case 0:
            return true;
        case 1:
            return this->func_ov000_020987c4(0, 10, 10, type, false);
        case 2:
            return this->func_ov000_020987c4(0, 10, 10, type, false);
        case 3:
            return this->func_ov000_020987c4(0, 45, 15, type, false);
        case 4:
            return this->func_ov000_020987c4(30, 30, 30, type, false);
        case 5:
            return this->func_ov000_020987c4(10, 10, 10, type, true);
        case 6:
            return this->func_ov000_020987c4(30, 30, 30, type, true);
    }
    return false;
}

ARM bool CutsceneHandler::func_ov000_020987c4(unk32 param1, u16 param2, unk32 param3, unk32 param4, bool param5) {
    gFadeController.func_0202d77c(mFadeControl);
    mFadeControl->mUnk_20 = param5 ? false : true;
    FadeControl *fade     = mFadeControl;
    fade->mState          = 1;
    fade->mCurrentBright  = 0;
    return mFadeControl->func_0202ac0c(param1, param2, param3, param4);
}

ARM bool CutsceneHandler::func_ov000_02098834() {
    if (gFadeController.Has(mFadeControl)) {
        return mFadeControl->mUnk_21;
    }
    return false;
}

ARM bool CutsceneHandler::func_ov000_02098860() {
    if (this->func_ov000_02098834() == false) {
        return false;
    }
    return mFadeControl->mState == 0 ? true : false;
}

ARM unk32 CutsceneHandler::func_ov000_02098890(unk32 param1, s32 param2) {
    if (param2 == 0) {
        return 0;
    }
    mFlags1 |= 1;
    mFlags2 |= 1;
    mCutsceneActive = true;
    mUnk_0a         = false;
    mCutsceneTimer1 = 0;
    mUnk_1c         = 0;
    mCutsceneEnd    = CutsceneHandler::func_ov000_02098920(param2);
    func_ov000_02089168(data_027e0f64->mUnk_4, (Vec3p *) param1, param2, 0, 0);
    return 1;
}

ARM unk32 CutsceneHandler::func_ov000_02098920(unk32 param1) {
    switch (param1) {
        case 0:
        case 1:
            break;
        case 2:
            return 1;
        case 3:
            return 15;
        case 4:
            return 30;
        case 5:
            return 15;
        case 6:
            return 30;
        case 7:
            return 45;
        case 8:
            return 30;
        case 9:
            return 45;
        case 10:
            return 60;
    }
    return 0;
}
