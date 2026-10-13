#include "Player/LinkStateRoll.hpp"
#include "DTCM/UnkStruct_027e0e58.hpp"
#include "Game/Game.hpp"
#include "Player/PlayerControl.hpp"
#include "Unknown/UnkStruct_020eec9c.hpp"

extern "C" {
void func_ov000_0207c39c(UnkStruct_027e0e58 *param1, unk32 *param2, unk32 param3, unk32 param4, unk32 param5, unk32 param6,
                         unk32 param7, Vec3p *param8, unk32 param9);
void func_ov000_0207c444(UnkStruct_027e0e58 *param1, unk32 *param2);
void func_ov021_02170660(LinkStateRoll *param1);
void func_ov023_0217139c(LinkStateRoll *param1);
void func_ov023_021720f0(LinkStateRoll *param1);
bool func_ov023_021712fc(LinkStateRoll *param1, s32 param2);
}
extern void func_ov000_020b7e6c(s32 *param1);

LinkStateBase_UnkStruct1 data_ov000_020e6098 = {0x45, {0x1000, 0x0, 0x1000}};
LinkStateBase_UnkStruct1 data_ov000_020e6088 = {0x23, {0x1000, 0x0, 0x2c000}};
LinkStateBase_UnkStruct1 data_ov000_020e6078 = {0xb, {0x119a, 0x1000, 0x13000}};
LinkStateBase_UnkStruct1 data_ov000_020e60a8 = {0x2d, {0x3000, 0x0, 0x11000}};

THUMB void LinkStateRoll::vfunc_00() {}

ARM LinkStateId LinkStateRoll::GetId() {
    return LinkStateId_Roll;
}

THUMB void LinkStateRoll::LoadBhio() {
    this->GetBhio0();
}

ARM void LinkStateRoll::OnStateEnter() {
    switch (mSubState) {
        case 0: {
            this->func_ov00_020a82ac();
            this->GetPlayerVel()->x /= 2;
            this->GetPlayerVel()->z /= 2;
            u16 angle  = *this->GetPlayerAngle();
            Vec3p *vel = this->GetPlayerVel();
            s32 sin    = SIN(angle);
            s32 cos    = COS(angle);
            vel->x += MUL_Q20(sin, 0x148);
            vel->z += MUL_Q20(cos, 0x148);
            this->ApplyImpulse(*(s16 *) this->GetPlayerAngle(), 0x400);
            if (this->GetPlayerVel()->y < 0x19a) {
                this->GetPlayerVel()->y = 0x19a;
            }
            gPlayerControl->StopFollowing();
            this->func_ov00_020a8a4c(&data_ov000_020e6078, 1);
            data_ov000_020eec9c.func_ov000_020d7a84(0xd1, this->GetPlayerPos());
            this->func_ov00_020aee58(2, 2);
            mUnk_20 = this->GetPlayerPos()->y;
        } break;
        case 1: {
            this->func_ov00_020a8a4c(&data_ov000_020e6088, 1);
            this->func_ov00_020a8638(1);
            mUnk_0c                 = 1;
            mUnk_0e                 = 0;
            mUnk_12                 = 0;
            UnkStruct_027e0e58 *unk = data_027e0e58;
            func_ov000_0207c39c(unk, mUnk_2c, 0x156, 0x157, 0x158, 0x159, 0x15a, this->GetPlayerPos(), 1);
        } break;
        case 4: {
            this->func_ov005_02107c8c();
            mUnk_0c    = 2;
            Vec3p *pos = this->GetPlayerPos();
            mUnk_8c.x  = pos->x;
            mUnk_8c.y  = pos->y;
            mUnk_8c.z  = pos->z;
        } break;
        case 2: {
            s16 angle = this->func_ov00_020a8d40()->func_Ov000_020b4c2c();
            this->TurnTo(angle, angle, 0x2aab);
            this->func_ov00_020a82ac();
            data_ov000_020eec9c.func_ov000_020d7a84(0xf0, this->GetPlayerPos());
        } break;
        case 3: {
            this->func_ov00_020a8a4c(&data_ov000_020e6098, 1);
            mUnk_1c                              = this->GetPlayerPos()->y;
            s32 y                                = this->GetPlayerPos()->y;
            mUnk_20                              = y;
            this->func_ov00_020a8d40()->mUnk_09c = y;
            this->func_ov00_020a8d40()->mUnk_05a = 3;
        } break;
        case 5:
            func_ov021_02170660(this);
            break;
        case 6:
            mUnk_18 = 0;
            this->func_ov00_020a8a4c(&data_ov000_020e60a8, 1);
            break;
        case 7:
            mUnk_28[0]              = 0;
            mUnk_18                 = 0;
            *this->GetPlayerAngle() = 0;
            this->func_ov00_020a82ac();
            this->EquipItem_vfunc_28();
            this->func_ov00_020a8a4c(&data_ov000_020e60a8, 1);
            break;
        case 8:
            this->func_ov005_02108188();
            break;
        case 9:
            func_ov023_0217139c(this);
            break;
    }
}

