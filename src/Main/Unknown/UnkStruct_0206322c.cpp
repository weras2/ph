#include "Unknown/UnkStruct_0206322c.hpp"
#include "global.h"
#include "types.h"
#include <stdarg.h>

void func_02027ab4(unk32, Screen *, UNK_PTR, UNK_PTR, unk32, unk32, unk32, unk32);

extern "C" {
unk32 *MountCompressedNarc(char *, char *, unk8 *, unk32, unk32);
unk8 data_020691a0[0xCC00];
UNK_PTR func_02032054(char *, unk32);
UNK_PTR func_0203206c(char *, unk32);
void func_02016fcc(unk32 *);

void GX_LoadBG0Scr(u16 *data, unk32, u32 size);
void GXS_LoadBG0Scr(u16 *data, unk32, u32 size);
void CleanAndInvalidateDataCacheLines(void *, u32 size); // DC_FlushRange?
void Fill16(unk32, void *, u32 size);
int vsnprintf(char *s, size_t n, const char *format, va_list arg);
bool func_02030758(s32 ch);
bool func_020307dc(s32 ch);
s32 func_02030730(s32 ch);
s32 func_020306c0(char *str, s32 length);
}

THUMB void UnkStruct_0206322c::func_02030354(bool doTopScreen, bool doBottomScreen) {
    Screen *pScreen;
    unk32 *uVar1;

    uVar1         = MountCompressedNarc("BGF", "Menu/UI_main/DbgFntM.bin", data_020691a0, sizeof(data_020691a0), 1);
    this->mUnk_00 = func_02032054("BGF:DbgFntM.ncgr", 1);
    this->mUnk_04 = func_0203206c("BGF:UIM.nclr", 1);

    if (doTopScreen) {
        pScreen          = &this->topScreen;
        pScreen->mUnk_00 = 0x100;
        pScreen->mUnk_02 = 0xC0;
        pScreen->mUnk_04 = 0;
        pScreen->mUnk_06 = 0;
        pScreen->mUnk_08 = 0xC00;
        func_02027ab4(0, pScreen, this->mUnk_00, this->mUnk_04, 0, 0, 0, 2);
    }

    if (doBottomScreen) {
        pScreen          = &this->bottomScreen;
        pScreen->mUnk_00 = 0x100;
        pScreen->mUnk_02 = 0xC0;
        pScreen->mUnk_04 = 0;
        pScreen->mUnk_06 = 0;
        pScreen->mUnk_08 = 0xC00;
        func_02027ab4(4, pScreen, this->mUnk_00, this->mUnk_04, 0, 0, 0, 2);
    }

    func_02016fcc(uVar1);
}

THUMB void *UnkStruct_0206322c::func_02030408(void) {
    this->mUnk_00 = NULL;
    this->mUnk_04 = NULL;
    this->func_020304a8(true, true);
    return this;
}

// Screen::data starts 6 halfwords into the Screen
#define SCREEN_TILE(screen, x, y) (((u16 *) &(screen))[(x) + (y) * SCREEN_WIDTH + 6])

extern "C" THUMB void func_02030420(UnkStruct_0206322c *param1, s32 x, s32 y, s32 tile, unk32 bottomScreen, s32 palette) {
    if (!(u8) bottomScreen) {
        SCREEN_TILE(param1->topScreen, x, y) = tile | palette << 12;
    } else {
        SCREEN_TILE(param1->bottomScreen, x, y) = tile | palette << 12;
    }
}

THUMB void UnkStruct_0206322c::func_02030464(bool doTopScreen, bool doBottomScreen) {
    if (doTopScreen) {
        CleanAndInvalidateDataCacheLines(&this->topScreen.data, sizeof(this->topScreen.data));
        GX_LoadBG0Scr(this->topScreen.data, 0, sizeof(this->topScreen.data));
    }

    if (doBottomScreen) {
        CleanAndInvalidateDataCacheLines(&this->bottomScreen.data, sizeof(this->bottomScreen.data));
        GXS_LoadBG0Scr(this->bottomScreen.data, 0, sizeof(this->bottomScreen.data));
    }
}

THUMB void UnkStruct_0206322c::func_020304a8(bool doTopScreen, bool doBottomScreen) {
    if (doTopScreen) {
        Fill16(0, this->topScreen.data, sizeof(this->topScreen.data));
    }

    if (doBottomScreen) {
        Fill16(0, this->bottomScreen.data, sizeof(this->bottomScreen.data));
    }
}

extern "C" s32 func_020305ac(s32 x, s32 y, s32 palette, s32 ch, unk32 bottomScreen);

THUMB void DisplayDebugText(unk32 x, unk32 y, unk32 align, unk32 palette, char *str, unk32 bottomScreen) {
    s32 col = -1;
    s32 ch;
    s32 length = 0;
    s32 startX = x;
    u8 *s      = (u8 *) str;

    if (*s == 0) {
        return;
    }

    do {
        if (col >= SCREEN_WIDTH || (func_02030758(ch) && col > SCREEN_WIDTH - 2)) {
            y++;
            col = -1;
        }
        if (col < 0) {
            switch (align) {
                case 1:
                    startX = x - (func_020306c0(str, length) >> 1);
                    if (startX < 0) {
                        startX = 0;
                    }
                    break;
                case 2:
                    startX = x - func_020306c0(str, length);
                    if (startX < 0) {
                        startX = 0;
                    }
                    break;
                case 0:
                    startX = x;
                    break;
            }
            col = startX;
        }

        ch = *s++;
        length++;
        if (ch >= 0x80 && *s != 0) {
            ch = ch << 8 | *s;
            s++;
            length++;
        }

        if (ch == '\n') {
            y++;
            col = -1;
        } else {
            if (func_020305ac(col, y, palette, ch, bottomScreen) == 1) {
                col++;
            }
            col++;
        }
    } while (*s != 0);
}

extern "C" THUMB s32 func_020305ac(s32 x, s32 y, s32 palette, s32 ch, unk32 bottomScreen) {
    s32 result = 0;
    s32 second = 0;

    if (ch >= 0x8000) {
        if (func_02030758(ch)) {
            ch--;
            second = 0x814a;
        } else if (func_020307dc(ch)) {
            second = 0x814b;
            ch -= 2;
        }
        ch = func_02030730(ch);
    }

    for (s32 i = 0; i < 2; i++) {
        ch -= 32;
        func_02030420(&data_0206322c, x, y, ch, bottomScreen, palette);
        if (i != 0 || second == 0) {
            break;
        }
        ch     = func_02030730(second);
        result = 1;
        x++;
    }
    return result;
}

THUMB void DisplayDebugTextFormat(unk32 param1, unk32 x, unk32 y, unk32 unkVal1, unk32 unkVal2, char *fmt, va_list args) {
    char buffer[0x100];

    vsnprintf(buffer, sizeof(buffer), fmt, args);
    DisplayDebugText(x, y, unkVal1, unkVal2, buffer, param1);
}

THUMB void DisplayDebugTextFormat_thunk(unk32 param1, unk32 param2, unk32 param3, unk32 param4, unk32 param5, char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    DisplayDebugTextFormat(param1, param2, param3, param4, param5, fmt, args);
    va_end(args);
}

THUMB void DisplayDebugTextF(unk32 x, unk32 y, unk32 unkVal1, unk32 unkVal2, char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    DisplayDebugTextFormat(0, x, y, unkVal1, unkVal2, fmt, args);
    va_end(args);
}
