#include "Player/LinkStateItem.hpp"

THUMB LinkStateItem::LinkStateItem(PlayerLinkBase *link) :
    LinkStateBase(link),
    mUnk_0c(data_02057200),
    mEquipId((ItemFlag) 0),
    mNextEquip(ItemFlag_None),
    mUnk_1c(-1),
    mUnk_20(0),
    mUnk_24(0),
    mUnk_25(0),
    mUnk_26(0),
    mUnk_27(0),
    mUnk_28(0),
    mUnk_29(0),
    mUnk_2a(0),
    mUnk_2c(0),
    mUnk_30(NULL),
    mUnk_34(0),
    mUnk_58(0),
    mUnk_5c(-1) {
    mUnk_38.x = 0;
    mUnk_38.y = 0;
    mUnk_38.z = 0;
    mUnk_44   = 0;
    mUnk_48   = NULL;
    mUnk_4c   = 0;
}

THUMB LinkStateItem::~LinkStateItem() {}
