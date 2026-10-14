#include "Map/TriggerAABB_Unk2.hpp"

ARM unk32 TriggerAABB_Unk2_Unk1::vfunc_08() {
    return 2;
}

ARM void TriggerAABB_Unk2_Unk1::SetBoundingBox(AABB *param1) {
    mUnk_14.min.x = param1->min.x;
    mUnk_14.min.y = param1->min.y;
    mUnk_14.min.z = param1->min.z;
    mUnk_14.max.x = param1->max.x;
    mUnk_14.max.y = param1->max.y;
    mUnk_14.max.z = param1->max.z;
}

ARM void TriggerAABB_Unk2_Unk1::GetBoundingBox(AABB *bbox) {
    bbox->min.x = mUnk_14.min.x;
    bbox->min.y = mUnk_14.min.y;
    bbox->min.z = mUnk_14.min.z;
    bbox->max.x = mUnk_14.max.x;
    bbox->max.y = mUnk_14.max.y;
    bbox->max.z = mUnk_14.max.z;
}

ARM void TriggerAABB_Unk2_Unk1::SetPosition(Vec3p *pos) {
    Vec3p center;
    mUnk_14.GetCenter(&center);
    Vec3p offset;
    Vec3p_Sub(pos, &center, &offset);
    Vec3p_Add(&mUnk_14.min, &offset, &mUnk_14.min);
    Vec3p_Add(&mUnk_14.max, &offset, &mUnk_14.max);
}

ARM void TriggerAABB_Unk2_Unk1::vfunc_34() {}

ARM void TriggerAABB_Unk2_Unk1::vfunc_38() {}

ARM void TriggerAABB_Unk2_Unk1::GetPosition(Vec3p *pos) {
    mUnk_14.GetCenter(pos);
}

ARM q20 TriggerAABB_Unk2_Unk1::GetSizeXZ() {
    q20 sizeX = mUnk_14.GetSizeX();
    q20 sizeZ = mUnk_14.GetSizeZ();
    return sizeX >= sizeZ ? sizeX >> 1 : sizeZ >> 1;
}

ARM q20 TriggerAABB_Unk2_Unk1::GetHeight() {
    return mUnk_14.GetSizeY();
}

ARM TriggerAABB_Unk2_Unk1::~TriggerAABB_Unk2_Unk1() {}
