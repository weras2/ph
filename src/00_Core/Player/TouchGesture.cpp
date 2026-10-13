#include "Player/TouchGesture.hpp"
#include "Player/PlayerControl.hpp"
#include "Player/TouchControl.hpp"

ARM TouchGesture::TouchGesture() {
    mIndex     = 0;
    mPrevAngle = 0;
    for (s32 i = 0; i < GESTURE_BUFFER_LENGTH; i++) {
        mAngleDelta[i] = 0;
        mTouchX[i]     = 128;
        mTouchY[i]     = 96;
    }
}

ARM void TouchGesture::ResetTouchHistory() {
    mUnk_4 = false;
    for (s32 i = 0; i < GESTURE_BUFFER_LENGTH; i++) {
        mAngleDelta[i] = 0;
        mTouchX[i]     = 128;
        mTouchY[i]     = 96;
    }
}

ARM void TouchGesture::Update(void *param1) {
    PlayerControl *control = (PlayerControl *) param1;

    if (control->mTouchDuration <= 0 || mUnk_4) {
        mAngleDelta[mIndex] = 0;
        mTouchX[mIndex]     = 128;
        mTouchY[mIndex]     = 96;
    } else {
        s32 delta = control->mTouchAngle - mPrevAngle;
        s32 min   = -0x2aab;
        if (delta > min) {
            min = delta;
        }
        mAngleDelta[mIndex] = min;
        mTouchX[mIndex]     = gTouchControl.mTouchLastX;
        mTouchY[mIndex]     = gTouchControl.mTouchLastY;
    }
    mPrevAngle = control->mTouchAngle;
    mIndex     = (mIndex + 1) % GESTURE_BUFFER_LENGTH;

    s32 totalAngle = 0;
    s32 minX       = 128;
    s32 maxX       = 128;
    s32 minY       = 96;
    s32 maxY       = 96;
    s32 minSum     = 224;
    s32 maxSum     = 224;
    s32 minDiff    = 32;
    s32 maxDiff    = 32;
    for (s32 i = 0; i < GESTURE_BUFFER_LENGTH; i++) {
        totalAngle += mAngleDelta[i];

        s32 x = mTouchX[i];
        if (x < minX) {
            minX = x;
        } else if (x > maxX) {
            maxX = x;
        }

        s32 y = mTouchY[i];
        if (y < minY) {
            minY = y;
        } else if (y > maxY) {
            maxY = y;
        }

        s16 sum  = mTouchX[i] + mTouchY[i];
        s16 diff = mTouchX[i] - mTouchY[i];
        if (sum < minSum) {
            minSum = sum;
        } else if (sum > maxSum) {
            maxSum = sum;
        }
        if (diff < minDiff) {
            minDiff = diff;
        } else if (diff > maxDiff) {
            maxDiff = diff;
        }
    }

    mUnk_4 = false;
    if (maxX - minX < 50 || maxY - minY < 50 || maxSum - minSum < 70 || maxDiff - minDiff < 70) {
        return;
    }

    if (totalAngle < -0xd555) {
        mUnk_4  = true;
        mUnk_08 = 0;
    } else if (totalAngle > 0xd555) {
        mUnk_4  = true;
        mUnk_08 = 1;
    }
}

ARM TouchGesture::~TouchGesture() {}

ARM void TouchGestureBase::ResetTouchHistory() {
    mUnk_4 = false;
}
