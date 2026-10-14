#include "Player/Bhio.hpp"

extern "C" {
void CopyDebugNodeDescription(char *dst, const char *src);
bool DebugNodeDescriptionEquals(BhioField *field, char *description);
}

THUMB BhioBase::BhioBase() {
    mNodes = NULL;
}

THUMB BhioBase::~BhioBase() {}

THUMB BhioGroup *BhioBase::FindGroup(u32 id) {
    BhioGroup *group = (BhioGroup *) mNodes;
    if (group == NULL) {
        return NULL;
    }
    u8 *end = (u8 *) group + group->mUnk_04;
    while ((u8 *) group < end) {
        if (group->mMagic != BHIO_GROUP_MAGIC) {
            return NULL;
        }
        if (group->mGroupId == id) {
            return group;
        }
        group = (BhioGroup *) ((u8 *) group + group->mUnk_08);
    }
    return NULL;
}

THUMB bool BhioBase::GetField(bool param1, const char *fieldName, u32 groupId, s32 *pValue, unk32 param5, unk32 param6,
                              unk32 param7, unk32 param8) {
    BhioGroup *group = FindGroup(groupId);
    if (group != NULL) {
        BhioField *field = group->mFields;
        BhioField *end   = field + group->mNumFields;
        char description[12];
        CopyDebugNodeDescription(description, fieldName);
        for (; field < end; field++) {
            if (DebugNodeDescriptionEquals(field, description)) {
                *pValue = field->mValue;
                return false;
            }
        }
    }
    return false;
}

THUMB void BhioBase::vfunc_08() {}

THUMB void BhioBase::vfunc_0c() {}

THUMB void BhioBase::vfunc_10() {}

THUMB void BhioBase::vfunc_14() {}

THUMB void BhioBase::vfunc_18() {}

THUMB void BhioBase::vfunc_1c() {}

THUMB unk32 BhioBase::vfunc_20(unk32 param1, const char *param2, unk32 param3, unk32 param4, unk32 param5, unk32 param6) {
    return 0;
}

THUMB void BhioBase::vfunc_24() {}

THUMB void BhioBase::vfunc_28() {}

THUMB void BhioBase::vfunc_2c() {}

THUMB void BhioBase::vfunc_30() {}

THUMB void BhioBase::vfunc_38() {}

THUMB void BhioBase::vfunc_3c(u32 groupId, s32 *pValue) {}

#pragma thumb off
