#include "DTCM/UnkStruct_027e077c.hpp"
#include "Game/Game.hpp"

THUMB void UnkStruct_027e077c::Init(unk32 param1) {
    mUnk_0 = mUnk_4 = param1;
    mUnk_8          = -1;
    mUnk_a          = 0;
}

ARM bool UnkStruct_027e077c::func_0202e740(unk32 param1) {
    if (gGame.mModeId != 2) {
        return false;
    }
    if (mUnk_0 != mUnk_4) {
        return false;
    }
    mUnk_4 = param1;
    return true;
}
