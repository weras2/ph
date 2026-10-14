#include "Player/PlayerBase.hpp"

THUMB PlayerBase::PlayerBase() :
    mInvincibleFrames(0),
    mHealth(0),
    mEntranceId(0),
    mUpdatePos(true),
    mVisible(true),
    mInvincible(false) {
    FadeControl *fade = new(data_027e0ce0[1], 4) FadeControl_Unk();
    mFadeControl      = fade;
    fade->Register();
    mFadeControl->mUnk_20 = true;
}

THUMB PlayerBase::~PlayerBase() {
    if (mFadeControl != NULL) {
        delete mFadeControl;
        mFadeControl = NULL;
    }
}
