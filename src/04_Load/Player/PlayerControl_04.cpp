#include "Player/PlayerBase.hpp"
#include "Player/PlayerControl.hpp"
#include "System/OverlayManager.hpp"

THUMB PlayerControl::PlayerControl() :
    TouchControl(0) {
    ResetTouchWorld();
    mUnk_78         = true;
    mUsingEquipItem = false;
    mUnk_7a         = true;
    mUnk_7b         = false;
    mUnk_7c         = 1;
    mUnk_7d         = true;
    mUnk_7e         = 1;
    mUnk_7f         = false;
    mUnk_80         = false;
    mFollowing      = false;
    mUnk_82         = false;
    mUnk_83         = false;
    mFollowRef.Reset();
    mNextFollowRef.Reset();
    mLastFollowRef.Reset();
    mUnk_9c.x         = 0;
    mUnk_9c.y         = 0;
    mFollowObject     = NULL;
    mFollowDist       = 0;
    mFollowStuckTimer = 0;
    mCutsceneEndTimer = 0;
    mUnk_ac           = 0;
    mAim              = gVec3p_ZERO;
    mAimWorld         = gVec3p_ZERO;
    mUnk_c8           = -1;
    mUnk_cc           = -1;
    mBhio             = NULL;
    mTouchGesture     = (TouchGesture **) SysObject::operator new[](sizeof(TouchGesture *) * 2, data_027e0ce0[1], 4);
    mTouchGesture[0]  = new(data_027e0ce0[1], 4) TouchGesture();
    mTouchGesture[1]  = NULL;
}

THUMB PlayerControl::~PlayerControl() {
    if (mBhio != NULL) {
        delete mBhio;
    }
    for (s32 i = 0; i < 2; i++) {
        if (mTouchGesture[i] != NULL) {
            delete mTouchGesture[i];
        }
    }
    SysObject::operator delete[](mTouchGesture);
}

THUMB void PlayerControl::Create() {
    gPlayerControl = new(data_027e0ce0[1], 4) PlayerControl();
}

THUMB void PlayerControl::Destroy() {
    delete gPlayerControl;
    gPlayerControl = NULL;
}

THUMB void PlayerControl::Init() {
    mUsingEquipItem         = false;
    gPlayerControl->mUnk_78 = true;
    if (gOverlayManager.mLoadedOverlays[OverlayIndex_6] == OverlayId_29) {
        mTouchGesture[1] = (TouchGesture *) new(data_027e0ce0[1], 4) TouchGesture_Unk1();
    }
}

THUMB void PlayerControl::func_ov004_0210b1d0() {
    if (mTouchGesture[1] != NULL) {
        delete mTouchGesture[1];
        mTouchGesture[1] = NULL;
    }
}

THUMB void PlayerControl::func_ov004_0210b1f0() {
    if (gPlayer != NULL) {
        delete gPlayer;
        gPlayer = NULL;
    }
}
