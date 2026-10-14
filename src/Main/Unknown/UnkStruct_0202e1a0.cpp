#include "Unknown/UnkStruct_0202e1a0.hpp"
#include "System/Random.hpp"

static inline u32 RandomNext(u32 max) {
    gRandom.mRandomValue = gRandom.mAddend + gRandom.mFactor * gRandom.mRandomValue;
    u64 value            = gRandom.mRandomValue >> 32;
    if (max != 0) {
        value = (value * max) >> 32;
    }
    return value;
}

UnkStruct_0202e1a0::UnkStruct_0202e1a0() {
    mUnk_00 = 0;
    mUnk_02 = 0;
    mUnk_04 = 0x1000;
    mUnk_08 = 0;
    mUnk_0c = 0;
    mUnk_10 = 0;
    mUnk_14 = 0;
}

void UnkStruct_0202e1a0::func_0202e1c4(s32 param1) {
    mUnk_00 = 0;
    mUnk_02 = 0;
    mUnk_04 = 0x1000;
    mUnk_08 = 0;
    mUnk_0c = 0;
    mUnk_10 = param1;
    mUnk_14 = 0;
}

void UnkStruct_0202e1a0::func_0202e1e8() {
    mUnk_02 &= ~5;
    if (mUnk_00 == 1 && (mUnk_02 & 8)) {
        return;
    }
    mUnk_08 = mUnk_08 + mUnk_04;

    switch (mUnk_00) {
        case 0:
            while (mUnk_08 < mUnk_0c) {
                mUnk_02 |= 3;
                s32 diff = mUnk_14 - mUnk_0c;
                if (diff <= 0) {
                    break;
                }
                mUnk_08 += diff;
            }
            while (mUnk_08 >= mUnk_10) {
                mUnk_02 |= 3;
                s32 diff = mUnk_10 - mUnk_14;
                if (diff <= 0) {
                    break;
                }
                mUnk_08 -= diff;
            }
            break;
        case 1:
            if (mUnk_08 <= mUnk_0c) {
                mUnk_02 |= 0xc;
                mUnk_08 = mUnk_0c;
            }
            if (mUnk_08 >= mUnk_10) {
                mUnk_02 |= 0xc;
                mUnk_08 = mUnk_10;
            }
            break;
    }
}

bool UnkStruct_0202e1a0::func_0202e310(s32 param1) {
    bool result = false;
    s32 prev    = mUnk_08;
    s32 next    = prev + mUnk_04;

    switch (mUnk_00) {
        case 0: {
            s32 start = mUnk_0c;
            if (prev < start) {
                if (prev <= next) {
                    if (prev <= param1 && param1 < next) {
                        result = true;
                    }
                } else {
                    if (next < start) {
                        s32 diff = mUnk_14 - start;
                        do {
                            if (diff <= 0) {
                                break;
                            }
                            next += diff;
                        } while (next < start);
                    }
                    if (next <= param1 && param1 < mUnk_14) {
                        result = true;
                    }
                }
                break;
            }
            s32 end = mUnk_10;
            if (end <= prev) {
                if (next <= prev) {
                    if (next <= param1 && param1 < prev) {
                        result = true;
                    }
                } else {
                    if (next >= end) {
                        s32 diff = end - mUnk_14;
                        do {
                            if (diff <= 0) {
                                break;
                            }
                            next -= diff;
                        } while (next >= end);
                    }
                    if (mUnk_14 <= param1 && param1 < next) {
                        result = true;
                    }
                }
            } else if (next < start) {
                if (param1 < start) {
                    result = true;
                } else {
                    if (next < start) {
                        s32 diff = mUnk_14 - start;
                        do {
                            if (diff <= 0) {
                                break;
                            }
                            next += diff;
                        } while (next < start);
                    }
                    if ((start <= param1 && param1 < prev) || (next <= param1 && param1 < mUnk_14)) {
                        result = true;
                    }
                }
            } else if (end <= next) {
                if (end <= param1) {
                    result = true;
                } else {
                    if (next >= end) {
                        s32 diff = end - mUnk_14;
                        do {
                            if (diff <= 0) {
                                break;
                            }
                            next -= diff;
                        } while (next >= end);
                    }
                    if ((prev <= param1 && param1 < end) || (mUnk_14 <= param1 && param1 < next)) {
                        result = true;
                    }
                }
            } else if (prev <= next) {
                if (prev <= param1 && param1 < next) {
                    result = true;
                }
            } else {
                if (next <= param1 && param1 < prev) {
                    result = true;
                }
            }
        } break;
        case 1: {
            s32 start = mUnk_0c;
            s32 end   = mUnk_10;
            if (next < start) {
                next = start;
            }
            if (next >= end) {
                next = end;
            }
            if (prev <= next) {
                if (prev <= param1 && param1 < next) {
                    result = true;
                }
            } else {
                if (next <= param1 && param1 < prev) {
                    result = true;
                }
            }
        } break;
    }
    return result;
}

bool UnkStruct_0202e1a0::func_0202e544() {
    bool result = false;
    if (mUnk_00 == 0) {
        if (mUnk_04 < 0) {
            result = func_0202e310(mUnk_0c);
        } else if (mUnk_04 > 0) {
            result = func_0202e310(mUnk_10);
        }
    }
    return result;
}

bool UnkStruct_0202e1a0::func_0202e58c() {
    bool result = false;
    switch (mUnk_00) {
        case 0:
            result = func_0202e544();
            break;
        case 1:
            if (mUnk_02 & 8) {
                result = true;
            }
            break;
    }
    return result;
}

void UnkStruct_0202e1a0::func_0202e5cc() {
    s32 start = mUnk_0c;
    s32 first = (start + 0xfff) >> 12;
    if (first < (mUnk_10 >> 12)) {
        s32 count = (mUnk_10 >> 12) - first + 1;
        s32 offset;
        if (count <= 0) {
            offset = 0;
        } else {
            offset = RandomNext(count);
        }
        mUnk_08 = (first + offset) << 12;
    } else {
        mUnk_08 = start;
    }
}

void UnkStruct_0202e1a0::func_0202e670() {
    mUnk_04 = -mUnk_04;
    if (mUnk_00 != 0) {
        mUnk_08 = mUnk_10;
    } else {
        mUnk_08 = 0;
        mUnk_14 = mUnk_10;
    }
}
