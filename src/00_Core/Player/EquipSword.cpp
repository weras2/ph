#include "Player/EquipSword.hpp"
#include "DTCM/UnkStruct_027e0e58.hpp"
#include "DTCM/UnkStruct_027e0f6c.hpp"
#include "DTCM/UnkStruct_027e0ffc.hpp"
#include "Item/ItemManager.hpp"
#include "Player/PlayerLinkBase.hpp"
#include "Unknown/UnkStruct_ov000_020beba8.hpp"
#include "nds/g3d/sbc.h"

struct EquipSword_Params {
    /* 00 */ q20 mRange;
    /* 04 */ q20 mHitboxSize;
    /* 08 */ s16 mHitStart;
    /* 0a */ s16 mHitEnd;
    /* 0c */ u16 mDamage;
    /* 0e */ u16 mUnk_0e;
    /* 10 */ s32 mAngleOffset;
    /* 14 */ s32 mAngleSweep;
    /* 18 */
};

struct EquipSword_MapObjectInfo {
    /* 00 */ unk8 mUnk_00[0xc];
    /* 0c */ u32 mFlags;
};

class EquipSword_MapObject {
public:
    /* 00 */ virtual void vfunc_00();
    /* 04 */ virtual void vfunc_04();
    /* 08 */ virtual void vfunc_08();
    /* 0c */ virtual void vfunc_0c();
    /* 10 */ virtual void vfunc_10();
    /* 14 */ virtual void vfunc_14();
    /* 18 */ virtual void vfunc_18();
    /* 1c */ virtual s32 vfunc_1c();
    /* 20 */ virtual void vfunc_20();
    /* 24 */ virtual void vfunc_24();
    /* 28 */ virtual void vfunc_28();
    /* 2c */ virtual void vfunc_2c();
    /* 30 */ virtual void vfunc_30();
    /* 34 */ virtual void vfunc_34();
    /* 38 */ virtual void vfunc_38();
    /* 3c */ virtual void vfunc_3c();
    /* 40 */ virtual void vfunc_40();
    /* 44 */ virtual void vfunc_44();
    /* 48 */ virtual void vfunc_48();
    /* 4c */ virtual void vfunc_4c();
    /* 50 */ virtual void vfunc_50();
    /* 54 */ virtual EquipSword_MapObjectInfo *vfunc_54();
};

// Map objects hit by a sword swing
class EquipSword_HitFilter : public SysObject {
public:
    /* 00 (vtable) */
    /* 04 */ u16 mUnk_04;
    /* 06 */ bool mUnk_06;
    /* 08 */

    /* 00 */ virtual ~EquipSword_HitFilter() {
        ((UnkStruct_ov000_020beba8 *) this)->UnkStruct_ov000_020beba8::~UnkStruct_ov000_020beba8();
    }
    /* 08 */ virtual bool vfunc_08(UnkStruct_ov000_020beba8_08 *param1);
    /* 0c */ virtual bool vfunc_0c(unk16 *param1);
    /* 10 */ virtual bool vfunc_10(s32 *param1);
    /* 14 */ virtual bool vfunc_14(u16 *param1);
    /* 18 */

    void func_ov000_020beed0(u32 *flags);
};

static char *gShipParts[8] = {"anc", "bow", "hul", "can", "dco", "pdl", "fnl", "brg"};

static const Vec3p data_ov000_020dd268         = {0x19a, 0, FLOAT_TO_Q20(0.5)};
static const Vec3p data_ov000_020dd274         = {0, 0, FLOAT_TO_Q20(1.0)};
static const Vec3p data_ov000_020dd280         = {0x8cd, 0x666, 0};
static const EquipSword_Params sSwordParams[9] = {
    {0x1333, 0x8cd, 1228, 4096, 4, 0, 0, 0x8000},    {0x1266, 0x800, 819, 3072, 4, 0, 45511, 54613},
    {0x1266, 0x800, 819, 3277, 4, 0, 23666, -43691}, {0x1800, 0x733, 0, 4096, 4, 0, 0, 0},
    {0x1333, 0x99a, 273, 4096, 6, 0, 0, 0x8000},     {0x1000, 0xb33, 0, 4096, 8, 0, 0xc000, -0x20000},
    {0x1000, 0xb33, 0, 3072, 8, 0, 43691, 0x28000},  {0x1000, 0xb33, 0, 4096, 8, 0, 60075, -0x30000},
    {0x1000, 0xb33, 0, 3072, 8, 0, 43691, 0x38000},
};

