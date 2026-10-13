#pragma once

#include "global.h"
#include "types.h"

#include "System/SysNew.hpp"

#define GESTURE_BUFFER_LENGTH 14

class TouchGestureBase : public SysObject {
public:
    /* 0 (vtable) */
    /* 4 */ bool mUnk_4;
    /* 5 */

    /* 00 */ virtual ~TouchGestureBase() {}
    /* 08 */ virtual void ResetTouchHistory();
    /* 0c */ virtual void Update(void *param1) = 0;
    /* 10 */

    inline TouchGestureBase() :
        mUnk_4(false) {}
};

class TouchGesture : public TouchGestureBase {
public:
    /* 00 (base) */
    /* 05 */ unk8 mUnk_05[3];
    /* 08 */ s32 mUnk_08;
    /* 0c */ u16 mIndex;
    /* 0e */ s16 mPrevAngle;
    /* 10 */ s16 mAngleDelta[GESTURE_BUFFER_LENGTH];
    /* 2c */ s16 mTouchX[GESTURE_BUFFER_LENGTH];
    /* 48 */ s16 mTouchY[GESTURE_BUFFER_LENGTH];
    /* 64 */

    /* 00 */ virtual ~TouchGesture() override;
    /* 08 */ virtual void ResetTouchHistory() override;
    /* 0c */ virtual void Update(void *param1) override;
    /* 10 */

    TouchGesture();
};
