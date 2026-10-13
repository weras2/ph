#include "Render/FadeController.hpp"

bool FadeController::Has(FadeControl *control) {}
bool FadeController::Contains(FadeControlEntry *needle, s32 length, FadeControl **haystack) {}
bool FadeController::AddIfAbsent(FadeControl *control) {}
bool FadeController::Add(FadeControlEntry *entry, s32 maxLength, s32 *length, FadeControl **list, bool allowDuplicates) {}
void FadeController::RemoveFadeControl(FadeControl *control) {}
bool FadeController::Remove(FadeControlEntry *entry, s32 *length, FadeControl **list) {}
bool FadeController::func_0202d77c(FadeControl *control) {}
bool FadeController::func_0202d7ac() {}
void FadeController::ProcessFade(s32 param1) {}
void FadeController::SetScreenBrightness(s32 param1) {}
