#pragma once

#include "global.h"
#include "types.h"

#include "Unknown/UnkStruct_ov000_020c0c08.hpp"

extern "C" void func_ov000_020a9a68(void *param1, unk32 param2, s32 param3);
extern "C" void func_ov000_020c0c9c(void *param1, unk32 param2);

class UnkStruct_ov000_020e5868 : public UnkStruct_ov000_020c0c08 {
public:
    /* 00 (base) */
    /* 24 */

    /* 00 */ virtual ~UnkStruct_ov000_020e5868() override;
    /* 08 */

    UnkStruct_ov000_020e5868(unk32 param1, ItemModel *param2, s32 param3);
};
