#include "DTCM/UnkStruct_027e0d38.hpp"
#include "Item/ItemModelLoader.hpp"
#include "Player/LinkStateDamage.hpp"
#include "Unknown/UnkStruct_ov000_020e5868.hpp"

extern char data_ov000_020dc528[];
extern char data_ov000_020dc53c[];

THUMB LinkStateDamage::LinkStateDamage(PlayerLinkBase *link) :
    LinkStateBase(link),
    mUnk_0c(gVec3p_ZERO),
    mUnk_18(0),
    mUnk_1c(0),
    mUnk_22(0),
    mUnk_30(false),
    mUnk_32(0),
    mUnk_3c(NULL),
    mUnk_98(NULL) {
    if (data_027e0d38->mUnk_14 != 1) {
        switch (data_027e0d38->mUnk_0c.func_ov000_020a5e9c()) {
            case 15:
            case 31:
            case 37:
            case 45:
                gItemModelLoader->func_ov000_020bb34c(5);
                gItemModelLoader->func_ov000_020bb390(15);
                mUnk_3c.Init_RenderObject(gItemModelLoader->func_ov000_020bb3f4(data_ov000_020dc528));
                mUnk_98 = new(data_027e0ce0[1], 4)
                    UnkStruct_ov000_020e5868(gItemModelLoader->func_ov000_020bb42c((unk32) data_ov000_020dc53c),
                                             (ItemModel *) mUnk_3c.GetLcdcAddress(), 4);
                mUnk_3c.vfunc_24(mUnk_98);
                break;
        }
    }
}

THUMB UnkStruct_ov000_020e5868::UnkStruct_ov000_020e5868(unk32 param1, ItemModel *param2, s32 param3) :
    UnkStruct_ov000_020c0c08(NULL, param2) {
    func_ov000_020a9a68(this, param1, param3);
    func_ov000_020c0c9c(this, param1);
}

THUMB LinkStateDamage::~LinkStateDamage() {
    if (mUnk_98 != NULL) {
        delete mUnk_98;
    }
}
