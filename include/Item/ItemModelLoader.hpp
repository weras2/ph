#pragma once

#include "global.h"
#include "types.h"

class ItemModelLoader {
public:
    /* 00 */ void *mItems;
    /* 04 */ void *mDungeonItems;
    /* 08 */ unk32 mUnk_08[6];
    /* 20 */

    ItemModelLoader();
    ItemModelLoader *func_ov000_020bb2ec();
    unk32 func_ov000_020bb34c(s32 index);
    unk32 func_ov000_020bb378(s32 param1);
    unk32 func_ov000_020bb390(s32 equipId);
    unk32 func_ov000_020bb3a8(s32 param1);
    s32 func_ov000_020bb3b4(s32 param1, char *param2);
    unk32 func_ov000_020bb3d4(s32 param1, unk32 param2);
    s32 func_ov000_020bb3f4(char *param2);
    unk32 func_ov000_020bb414(unk32 param1);
    unk32 func_ov000_020bb420(unk32 param1);
    unk32 func_ov000_020bb42c(unk32 param1);

    static void Create();
    static void Destroy();
};

extern ItemModelLoader *gItemModelLoader;
