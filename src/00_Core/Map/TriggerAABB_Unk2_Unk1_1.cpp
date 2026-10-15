#include "Map/TriggerAABB_Unk2.hpp"

ARM bool TriggerAABB_Unk2_Unk1::ContainsInXZ(Vec3p *pos) {
    return mUnk_14.ContainsInXZ(pos);
}

ARM bool TriggerAABB_Unk2_Unk1::Contains(Vec3p *pos) {
    return mUnk_14.Contains(pos);
}

ARM bool TriggerAABB_Unk2_Unk1::IntersectsCube(Cube *cube) {
    return mUnk_14.IntersectsCube(cube);
}

ARM void TriggerAABB_Unk2_Unk1::vfunc_54(Cube *param1, Vec3p *param2, u32 *param3) {
    mUnk_14.func_ov000_0208e87c(param1, param2, param3);
}
