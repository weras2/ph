#include "Player/LinkStateRoll.hpp"

extern const s16 data_ov000_020dc6e0;

THUMB LinkStateRoll::LinkStateRoll(PlayerLinkBase *link) :
    LinkStateBase(link),
    mUnk_0c(0),
    mUnk_10(0),
    mUnk_12(0),
    mUnk_14(data_ov000_020dc6e0),
    mUnk_16(0),
    mUnk_1a(0),
    mUnk_20(0),
    mUnk_26(0),
    mUnk_28(0),
    mUnk_2a(0),
    mUnk_2b(0) {}

THUMB LinkStateRoll::~LinkStateRoll() {}
