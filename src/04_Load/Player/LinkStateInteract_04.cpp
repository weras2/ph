#include "Player/LinkStateInteract.hpp"

THUMB LinkStateInteract::LinkStateInteract(PlayerLinkBase *link) :
    LinkStateBase(link),
    mUnk_0c(0),
    mUnk_ac(-1),
    mUnk_b0(false),
    mUnk_b1(false) {
    mThrowOffset.x = 0;
    mThrowOffset.y = 0;
    mThrowOffset.z = 0;
}

THUMB LinkStateInteract::~LinkStateInteract() {}
