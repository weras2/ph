#include "Render/FadeControl.hpp"
#include "Render/FadeController.hpp"
#include "nds/math.h"

extern "C" s32 GetFadeValue(u32 reg);

#define REG_MASTER_BRIGHT_A 0x0400006c
#define REG_MASTER_BRIGHT_B 0x0400106c

THUMB void FadeControl::Register() {
    gFadeController.AddIfAbsent(this);
}

THUMB FadeControl *FadeControl::Unregister() {
    gFadeController.RemoveFadeControl(this);
    return this;
}

THUMB FadeControl::FadeControl() {
    mState             = 0;
    mUnk_04            = 0;
    mCurrentBright     = -16;
    mBrightA           = -16;
    mBrightB           = -16;
    mCurrentFadeLength = 32;
    mUnk_16            = 32;
    mUnk_18            = 0;
    mFadeLength        = 32;
    mFadeTimer         = 0;
    mUnk_20            = true;
    mUnk_21            = false;
    mUnk_22            = true;
}

THUMB void FadeControl::func_0202aba8(s32 fadeLength, unk32 param2, unk32 newState) {
    if (fadeLength == 0) {
        fadeLength = 1;
    }
    mState             = newState;
    mUnk_04            = param2;
    mBrightA           = GetFadeValue(REG_MASTER_BRIGHT_A);
    mBrightB           = GetFadeValue(REG_MASTER_BRIGHT_B);
    mCurrentFadeLength = fadeLength;
    mFadeTimer         = mCurrentFadeLength;
    mUnk_21            = false;
}

THUMB bool FadeControl::func_0202abdc(s32 fadeLength, unk32 param2) {
    bool result = false;
    if (mState == 0) {
        this->func_0202aba8(fadeLength, param2, 2);
        result = true;
    }
    return result;
}

THUMB bool FadeControl::func_0202abf4(s32 fadeLength, unk32 param2) {
    bool result = false;
    if (mState == 1) {
        this->func_0202aba8(fadeLength, param2, 3);
        result = true;
    }
    return result;
}

THUMB bool FadeControl::func_0202ac0c(s32 currentFadeLength, u16 param2, s32 fadeLength, unk32 param4) {
    bool result = false;
    if (mState == 1) {
        if (currentFadeLength == 0) {
            currentFadeLength = 1;
        }
        if (fadeLength == 0) {
            fadeLength = 1;
        }
        mState             = 3;
        mUnk_04            = param4;
        mBrightA           = GetFadeValue(REG_MASTER_BRIGHT_A);
        mBrightB           = GetFadeValue(REG_MASTER_BRIGHT_B);
        mCurrentFadeLength = currentFadeLength;
        mFadeTimer         = mCurrentFadeLength;
        mUnk_16            = currentFadeLength;
        mUnk_18            = param2;
        mFadeLength        = fadeLength;
        result             = true;
        mUnk_21            = true;
    }
    return result;
}

ARM void FadeControl::UpdateFade(s32 speed) {
    if (!mUnk_22) {
        return;
    }
    s32 bright = mUnk_20 ? -16 : 16;
    switch (mState) {
        case 0:
            mCurrentBright = bright;
            if (!mUnk_21) {
                return;
            }
            if (mFadeTimer > 0) {
                mFadeTimer -= speed;
            }
            if (mFadeTimer > 0) {
                return;
            }
            mFadeTimer         = 0;
            mState             = 2;
            mCurrentFadeLength = mFadeLength;
            mFadeTimer         = mCurrentFadeLength;
            break;
        case 1:
            mCurrentBright = 0;
            break;
        case 2:
            if (mFadeTimer > 0 && (mFadeTimer -= speed) > 0) {
                mCurrentBright = (bright * (s32) CoDivide32(mFadeTimer << 12, mCurrentFadeLength) + 0x800) >> 12;
            }
            if (mFadeTimer > 0) {
                return;
            }
            mFadeTimer     = 0;
            mState         = 1;
            mCurrentBright = 0;
            mUnk_21        = false;
            break;
        case 3:
            if (mFadeTimer > 0 && (mFadeTimer -= speed) > 0) {
                mCurrentBright =
                    (bright * (s32) (FLOAT_TO_Q20(1.0) - CoDivide32(mFadeTimer << 12, mCurrentFadeLength)) + 0x800) >> 12;
            }
            if (mFadeTimer > 0) {
                return;
            }
            mFadeTimer     = 0;
            mCurrentBright = bright;
            if (mUnk_21) {
                if (mUnk_18 == 0) {
                    mState             = 2;
                    mCurrentFadeLength = mFadeLength;
                    mFadeTimer         = mCurrentFadeLength;
                } else {
                    mState             = 0;
                    mCurrentFadeLength = mUnk_18;
                    mFadeTimer         = mCurrentFadeLength;
                }
            } else {
                mState = 0;
            }
            break;
    }
}
