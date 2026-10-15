#include "Player/LinkStateCutscene.hpp"
#include "Player/PlayerControlData.hpp"
#include "Player/PlayerLink.hpp"

static LinkStateCutscene *GetLinkStateCutscene();

ARM bool PlayerLink::vfunc_44(Vec3p *param1) {
    GetLinkStateCutscene()->mSubState = 0;
    ChangeLinkState(LinkStateId_Cutscene);
    gPlayerControlData->vfunc_50();
    gPlayerControlData->vfunc_54(param1);
    GetLinkStateCutscene()->func_ov000_020b309c(param1);
    return true;
}

ARM static LinkStateCutscene *GetLinkStateCutscene() {
    return (LinkStateCutscene *) GetLinkState(LinkStateId_Cutscene);
}

ARM void PlayerLink::vfunc_48(Vec3p *param1) {
    gPlayerControlData->vfunc_54(param1);
    GetLinkStateCutscene()->func_ov000_020b309c(param1);
}

ARM void PlayerLink::vfunc_4c() {
    gPlayerControlData->vfunc_58();
    ChangeLinkState(LinkStateId_Move);
}