ARM void LinkStateRoll::OnStateLeave(s32 param1) {
    LinkStateBase::OnStateLeave(param1);
    switch (mSubState) {
        case 1: {
            this->Clear_PlayerLinkBase_Unk48(1);
            UnkStruct_027e0e58 *unk = data_027e0e58;
            for (u32 i = 0; i < ARRAY_LEN(mUnk_2c); i++) {
                func_ov000_0207c444(unk, &mUnk_2c[i]);
            }
        } break;
        case 6:
            this->func_ov00_020a84bc(1);
            break;
        case 3:
            this->func_ov00_020a8d40()->mUnk_05a = 0;
            break;
        case 9:
            func_ov023_021720f0(this);
            break;
    }
    for (s32 *it = (s32 *) mUnk_2c; it != (s32 *) &mUnk_40; it++) {
        func_ov000_020b7e6c(it);
    }
}

ARM bool LinkStateRoll::vfunc_20(s32 param1) {
    if (this->GetGrabActor() == NULL) {
        if (mUnk_12 >= 7) {
            mSubState = 1;
            return true;
        }
        if (this->func_ov00_020a8b80()) {
            PlayerControl *playerControl = gPlayerControl;
            if (playerControl->func_ov00_020b12d0((s16 *) this->GetPlayerAngle()) &&
                this->func_ov00_020a8d40()->mUnk_05a == 0 && !this->HasFlags_PlayerLinkBase_Unk48(0x3f) &&
                (gGame.mModeId != GameModeId_Adventure || this->GetCurrentCharacter() != PlayerCharacter_Gongoron)) {
                mSubState = 0;
                return true;
            }
        }
    }
    if (gGame.mModeId == GameModeId_Adventure) {
        if (this->GetGrabActor() == NULL) {
            if (this->GetCurrentCharacter() == PlayerCharacter_Gongoron) {
                return func_ov023_021712fc(this, param1);
            }
            if (this->func_ov00_020a8b80() && this->func_ov00_020a8d40()->mUnk_0dc >= 0x99a &&
                (s32) gPlayerControl->func_ov00_020b034c() > 0) {
                this->func_ov005_0210f808(gPlayerControl->func_ov00_020b034c(), NULL, 0);
                mSubState = 2;
                return true;
            }
        }
        return this->func_ov005_02108094();
    }
    return false;
}

ARM bool LinkStateRoll::vfunc_24(s32 param1) {
    switch (param1) {
        case 1:
            if (mSubState != 5 && mSubState != 6 && mSubState != 7) {
                break;
            }
            return false;
        case 4:
            if (mSubState == 0) {
                break;
            }
            return false;
        case 5:
            if (mSubState != 0 && mSubState != 3 && mSubState != 8) {
                break;
            }
            return false;
        case 7:
            if (mSubState == 0 && !this->func_ov005_0211139c() && PlayerControl::func_ov00_020aeeac()) {
                return true;
            }
            break;
        case 2:
        case 3:
            break;
        case 0:
        case 6:
        default:
            return false;
    }
    return LinkStateBase::vfunc_24(param1);
}

ARM void LinkStateRoll::func_ov00_020aee58(s16 amount, u16 type) {
    if (mUnk_16 != type) {
        mUnk_12 = 0;
    }
    mUnk_12 += amount;
    mUnk_14 = 15;
    mUnk_16 = type;
}

ARM void LinkStateRoll::func_ov00_020aee84() {
    if (mUnk_14 > 0) {
        mUnk_14--;
        return;
    }
    if (mUnk_12 > 0) {
        mUnk_12--;
    }
}
