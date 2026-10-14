#include "Player/LinkStateCutscene.hpp"

THUMB UnkStruct_ov004_0210abb8::UnkStruct_ov004_0210abb8(unk32 param1) :
    UnkStruct_02037750(param1, NULL),
    mUnk_20(0) {}

THUMB LinkStateCutscene::LinkStateCutscene(PlayerLinkBase *link) :
    LinkStateBase(link),
    mUnk_0c(0x1000000),
    mUnk_34(0),
    mUnk_38(-1),
    mUnk_3e(-1),
    mUnk_58(0),
    mUnk_5c(-1),
    mUnk_60(-1),
    mUnk_64(-1),
    mUnk_68(0),
    mUnk_6c(0),
    mUnk_70(0),
    mLastItemId(ItemId_None),
    mAngle(0),
    mUnk_7a(0),
    mUnk_7c(0),
    mUnk_7e(0),
    mUnk_80(-1),
    mUnk_84(NULL),
    mUnk_98(-1),
    mUnk_9c(NULL),
    mUnk_a0(-1),
    mUnk_a4(false),
    mUnk_a5(0),
    mUnk_a6(false),
    mUnk_a7(0),
    mUnk_a8(0),
    mUnk_a9(0),
    mUnk_aa(0),
    mUnk_ab(0) {
    mUnk_40.x = 0;
    mUnk_40.y = 0;
    mUnk_40.z = 0;

    mUnk_30 = new(data_027e0ce0[1], 4) LinkStateCutscene_Fade();
    mUnk_30->Register();
    mUnk_30->mUnk_20 = true;
}

THUMB LinkStateCutscene::~LinkStateCutscene() {
    if (mUnk_30 != NULL) {
        delete mUnk_30;
    }
}
