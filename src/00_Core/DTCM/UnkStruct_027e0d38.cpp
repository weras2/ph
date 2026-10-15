#include "DTCM/UnkStruct_027e0d38.hpp"
#include "Message/MsgProc.hpp"
#include "Save/AdventureFlags.hpp"

extern "C" s32 func_ov000_0209d738(UnkClass_data_027e0f7c *param1, s32 param2);
extern "C" unk8 func_ov000_0209d758(UnkClass_data_027e0f7c *param1, s32 param2);

ARM s32 UnkStruct_027e0d38::func_ov000_02078b40() {
    return func_ov000_0209d738(data_027e0f7c, mUnk_0c.func_ov000_020a5e9c());
}

ARM unk8 UnkStruct_027e0d38::func_ov000_02078b64() {
    return func_ov000_0209d758(data_027e0f7c, mUnk_0c.func_ov000_020a5e9c());
}

ARM bool UnkStruct_027e0d38::func_ov000_02078b88() {
    s32 index = mUnk_18;
    if (index >= 0 && index < 33 && gAdventureFlags->Get_FlagsUnk_48(index) != 0) {
        return true;
    }
    return false;
}
