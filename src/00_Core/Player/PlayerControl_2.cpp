#include "DTCM/UnkStruct_027e077c.hpp"
#include "DTCM/UnkStruct_027e0f64.hpp"
#include "Physics/Cylinder.hpp"
#include "Player/PlayerBase.hpp"
#include "Player/PlayerControl.hpp"

extern TouchState data_027e0d84;

extern "C" {
bool func_01ffe468(UnkStruct_027e0f64_04 *camera, Cylinder *pos, s32 *screenX, s32 *screenY, s32 param5);
void func_01ffb7ec(s32 x, s32 y, q20 height, s32 param4, s16 param5, s32 param6, Vec3p *param7, Mat4x3p *param8, Vec3p *result,
                   Vec3p *param10);
TouchEdge func_ov000_020b786c(s32 x, s32 y);
}

static inline s16 SaturatingAdd2(s16 value) {
    s16 next = value + 2;
    if (value <= next) {
        value = next;
    }
    return value;
}

ARM void PlayerControl::ResetTouchWorld() {
    mTouchWorld.x   = 0;
    mTouchWorld.y   = 0;
    mTouchWorld.z   = 0;
    mUnk_44.x       = 0;
    mUnk_44.y       = 0x1000;
    mUnk_44.z       = 0;
    mTouchDist      = 0;
    mTouchAngle     = 0;
    mTouchFastX     = 128;
    mTouchFastY     = 96;
    mTouchFastAngle = 0;
    InitTouchMovement();
}

ARM void PlayerControl::InitTouchMovement() {
    mTouchSpeedX       = 0;
    mTouchSpeedY       = 0;
    mTouchDuration     = -1;
    mTouchSlowDuration = 0;
    mTouchFastTime     = -1;
    mTouchSpeed        = 0;
    mTouchEdge         = TouchEdge_Middle;
    mTouchLastEdge     = TouchEdge_Middle;
    mTouchDiffX        = 0;
    mTouchDiffY        = 0;
    mTouchFast         = false;
}

ARM void PlayerControl::func_ov000_020b7924(s32 param1) {
    UpdateConditionally(&data_027e0d84, 2);
    UnkStruct_027e0f64_04 *camera = data_027e0f64->func_ov000_0208b180();
    s16 x                         = mTouchX;
    s16 y                         = mTouchY;
    Cylinder playerPos;
    gPlayer->vfunc_14(&playerPos);
    mTouchSlowDuration = SaturatingAdd2(mTouchSlowDuration);

    s32 screenX;
    s32 screenY;
    if (param1 == 0 || !mTouch || x < 0 || y < 0 || !func_01ffe468(camera, &playerPos, &screenX, &screenY, 0)) {
        if (mFlags & TouchFlag_UntouchedNow) {
            mTouchDuration = SaturatingAdd2(mTouchDuration);
            return;
        }
        InitTouchMovement();
        return;
    }

    TouchEdge prevEdge = mTouchEdge;
    mTouchEdge         = func_ov000_020b786c(x, y);
    if (!(mFlags & TouchFlag_TouchedNow) && mTouchEdge != TouchEdge_Middle &&
        func_ov000_020b786c(mTouchPrevX, mTouchPrevY) == TouchEdge_Middle) {
        mTouchFast = true;
    } else {
        mTouchFast = false;
    }
    if (prevEdge != TouchEdge_Middle) {
        mTouchSlowDuration = 0;
        mTouchLastEdge     = prevEdge;
    }

    screenX = screenX > 247 ? 247 : (screenX < 8 ? 8 : screenX);
    screenY = screenY > 183 ? 183 : (screenY < 8 ? 8 : screenY);

    func_01ffb7ec(x, y, gPlayerPos.y, 0x59, *(s16 *) ((u8 *) camera + 4), *(s32 *) ((u8 *) camera + 8), &camera->mUnk_260,
                  &camera->mUnk_01c, &mTouchWorld, &mUnk_44);

    q20 scaleX = 0x1000;
    q20 scaleY = 0x1000;
    if (x < screenX && screenX < 80) {
        scaleX = CoDivide64By32(80, screenX);
    } else if (x > screenX && screenX >= 176) {
        scaleX = CoDivide64By32(80, 255 - screenX);
    }
    if (y < screenY && screenY < 80) {
        scaleY = CoDivide64By32(80, screenY);
    } else if (y > screenY && screenY >= 112) {
        scaleY = CoDivide64By32(80, 191 - screenY);
    }

    Vec3p touchVec;
    if (data_027e077c.mUnk_0 == 1) {
        touchVec.x = scaleX * (x - screenX);
        touchVec.y = 0;
        touchVec.z = scaleY * (y - screenY);
    } else {
        touchVec.x = 0;
        touchVec.y = 0;
        touchVec.z = 0;
        mUnk_44.x  = 0;
        mUnk_44.y  = 0x1000;
        mUnk_44.z  = 0;
    }
    mTouchDist = Vec3p_Length(&touchVec);
    if (mTouchDist > 0) {
        s16 cameraAngle = *(s16 *) ((u8 *) data_027e0f64->func_ov000_0208b180() + 0x226);
        mTouchAngle     = cameraAngle + (s16) FX_Atan2Idx(touchVec.x, touchVec.z);
    }

    if (mTouchDuration < 0) {
        if (!mTouch) {
            return;
        }
        mTouchDuration  = 0;
        mTouchFastTime  = 0;
        mTouchFastX     = x;
        mTouchFastY     = y;
        mTouchFastAngle = mTouchAngle;
        return;
    }

    mTouchDiffX = x - mTouchPrevX;
    mTouchDiffY = y - mTouchPrevY;
    if (mTouchSpeed > 0x800) {
        mTouchFastTime  = mTouchDuration;
        mTouchFastAngle = mTouchAngle;
        mTouchFastX     = x;
        mTouchFastY     = y;
    }
    if (mTouchDiffX * mTouchDiffX + mTouchDiffY * mTouchDiffY <= 8) {
        mTouchSpeed = 0;
    } else {
        if (mTouchSpeedX != 0 && mTouchSpeedY != 0) {
            s16 angle   = FX_Atan2Idx(mTouchDiffX << 12, mTouchDiffY << 12);
            s16 delta   = angle - (s16) FX_Atan2Idx(mTouchSpeedX, mTouchSpeedY);
            s32 speed   = delta >> 3;
            mTouchSpeed = speed < 0 ? -speed : speed;
        }
        s16 diffX    = mTouchDiffX;
        s16 diffY    = mTouchDiffY;
        mTouchSpeedX = diffX << 12;
        mTouchSpeedY = diffY << 12;
    }
    mTouchDuration += 2;
}

ARM void PlayerControl::ApplyTouchWorld(Vec3p *result, unk32 scale) {
    Vec3p_Axpy(scale, &mUnk_44, &mTouchWorld, result);
}

ARM bool PlayerControl::func_ov000_020b7d6c() {
    return mTouchFast;
}
