#include "Player/PlayerControlData.hpp"

extern s32 data_ov004_02110cb4;

THUMB PlayerControlData::PlayerControlData() :
    mUnk_028(0),
    mUnk_02a(0),
    mUnk_02c(0),
    mUnk_02e(0),
    mUnk_030(0),
    mUnk_032(0),
    mUnk_140(NULL),
    mUnk_148(0),
    mUnk_149(0),
    mUnk_14a(0),
    mUnk_14b(0),
    mUnk_14d(0),
    mUnk_14e(0),
    mUnk_154(0, 0x1000, 0, 0x1000),
    mUnk_18c(0),
    mUnk_19c(0),
    mUnk_19e(0) {
    mUnk_150            = 0x400;
    mUnk_008            = 0xa4;
    mUnk_004            = 0x333;
    mRadius             = 0x666;
    mUnk_010            = 0xccd;
    mUnk_014            = 0xccd;
    mStateUnk           = 0;
    mFairyVector.x      = 0;
    mFairyVector.y      = 0;
    mFairyVector.z      = 0;
    mLastJumpLocation.x = 0;
    mLastJumpLocation.y = 0;
    mLastJumpLocation.z = 0;
    for (s32 i = 0; i < 3; i++) {
        Mat4x3p_InitIdentity(&mUnk_040[i]);
    }
    mUnk_190                  = 0;
    mUnk_194                  = 0;
    mUnk_198                  = 0;
    s32 height                = data_ov004_02110cb4;
    mUnk_154.mUnk_04.pos.x    = 0;
    mUnk_154.mUnk_04.pos.y    = height;
    mUnk_154.mUnk_04.pos.z    = 0;
    mUnk_154.mUnk_04.size     = height + 0x1000;
    PlayerControlData_Unk1 *p = &mUnk_168[0];
    p->mUnk_4                 = 0x121;
    p->mUnk_8                 = 1;
    p                         = &mUnk_168[1];
    p->mUnk_4                 = 0x122;
    p->mUnk_8                 = 1;
    p                         = &mUnk_168[2];
    p->mUnk_4                 = 0x123;
    p->mUnk_8                 = 1;
}

THUMB PlayerControlData::~PlayerControlData() {
    if (mUnk_140 != NULL) {
        delete mUnk_140;
        mUnk_140 = NULL;
    }
}

THUMB void PlayerControlData::vfunc_18() {
    mUnk_14c = 0;
    for (s32 i = 0; i < 2; i++) {
        mUnk_0d0[i].x = 0;
        mUnk_0d0[i].y = 0;
        mUnk_0d0[i].z = 0;
        mUnk_0e8[i].x = 0;
        mUnk_0e8[i].y = 0;
        mUnk_0e8[i].z = 0;
    }
}

THUMB void PlayerControlData::vfunc_1c() {}
