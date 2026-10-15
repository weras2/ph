#include "DTCM/UnkStruct_027e05f8.hpp"

#define REG_KEYINPUT (*(volatile u16 *) 0x04000130)
#define REG_027fffa8 (*(volatile u16 *) 0x027fffa8)

ARM void UnkStruct_027e05f8::func_0202adf4(unk32 param1, s32 param2) {
    if (param2 != 0) {
        func_02037480();
        return;
    }
    u16 keys = 0;
    if (!func_02037490()) {
        keys = ((REG_KEYINPUT | REG_027fffa8) ^ 0x2fff) & 0x2fff;
    }
    func_02037458(keys, param1);
}

ARM UnkStruct_027e05f8::~UnkStruct_027e05f8() {}
