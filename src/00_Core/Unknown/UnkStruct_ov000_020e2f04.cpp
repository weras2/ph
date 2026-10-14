#include "Unknown/UnkStruct_ov000_020e2f04.hpp"
#include "System/SysNew.hpp"

class UnkStruct_ov000_020e2f04_Handler {
public:
    /* 00 */ virtual void vfunc_00();
    /* 04 */ virtual void vfunc_04();
    /* 08 */ virtual bool vfunc_08(unk32 param1, unk32 param2);
    /* 0c */ virtual bool vfunc_0c(unk32 param1, unk32 param2);
};

ARM UnkStruct_ov000_020e2f04::~UnkStruct_ov000_020e2f04() {}

ARM void UnkStruct_ov000_020e2f04::vfunc_0c() {}

ARM void UnkStruct_ov000_020e2f04::vfunc_10() {}

ARM void UnkStruct_ov000_020e2f04::vfunc_14(AABB *param1, unk32 param2, unk32 param3, unk32 param4) {}

ARM void UnkStruct_ov000_020e2f04::vfunc_18() {}

ARM void UnkStruct_ov000_020e2f04::vfunc_1c() {}

ARM void UnkStruct_ov000_020e2f04::SetBoundingBox(AABB *param1) {}

ARM void UnkStruct_ov000_020e2f04::vfunc_24() {}

ARM void UnkStruct_ov000_020e2f04::vfunc_28() {}

ARM void UnkStruct_ov000_020e2f04::GetBoundingBox(AABB *bbox) {}

ARM bool UnkStruct_ov000_020e2f04::vfunc_58(unk32 param1, unk32 param2, s32 param3) {
    // The handler pointer lives in the derived classes at 0x10
    UnkStruct_ov000_020e2f04_Handler *handler = *(UnkStruct_ov000_020e2f04_Handler **) ((u8 *) this + 0x10);
    if (handler == NULL) {
        return true;
    }
    if (param3 != 0) {
        return handler->vfunc_08(param1, param2);
    }
    return handler->vfunc_0c(param1, param2);
}
