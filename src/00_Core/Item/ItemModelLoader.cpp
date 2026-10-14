#include "Item/ItemModelLoader.hpp"
#include "DTCM/UnkStruct_027e0d38.hpp"
#include "System/SysNew.hpp"

class ItemModelLoader_Archive {
public:
    /* 00 */ virtual void vfunc_00();
    /* 04 */ virtual void vfunc_04();
    /* 08 */ virtual void vfunc_08(s32 param1);
    /* 0c */ virtual void vfunc_0c();

    /* 04 */ unk32 mUnk_04;
    /* 08 */ unk32 mUnk_08;
};

struct ItemModelLoader_File {
    /* 00 */ unk32 mUnk_00;
    /* 04 */ unk32 mUnk_04;
    /* 08 */ unk32 mUnk_08;
    /* 0c */ unk32 mUnk_0c;
    /* 10 */ unk32 mUnk_10;
    /* 14 */
};

extern ItemModelLoader_Archive *data_ov000_020e691c[6];
extern ItemModelLoader_Archive *data_ov000_020e6934[16];
extern ItemModelLoader_File data_ov000_020ee4e4[6];
extern char data_ov000_020e6974[];
extern char data_ov000_020e6978[];
extern char data_ov000_020e6988[];
extern char data_ov000_020e698c[];

extern "C" {
void *func_0202d598(s32 param1, u32 *heap, char *param3, char *param4, s32 param5, s32 param6);
void func_0202d5dc(void *param1);
void func_020300cc(ItemModelLoader_File *param1);
unk32 func_ov000_020bd728(ItemModelLoader_Archive *param1, ItemModelLoader_File *param2, s32 param3, s32 param4);
unk32 func_0201e4cc(unk32 param1);
s32 *func_0201e24c(s32 param1, char *param2);
unk32 func_ov000_020c0bdc(ItemModelLoader_Archive *param1, unk32 param2);
}

THUMB ItemModelLoader::ItemModelLoader() {
    for (s32 i = 0; i < 2; i++) {
        (&mItems)[i] = NULL;
    }
    for (s32 j = 0; j < 6; j++) {
        mUnk_08[j] = 0;
    }

    mItems = func_0202d598(0x92, data_027e0ce0[1], data_ov000_020e6974, data_ov000_020e6978, 0x10, 1);
    if (data_027e0d38->mUnk_14 != 1 &&
        (data_027e0d38->func_ov000_02078b40() == 1 || data_027e0d38->func_ov000_02078b40() == 3 ||
         data_027e0d38->func_ov000_02078b40() == 4)) {
        mDungeonItems = func_0202d598(0x92, data_027e0ce0[1], data_ov000_020e6988, data_ov000_020e698c, 0x10, 1);
    }

    if (data_027e0d38->func_ov000_02078b40() == 2) {
        func_ov000_020bb34c(0);
        func_ov000_020bb390(2);
        func_ov000_020bb390(3);
        func_ov000_020bb390(5);
    } else if (data_027e0d38->mUnk_14 != 1) {
        func_ov000_020bb34c(4);
        func_ov000_020bb390(12);
        func_ov000_020bb390(13);
        func_ov000_020bb390(14);
    }
}

THUMB ItemModelLoader *ItemModelLoader::func_ov000_020bb2ec() {
    for (s32 i = 0; i < 6; i++) {
        if (data_ov000_020e691c[i] != NULL) {
            data_ov000_020e691c[i]->vfunc_0c();
        }
        func_020300cc(&data_ov000_020ee4e4[i]);
    }
    for (s32 j = 0; j < 16; j++) {
        data_ov000_020e6934[j]->vfunc_0c();
    }
    for (s32 i = 0; i < 2; i++) {
        if ((&mItems)[i] != NULL) {
            func_0202d5dc((&mItems)[i]);
        }
    }
    return this;
}

THUMB unk32 ItemModelLoader::func_ov000_020bb34c(s32 index) {
    mUnk_08[index] = func_ov000_020bd728(data_ov000_020e691c[index], &data_ov000_020ee4e4[index], 1, 0);
    return mUnk_08[index];
}

THUMB unk32 ItemModelLoader::func_ov000_020bb378(s32 param1) {
    return func_0201e4cc(data_ov000_020ee4e4[param1].mUnk_08);
}

THUMB unk32 ItemModelLoader::func_ov000_020bb390(s32 equipId) {
    data_ov000_020e6934[equipId]->vfunc_08(16);
    return (unk32) data_ov000_020e6934[equipId];
}

THUMB unk32 ItemModelLoader::func_ov000_020bb3a8(s32 param1) {
    return (unk32) data_ov000_020e6934[param1];
}

THUMB s32 ItemModelLoader::func_ov000_020bb3b4(s32 param1, char *param2) {
    s32 data = mUnk_08[param1];
    if (data != 0) {
        return data + *func_0201e24c(data + 8, param2);
    }
    return 0;
}

THUMB unk32 ItemModelLoader::func_ov000_020bb3d4(s32 param1, unk32 param2) {
    ItemModelLoader_Archive *archive = data_ov000_020e6934[param1];
    if (archive->mUnk_08 != 0) {
        return func_ov000_020c0bdc(archive, param2);
    }
    return 0;
}

THUMB s32 ItemModelLoader::func_ov000_020bb3f4(char *param2) {
    s32 result = func_ov000_020bb3b4(5, param2);
    if (result == 0) {
        result = func_ov000_020bb3b4(4, param2);
    }
    return result;
}

THUMB unk32 ItemModelLoader::func_ov000_020bb414(unk32 param1) {
    return func_ov000_020bb3d4(12, param1);
}

THUMB unk32 ItemModelLoader::func_ov000_020bb420(unk32 param1) {
    return func_ov000_020bb3d4(13, param1);
}

THUMB unk32 ItemModelLoader::func_ov000_020bb42c(unk32 param1) {
    unk32 result = func_ov000_020bb3d4(14, param1);
    if (result == 0) {
        result = func_ov000_020bb3d4(15, param1);
    }
    return result;
}
