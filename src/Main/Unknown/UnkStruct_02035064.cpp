#include "Unknown/UnkStruct_02035064.hpp"
#include "Game/Game.hpp"
#include "Message/MsgProc.hpp"

extern "C" {
UnkStruct_02035064_74 *func_02023ac8(unk32 param1, unk32 param2);
void func_02028610(void *param1, UnkStruct_02035064_74 *param2, unk32 param3);
void func_0202864c(void *param1, UnkStruct_02035064_74 *param2);
void func_02028664(void *param1, u16 param2);
}

ARM UnkStruct_02035064::UnkStruct_02035064() {
    this->mUnk_74 = NULL;
    this->mUnk_78 = NULL;
    this->mUnk_7c = 0;
    this->mUnk_80 = 0;
    this->mUnk_82 = 0;
    this->mUnk_84 = 0;
    this->mUnk_86 = 0;
    this->mUnk_87 = 0;
}

ARM UnkStruct_02035064::~UnkStruct_02035064() {}

ARM void UnkStruct_02035064::func_020350b0() {}

ARM void UnkStruct_02035064::func_020350b4(s32 param1, unk32 param2, unk8 param3, s16 param4, s16 param5) {
    this->mUnk_87 = param3;

    UnkClass_027e0cbc_04 *unk = data_027e0cbc.mUnk_4[param1];
    this->mUnk_78             = unk->mUnk_8;
    func_02028610(&this->mUnk_04, func_02023ac8(this->mUnk_78->mUnk_4, 0), unk->mUnk_4);
    this->mUnk_74 = func_02023ac8(this->mUnk_78->mUnk_4, param2);
    func_0202864c(&this->mUnk_04, this->mUnk_74);

    u16 numFrames = this->mUnk_74->mUnk_00;
    this->mUnk_7c = 0;
    for (s32 i = 0; i < numFrames; i++) {
        this->mUnk_7c += this->mUnk_74->mUnk_0c[i].mUnk_4 << 12;
    }

    this->mUnk_82 = param4;
    this->mUnk_84 = param5;
}

ARM void UnkStruct_02035064::func_0203516c() {
    if (this->mUnk_78 != 0x0) {
        if (this->mUnk_86 == false) {
            this->mUnk_5c.func_0202e1e8();
            this->func_020352d8();
        } else {
            this->mUnk_86 = false;
        }
    }
}

ARM s32 UnkStruct_02035064::vfunc_00() {
    return this->mUnk_4c;
}

ARM s32 UnkStruct_02035064::vfunc_04() {
    return this->mUnk_4e;
}

ARM void UnkStruct_02035064::func_020351b8(bool param1, bool param2, bool param3, bool param4) {
    this->mUnk_7c = 0;
    u16 numFrames = this->mUnk_74->mUnk_00;
    for (s32 i = 0; i < numFrames; i++) {
        this->mUnk_7c += this->mUnk_74->mUnk_0c[i].mUnk_4 << 12;
    }
    if (param1) {
        this->mUnk_7c -= 0x1000;
    }

    s32 prevTime = this->mUnk_5c.mUnk_08;
    this->mUnk_5c.func_0202e1c4(this->mUnk_7c);
    this->mUnk_5c.mUnk_00 = param1;
    if (param2) {
        this->mUnk_5c.func_0202e670();
    }

    if (param3) {
        this->mUnk_5c.mUnk_08 = prevTime;
        this->func_020352d8();
        this->mUnk_86 = false;
    } else {
        if (param4) {
            this->mUnk_5c.func_0202e5cc();
        } else {
            this->mUnk_5c.mUnk_08 = 0;
            this->func_020352d8();
        }
        this->mUnk_86 = true;
    }

    this->mUnk_5c.mUnk_04 = gGame.mUnk_0f2 << 12;
    if (param2) {
        this->mUnk_1c = !param1 ? 4 : 3;
    } else {
        this->mUnk_1c = !param1 ? 2 : 1;
    }
    this->func_020352d8();
}

ARM void UnkStruct_02035064::func_020352d8() {
    if (this->mUnk_5c.mUnk_08 < 0) {
        this->mUnk_80 = 0;
        return;
    }
    s32 time = this->mUnk_5c.mUnk_08;

    s32 frameStart                  = 0;
    s32 i                           = 0;
    UnkStruct_02035064_74_0c *frame = this->mUnk_20->mUnk_0c;
    s32 count                       = this->mUnk_74->mUnk_00;
    for (; i < count; i++) {
        u16 duration = frame->mUnk_4;
        s32 frameEnd = frameStart + (duration << 12);
        if (frameStart <= time && time < frameEnd) {
            break;
        }
        frameStart += duration << 12;
        if (i == count - 1) {
            i--;
            frame--;
            frameStart -= duration;
        }
        frame++;
    }

    this->mUnk_80 = i;
    func_02028664(&this->mUnk_04, this->mUnk_80);
    this->mUnk_14 = time - frameStart;
}
