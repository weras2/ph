#include "System/SysNew.hpp"
#include "Unknown/UnkStruct_02063220.hpp"

#include <nds/heap.h>

extern "C" {
void *Heap_FRMHNew(Heap_Header *heap, u32 size, int alignment);
Heap_Header *Heap_FindBlock(const void *memBlock);
void *func_0202eb94(UnkStruct_0202e894 *heap);
void *func_0202eabc(void *heap, s32 length);
void func_0202eb3c(void *heap, void *ptr);
unk32 func_0202ebbc(UnkStruct_0202e894 *heap);
}

extern char data_020576e4[];
extern char data_020576f0[];

ARM void *SysNew(UnkStruct_0202e894 *param1, s32 length, s32 param3) {
    void *result = NULL;
    switch (param1->mId) {
        case 'EXPH':
            result = Heap_EXPHNew((Heap_Header *) param1, length, param3);
            break;
        case 'FRMH':
            result = Heap_FRMHNew((Heap_Header *) param1, length, param3);
            break;
        case 'UNSH':
            result = func_0202eabc(func_0202eb94(param1), length);
            break;
    }
    if (result == NULL) {
        data_02063220.DisplayAssertError(data_020576e4, 163, data_020576f0, func_0202ebbc(param1));
    }
    return result;
}

ARM void SysDelete(void *ptr) {
    if (ptr == NULL) {
        return;
    }
    Heap_Header *heap = Heap_FindBlock(ptr);
    switch (heap->stamp) {
        case 'EXPH':
            Heap_EXPHFreeBlock(heap, ptr);
            break;
        case 'UNSH':
            func_0202eb3c(func_0202eb94((UnkStruct_0202e894 *) heap), ptr);
            break;
    }
}

ARM void *func_0202e99c(s32 length) {
    return SysNew((UnkStruct_0202e894 *) data_027e0ce0[1], length, 4);
}

ARM void *func_0202e9bc(s32 length) {
    return SysNew((UnkStruct_0202e894 *) data_027e0ce0[1], length, 4);
}

ARM void *SysObject::operator new(unsigned long length, u32 *id, u32 idLength) {
    return SysNew((UnkStruct_0202e894 *) id, length, idLength);
}

ARM void *SysObject::operator new[](unsigned long length, u32 *id, u32 idLength) {
    return SysNew((UnkStruct_0202e894 *) id, length, idLength);
}

ARM void SysObject::operator delete(void *ptr) {
    SysDelete(ptr);
}

ARM void SysObject::operator delete[](void *ptr) {
    SysDelete(ptr);
}