extern "C" {
void func_ov000_0207c1f8(UnkStruct_027e0e58 *param1, EquipSword_Effect **param2, unk32 param3, const Vec3p *param4,
                         unk32 param5);
void func_ov000_0207c444(UnkStruct_027e0e58 *param1, EquipSword_Effect **param2);
void func_ov000_020ceb24(UnkStruct_027e0ffc *param1, u16 param2, Vec3p *param3, unk32 param4);
void func_ov000_020cef10(void *param1, Cylinder *param2);
void func_ov000_020b41c4(ModelRender *param1);
void func_020197fc(void *param1, s32 param2);
void G3d_GetCurrentMtx(Mat4x3p *mtx1, Mat3p *mtx2);
Mat4x3p *func_02018450();
void Vec3p_RotateY(s32 angle, Vec3p *vec);
}
extern void func_ov000_020b7e6c(s32 *param1);
extern void *data_027e1038;
extern u16 data_027e0e5c;

ARM bool EquipSword_HitFilter::vfunc_08(UnkStruct_ov000_020beba8_08 *param1) {
    u32 flags;
    UnkStruct_027e0f6c::func_ov000_02093a1c(&flags, data_027e0f6c, param1->mUnk_00);
    this->func_ov000_020beed0(&flags);
    return true;
}

ARM void EquipSword_HitFilter::func_ov000_020beed0(u32 *flags) {
    switch (*flags & 0x1f) {
        case 6:
            mUnk_04 = 245;
            break;
        case 7:
            mUnk_04 = 244;
            break;
        case 9:
            mUnk_04 = 246;
            break;
    }
}

ARM bool EquipSword_HitFilter::vfunc_0c(unk16 *param1) {
    return true;
}

ARM bool EquipSword_HitFilter::vfunc_10(s32 *param1) {
    EquipSword_MapObject *obj      = (EquipSword_MapObject *) param1;
    EquipSword_MapObjectInfo *info = obj->vfunc_54();
    u32 flags;
    if (info == NULL) {
        flags = 0;
    } else {
        flags = info->mFlags;
    }
    this->func_ov000_020beed0(&flags);

    switch (obj->vfunc_1c()) {
        case 16:
        case 23:
            mUnk_06 = true;
            break;
        case 25:
        case 144: {
            PlayerLinkBase *link = gPlayerLink;
            if (link->func_ov000_020bbd40() || link->func_ov000_020bbd60()) {
                return false;
            }
            break;
        }
    }
    return true;
}

ARM void func_ov000_020befe0(EquipSword_Effect *effect, s16 *offset) {
    effect->mUnk_50[0] = offset[0];
    effect->mUnk_50[1] = offset[1];
    effect->mUnk_50[2] = offset[2];
}

ARM void EquipSword::vfunc_00() {}

ARM ItemFlag EquipSword::GetId() const {
    return ItemFlag_OshusSword;
}

ARM void EquipSword::func_ov000_020bf008(s16 param1, s16 param2) {
    if (mUnk_56 >= 1) {
        return;
    }
    mUnk_56 = 1;
    mUnk_58 = param1;
    mUnk_5a = param2;
}

ARM bool EquipSword::func_ov000_020bf028() {
    switch (mUnk_40) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            break;
        case 5:
        case 6:
        case 7:
        case 8:
            if (mUnk_44 < 0x4ba) {
                return false;
            }
            break;
    }
    return mUnk_56 > 0;
}

ARM void EquipSword::func_ov000_020bf088() {
    Cylinder hitbox;
    if (!this->GetHitbox(&hitbox)) {
        return;
    }
    this->func_ov000_020c0648();

    s16 offset[3];
    offset[0] = 0;
    offset[1] = 0;
    offset[2] = 0;
    offset[0] = this->GetPlayerPos()->x - hitbox.pos.x;
    offset[2] = this->GetPlayerPos()->z - hitbox.pos.z;
    data_027e0e58->func_ov000_0207c1b0(0x1c3, &hitbox.pos, 1, (unk32) offset, (unk32) func_ov000_020befe0);
    data_027e0e58->func_ov000_0207c1b0(0x1c4, &hitbox.pos, 1, (unk32) offset, (unk32) func_ov000_020befe0);
    func_ov000_020ceb24(&data_027e0ffc, mUnk_58, &hitbox.pos, 0);
    func_ov000_020cef10(data_027e1038, &hitbox);
}

THUMB void EquipSword::vfunc_10() {
    mUnk_0c->Init_RenderObject(gItemManager->GetItemModel(ItemModelId_OshusSword));
    mUnk_10->Init_RenderObject(gItemManager->GetItemModel(ItemModelId_PhantomSword));
}

