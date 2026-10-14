#include "Map/TriggerAABB.hpp"
#include "Map/TriggerAABB_Unk1.hpp"
#include "Map/TriggerAABB_Unk2.hpp"
#include "Map/TriggerBase.hpp"
#include "Map/TriggerSphere.hpp"

#include "Map/MapManager.hpp"

static inline void Vec3p_Set3(Vec3p *v, q20 x, q20 y, q20 z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

static inline void AABB_Set2(AABB *box, Vec3p *min, Vec3p *max) {
    box->min.x = min->x;
    box->min.y = min->y;
    box->min.z = min->z;
    box->max.x = max->x;
    box->max.y = max->y;
    box->max.z = max->z;
}

TriggerBase::TriggerBase(TriggerParams *params) {
    mUnk_04 = true;
    mId     = params->id;
    mUnk_08 = params->mUnk_6;
    mUnk_0c = params->mUnk_7;
    mUnk_10 = params->mUnk_8;
    if (mUnk_0c >= 0x6c) {
        mUnk_0c = -1;
    }
}

TriggerBase::TriggerBase(u8 id, u32 param2, u32 param3, u32 param4) {
    mUnk_04 = false;
    mId     = id;
    mUnk_08 = param2;
    mUnk_0c = param3;
    mUnk_10 = param4;
    if (mUnk_0c >= 0x6c) {
        mUnk_0c = -1;
    }
}

TriggerBase::~TriggerBase() {}

TriggerAABB::TriggerAABB(TriggerParams *params) :
    TriggerBase(params) {
    Vec3p min;
    Vec3p_Set3(&min, gMapManager->GetTileStartX(params->xMin), -0x5000, gMapManager->GetTileStartZ(params->zMin));
    mAABB.min.x = min.x;
    mAABB.min.y = min.y;
    mAABB.min.z = min.z;
    Vec3p_Set3(&mAABB.max, gMapManager->GetTileEndX(params->xMax), 0xc000, gMapManager->GetTileEndZ(params->zMax));
}

TriggerAABB::~TriggerAABB() {}

TriggerSphere::TriggerSphere(TriggerParams *params) :
    TriggerBase(params) {
    mSphere.radius = 0;
    mSphere.pos.x  = 0;
    mSphere.pos.y  = 0;
    mSphere.pos.z  = 0;

    s32 startZ = gMapManager->GetTileStartZ(params->zMin);
    Vec3p pos;
    pos.x      = gMapManager->GetTileStartX(params->xMin);
    pos.y      = -0x5000;
    pos.z      = startZ;
    u16 radius = (params->zMax << 8) | params->xMax;

    mSphere.pos    = pos;
    mSphere.radius = MUL_Q20((q20) CoDivide64By32(0x1000, 0x10000), radius << 12);
    mHeight        = 0xa000;
}

TriggerSphere::TriggerSphere(u8 id, u32 param2, u32 param3, u32 param4) :
    TriggerBase(id, param2, param3, param4) {
    mSphere.radius = 0;
    mSphere.pos.x  = 0;
    mSphere.pos.y  = 0;
    mSphere.pos.z  = 0;
}

TriggerSphere::~TriggerSphere() {}

bool TriggerSphere::GetBoundingBox(AABB *bbox) {
    Vec3p min = mSphere.pos;
    Vec3p max = mSphere.pos;
    AABB_Set2(bbox, &min, &max);

    q20 radius = mSphere.radius;
    Vec3p size;
    size.x = radius;
    size.y = mHeight;
    size.z = radius;

    bbox->Grow(&size);
    return true;
}

TriggerAABB_Unk2::TriggerAABB_Unk2(TriggerParams *params) :
    TriggerAABB(params),
    mUnk_2c(false) {}

TriggerAABB_Unk2::~TriggerAABB_Unk2() {
    for (u32 i = 0; i < 4; i++) {
        func_ov000_02093af0(data_027e0f6c, &mUnk_30[i]);
    }
}

void TriggerAABB_Unk2::vfunc_08() {
    this->vfunc_0c(false);
}

bool TriggerAABB_Unk2::vfunc_0c(bool param1) {
    Vec3p center;
    mAABB.GetCenter(&center);
    s32 halfX = mAABB.GetSizeX() >> 1;
    s32 halfZ = mAABB.GetSizeZ() >> 1;

    TriggerShapeFlags baseFlags;
    baseFlags.raw          = 0;
    baseFlags.bits.mType   = 1;
    baseFlags.bits.mUnk_0d = 2;
    baseFlags.bits.mUnk_16 = 1;
    baseFlags.bits.mUnk_17 = 1;
    baseFlags.bits.mUnk_18 = 1;
    baseFlags.bits.mUnk_19 = 1;
    baseFlags.bits.mUnk_1c = 1;
    baseFlags.bits.mUnk_1d = 1;

    for (u32 i = 0; i < 4; i++) {
        TriggerShapeFlags flags = baseFlags;
        Vec3p min;
        Vec3p max;
        AABB box;

        switch (i) {
            case 0: {
                min.x = max.x = center.x + halfX;
                min.y = max.y = center.y;
                min.z = max.z = center.z;
                Vec3p sub;
                sub.x = 0;
                sub.y = 0x5000;
                sub.z = halfZ + 0x1000;
                Vec3p_Sub(&min, &sub, &min);
                Vec3p add;
                add.x = 0x1000;
                add.y = 0x5000;
                add.z = halfZ + 0x1000;
                Vec3p_Add(&max, &add, &max);
                if (param1 && halfX >= 0x3000 && halfZ >= 0x3000) {
                    flags.bits.mUnk_0f = 1;
                }
            } break;
            case 1: {
                min.x = max.x = center.x - halfX;
                min.y = max.y = center.y;
                min.z = max.z = center.z;
                Vec3p sub;
                sub.x = 0x1000;
                sub.y = 0x5000;
                sub.z = halfZ + 0x1000;
                Vec3p_Sub(&min, &sub, &min);
                Vec3p add;
                add.x = 0;
                add.y = 0x5000;
                add.z = halfZ + 0x1000;
                Vec3p_Add(&max, &add, &max);
                if (param1 && halfX >= 0x3000 && halfZ >= 0x3000) {
                    flags.bits.mUnk_0f = 1;
                }
            } break;
            case 2: {
                min.x = max.x = center.x;
                min.y = max.y = center.y;
                min.z = max.z = center.z + halfZ;
                Vec3p sub;
                sub.x = halfX + 0x1000;
                sub.y = 0x5000;
                sub.z = 0;
                Vec3p_Sub(&min, &sub, &min);
                Vec3p add;
                add.x = halfX + 0x1000;
                add.y = 0x5000;
                add.z = 0x1000;
                Vec3p_Add(&max, &add, &max);
                if (param1 && halfX >= 0x3000 && halfZ >= 0x3000) {
                    flags.bits.mUnk_0f = 1;
                }
            } break;
            case 3: {
                min.x = max.x = center.x;
                min.y = max.y = center.y;
                min.z = max.z = center.z - halfZ;
                Vec3p sub;
                sub.x = halfX + 0x1000;
                sub.y = 0x5000;
                sub.z = 0x1000;
                Vec3p_Sub(&min, &sub, &min);
                Vec3p add;
                add.x = halfX + 0x1000;
                add.y = 0x5000;
                add.z = 0;
                Vec3p_Add(&max, &add, &max);
                if (param1 && halfX >= 0x3000 && halfZ >= 0x3000) {
                    flags.bits.mUnk_0f = 1;
                }
            } break;
        }

        box.min = min;
        box.max = max;
        mUnk_30[i].vfunc_14(&box, 3, flags.raw, 0);
        func_ov000_02093a5c(data_027e0f6c, &mUnk_30[i]);
    }

    if (param1) {
        mUnk_2c = false;
    }
    return true;
}

unk32 TriggerAABB_Unk2::vfunc_10() {
    if (mUnk_2c) {
        return true;
    }
    for (u32 i = 0; i < 4; i++) {
        func_ov000_02093af0(data_027e0f6c, &mUnk_30[i]);
    }
    mUnk_2c = true;
    return true;
}

TriggerAABB_Unk1::TriggerAABB_Unk1(TriggerParams *params) :
    TriggerAABB(params),
    mUnk_2c(params->isAABB_Unk1) {}

TriggerAABB_Unk1::~TriggerAABB_Unk1() {
    func_ov000_02093af0(data_027e0f6c, &mUnk_30);
}

void TriggerAABB_Unk1::vfunc_08() {
    TriggerShapeFlags flags;
    flags.raw          = 0;
    flags.bits.mType   = 7;
    flags.bits.mUnk_0d = 1;
    flags.bits.mUnk_16 = 1;
    flags.bits.mUnk_17 = 1;
    flags.bits.mUnk_18 = 1;
    flags.bits.mUnk_19 = 1;
    flags.bits.mUnk_1d = 1;
    flags.raw          = (flags.raw & ~0x3f0000) | (mUnk_2c << 16);
    mUnk_30.vfunc_14(&mAABB, 4, flags.raw, 0);
    mUnk_30.mUnk_04 = 0;
    func_ov000_02093a5c(data_027e0f6c, &mUnk_30);
}

bool TriggerSphere::Overlaps(Vec3p *point) {
    return mSphere.ContainsInXZ(point);
}

bool TriggerAABB::Overlaps(Vec3p *point) {
    return mAABB.ContainsInXZ(point);
}

bool TriggerAABB::GetBoundingBox(AABB *bbox) {
    bbox->min.x = mAABB.min.x;
    bbox->min.y = mAABB.min.y;
    bbox->min.z = mAABB.min.z;
    bbox->max.x = mAABB.max.x;
    bbox->max.y = mAABB.max.y;
    bbox->max.z = mAABB.max.z;
    return true;
}
