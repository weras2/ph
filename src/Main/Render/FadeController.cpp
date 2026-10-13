#include "Render/FadeController.hpp"

extern "C" void SetBrightColor(u32 reg, s32 brightness);

#define REG_MASTER_BRIGHT_A 0x0400006c
#define REG_MASTER_BRIGHT_B 0x0400106c
#define REG_POWER_CNT 0x04000304

ARM bool FadeController::Has(FadeControl *control) {
    return FadeController::Contains((FadeControlEntry *) &control, mLength, mList);
}

THUMB bool FadeController::Contains(FadeControlEntry *needle, s32 length, FadeControl **haystack) {
    if (length > 0) {
        for (s32 i = 0; i < length; i++, haystack++) {
            if (needle->mControl == *haystack) {
                return true;
            }
        }
    }
    return false;
}

THUMB bool FadeController::AddIfAbsent(FadeControl *control) {
    return FadeController::Add((FadeControlEntry *) &control, FADE_CONTROL_COUNT, &mLength, mList, false);
}

THUMB bool FadeController::Add(FadeControlEntry *entry, s32 maxLength, s32 *length, FadeControl **list, bool allowDuplicates) {
    if (*length < maxLength && (allowDuplicates || !FadeController::Contains(entry, *length, list))) {
        list[*length] = entry->mControl;
        (*length)++;
        return true;
    }
    return false;
}

THUMB bool FadeController::RemoveFadeControl(FadeControl *control) {
    bool removed = FadeController::Remove((FadeControlEntry *) &control, &mLength, mList);
    if (removed && mCurrent == control) {
        mCurrent = NULL;
    }
    return removed;
}

ARM bool FadeController::Remove(FadeControlEntry *entry, s32 *length, FadeControl **list) {
    bool found = false;
    if (*length > 0) {
        for (s32 i = 0; i < *length; i++, list++) {
            if (!found) {
                if (entry->mControl == *list) {
                    found = true;
                }
            } else {
                list[-1] = *list;
            }
        }
        if (found) {
            (*length)--;
        }
    }
    return found;
}

ARM bool FadeController::func_0202d77c(FadeControl *control) {
    bool result = false;
    if (control == NULL || this->Has(control)) {
        mCurrent = control;
        result   = true;
    }
    return result;
}

ARM bool FadeController::func_0202d7ac() {
    if (mCurrent == NULL || mCurrent->mState == 1) {
        return false;
    }
    return true;
}

ARM void FadeController::ProcessFade(s32 param1) {
    for (s32 i = 0; i < mLength; i++) {
        if (mList[i] != NULL) {
            mList[i]->UpdateFade(param1);
        }
    }
}

ARM void FadeController::SetScreenBrightness(s32 param1) {
    FadeControl *current = mCurrent;
    if (current == NULL) {
        SetBrightColor(REG_MASTER_BRIGHT_A, 0);
        if (param1 != 0) {
            SetBrightColor(REG_MASTER_BRIGHT_B, 0);
        }
        return;
    }

    bool mainA = false;
    bool mainB = false;
    bool subA  = false;
    bool subB  = false;
    switch (current->mUnk_04) {
        case 0:
            mainA = true;
            mainB = true;
            break;
        case 1:
            if (((*(vu16 *) REG_POWER_CNT & 0x8000) >> 15) == 1) {
                mainA = true;
                subB  = true;
            } else {
                mainB = true;
                subA  = true;
            }
            break;
        case 2:
            if (((*(vu16 *) REG_POWER_CNT & 0x8000) >> 15) == 0) {
                mainA = true;
                subB  = true;
            } else {
                mainB = true;
                subA  = true;
            }
            break;
    }

    if (!mainA && !mainB && !subA && !subB) {
        return;
    }
    if (mainA) {
        SetBrightColor(REG_MASTER_BRIGHT_A, current->mCurrentBright);
    } else if (subA) {
        SetBrightColor(REG_MASTER_BRIGHT_A, current->mBrightA);
    }
    if (param1 == 0) {
        return;
    }
    if (mainB) {
        SetBrightColor(REG_MASTER_BRIGHT_B, mCurrent->mCurrentBright);
    } else if (subB) {
        SetBrightColor(REG_MASTER_BRIGHT_B, mCurrent->mBrightB);
    }
}