ARM bool EquipSword::UpdateInUse(unk32 param1) {
    EquipItem::UpdateInUse(param1);
    if (param1 != 0) {
        func_ov000_0207c1f8(data_027e0e58, &mUnk_30, 0x15b, &gVec3p_ZERO, 1);
        func_ov000_0207c1f8(data_027e0e58, &mUnk_34, 0x15c, &gVec3p_ZERO, 1);
        if (mUnk_30 != NULL) {
            mUnk_30->mUnk_24_1 = true;
        }
        if (mUnk_34 != NULL) {
            mUnk_34->mUnk_24_1 = true;
        }
    } else {
        func_ov000_020b7e6c((s32 *) &mUnk_30);
        func_ov000_020b7e6c((s32 *) &mUnk_34);
    }
    mUnk_6e = false;
    return mInUse;
}

ARM void EquipSword::vfunc_18() {
    mUnk_6c = false;
    this->func_ov000_020c0648();
    if (mUnk_40 <= 3) {
        mUnk_54 = gItemManager->GetActiveFairyLevel(FairyId_Courage);
        mUnk_54 = mUnk_54 > 0 ? mUnk_54 : 0;
    }
    this->func_ov000_020bf330();
    mUnk_6d   = false;
    mUnk_60.x = 0;
    mUnk_60.y = 0;
    mUnk_60.z = 0;
}

ARM void EquipSword::vfunc_1c() {
    this->func_ov000_020c0648();
    mUnk_40 = -1;
    mUnk_4c = 0;
    if (mUnk_30 != NULL) {
        mUnk_30->mUnk_24_1 = true;
    }
    if (mUnk_34 != NULL) {
        mUnk_34->mUnk_24_1 = true;
    }
    mUnk_6e = false;
    mUnk_56 = 0;
    mUnk_5a = 0;
}

ARM void EquipSword::func_ov000_020bf330() {
    s16 angle = mUnk_04;
    s32 effect;
    Vec3p pos;
    switch (mUnk_40) {
        case 0:
            angle += 0x4000;
            effect = 0x21e;
            break;
        case 1:
            effect = 0x220;
            break;
        case 2:
            effect = 0x221;
            break;
        case 3: {
            Vec3p offset = data_ov000_020dd268;
            Vec3p_RotateY(mUnk_04, &offset);
            this->func_ov000_020be99c(&pos);
            Vec3p_Add(&pos, &offset, &pos);
            func_ov000_0207c1f8(data_027e0e58, &mUnk_2c, 0x1c0, &pos, 1);
            if (mUnk_2c == NULL) {
                return;
            }
            Vec3p dir = data_ov000_020dd274;
            Vec3p_RotateY(mUnk_04, &dir);
            Vec3p_Normalize(&dir, &dir);
            mUnk_2c->mUnk_50[0] = dir.x;
            mUnk_2c->mUnk_50[1] = dir.y;
            mUnk_2c->mUnk_50[2] = dir.z;
            return;
        }
        case 4:
            angle += 0x4000;
            effect = 0x21f;
            break;
        case 5:
            effect = 0x21a;
            break;
        case 6:
            effect = 0x21b;
            break;
        case 7:
            effect = 0x21d;
            break;
        case 8:
            effect = 0x21c;
            break;
        default:
            return;
    }
    this->func_ov000_020be99c(&pos);
    func_ov000_020b7e6c((s32 *) &mUnk_2c);
    func_ov000_0207c1f8(data_027e0e58, &mUnk_2c, effect, &pos, 1);
    if (mUnk_2c != NULL) {
        mUnk_2c->mUnk_56 = angle;
    }
}

ARM bool EquipSword::func_ov000_020bf4f4() {
    switch (mUnk_40) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            return true;
        case 5:
        case 6:
        case 7:
        case 8:
            return false;
    }
    return true;
}

ARM void EquipSword::vfunc_30() {}

ARM EquipRope *EquipSword::GetEquipRope() {
    return (EquipRope *) ItemManager::GetEquipItemUnchecked(ItemFlag_GrapplingHook);
}

static inline void SetEffectHidden(EquipSword_Effect *effect, bool hidden) {
    if (effect != NULL) {
        effect->mUnk_24_2 = !hidden;
    }
}

ARM void EquipSword::vfunc_38(unk32 param1) {
    if (this->IsInUse()) {
        if (mUnk_5c != 0) {
            G3d_RestoreMtx_inline(29);
            Mat4x3p mtx;
            G3d_GetCurrentMtx(&mtx, NULL);
            Mat4x3p_MultiplyVec((Vec3p *) &data_ov000_020dd280, &mtx, &mUnk_60);
            Mat4x3p_MultiplyVec(&mUnk_60, func_02018450(), &mUnk_60);
            if (gItemManager->HasItem(ItemFlag_PhantomSword)) {
                s16 alpha = mUnk_5c;
                if (alpha > 0) {
                    func_020197fc(mUnk_10->GetLcdcAddress(), alpha);
                } else {
                    func_020197fc(mUnk_10->GetLcdcAddress(), 31);
                }
                func_ov000_020b41c4(mUnk_10);
            } else {
                s16 alpha = mUnk_5c;
                if (alpha > 0) {
                    func_020197fc(mUnk_0c->GetLcdcAddress(), alpha);
                } else {
                    func_020197fc(mUnk_0c->GetLcdcAddress(), 31);
                }
                func_ov000_020b41c4(mUnk_0c);
            }
        }
        if (mUnk_5c > 0) {
            switch (mUnk_50) {
                case 1:
                    if (mUnk_14 != NULL && mUnk_14->GetLcdcAddress() != NULL) {
                        G3d_RestoreMtx_inline(29);
                        func_ov000_020b41c4(mUnk_14);
                    }
                    break;
                case 2:
                    if (mUnk_18 != NULL && mUnk_18->GetLcdcAddress() != NULL) {
                        G3d_RestoreMtx_inline(29);
                        func_ov000_020b41c4(mUnk_18);
                    }
                    break;
            }
        }
        if (mUnk_2c != NULL) {
            SetEffectHidden(mUnk_2c, data_027e0e5c == 0);
        }
    }
    mUnk_6e = this->IsInUse() && mUnk_5c > 0;
    mUnk_5c = 31;
}

ARM bool EquipSword::GetHitbox(Cylinder *hitbox) const {
    if (mUnk_4c <= 0) {
        return false;
    }
    hitbox->pos = *((EquipSword *) this)->GetPlayerPos();
    ((EquipSword *) this)->func_ov000_020c0550(&hitbox->pos, mUnk_44);
    hitbox->size = sSwordParams[mUnk_40].mHitboxSize;
    return true;
}

ARM void EquipSword::func_ov000_020c024c(Vec3p *param1, s32 param2) {
    const EquipSword_Params *params = &sSwordParams[mUnk_40];
    u16 angle                       = (s16) (mUnk_04 + params->mAngleOffset + MUL_Q20(param2, params->mAngleSweep));
    param1->x += MUL_Q20(SIN(angle), params->mRange);
    param1->z += MUL_Q20(COS(angle), params->mRange);
}

ARM void EquipSword::func_ov000_020c0318(Vec3p *param1, s32 param2) {
    switch (mUnk_40) {
        case -1:
            return;
        case 0:
        case 4: {
            u16 pitch = MUL_Q20(FLOAT_TO_Q20(0.5) - param2, sSwordParams[mUnk_40].mAngleSweep);
            s32 range = MUL_Q20(COS(pitch), sSwordParams[mUnk_40].mRange);
            u16 angle = mUnk_04;
            param1->x += MUL_Q20(SIN(angle), range);
            param1->z += MUL_Q20(COS(angle), range);
            param1->y += 0xa66;
            break;
        }
        case 1:
        case 2:
            this->func_ov000_020c024c(param1, param2);
            param1->y += 0x99a;
            break;
        case 3: {
            s32 range;
            if (param2 < 0xb33) {
                range = sSwordParams[mUnk_40].mRange * param2 / 0xb33;
            } else {
                range = sSwordParams[mUnk_40].mRange * (0xb33 * 2 - param2) / 0xb33;
            }
            range += 0x266;
            u16 angle = mUnk_04;
            param1->x += MUL_Q20(SIN(angle), range);
            param1->z += MUL_Q20(COS(angle), range);
            param1->y += 0x99a;
            break;
        }
        case 5:
        case 6:
        case 7:
        case 8:
            this->func_ov000_020c024c(param1, param2);
            param1->y += 0x8cd;
            break;
    }
}

ARM void EquipSword::func_ov000_020c0550(Vec3p *param1, s32 param2) {
    this->func_ov000_020c0318(param1, param2);
    if (mUnk_40 != 0 && mUnk_40 != 4) {
        return;
    }
    u16 pitch = MUL_Q20(FLOAT_TO_Q20(0.5) - param2, sSwordParams[mUnk_40].mAngleSweep);
    param1->y += MUL_Q20(SIN(pitch), sSwordParams[mUnk_40].mRange);
}

ARM void EquipSword::func_ov000_020c05ec(s32 param1) {
    mUnk_44 = param1;
    if (mUnk_40 != -1 && sSwordParams[mUnk_40].mHitStart <= mUnk_44 && mUnk_44 < sSwordParams[mUnk_40].mHitEnd) {
        mUnk_4c = 3;
        return;
    }
    mUnk_4c = 0;
}

ARM void EquipSword::func_ov000_020c0648() {
    mUnk_44 = 0;
    mUnk_4c = 0;
    func_ov000_0207c444(data_027e0e58, &mUnk_2c);
}

ARM u32 EquipSword::vfunc_2c() {
    return sSwordParams[mUnk_40].mDamage + gItemManager->GetActiveFairyLevel(FairyId_Power) * 2;
}

ARM void EquipSword::func_ov000_020c06b0(s32 param1) {
    mUnk_40 = param1;
}
