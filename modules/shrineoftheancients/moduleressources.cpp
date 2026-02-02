#include "moduleressources.h"
#include "cgamemanagement.h"
#include "croom.h"
#include "cshrineoftheancients.h"

std::string ShrineRessources::moduleName()
{
    return "ShrineOfTheAncients";
}

Module::ModuleInfo ShrineInfo::moduleInfo()
{
    const auto roomFactory = [](const std::string_view& objectName) -> CRoom*
    {
        if (TagNames::Shrine::shrine.compare(objectName) == 0)
        {
            return new CShrineOfTheAncients();
        }

        return nullptr;
    };

    Module::ModuleInfo moduleInfo = Module::ModuleInfo();

    moduleInfo.moduleName = ShrineRessources::moduleName();
    moduleInfo.translatorFile = "shrineoftheancients";
    moduleInfo.gameStage = Module::EGameStage::eStart,
    moduleInfo.questLogFunction = []() { return "Visit the shrine of the ancients."; };
    moduleInfo.deInitFunction = []()
    { CGameManagement::getProgressionInstance()->reRegisterModuleForNextStage(ShrineRessources::moduleName()); };
    moduleInfo.initWorldMapFunction = [](std::vector<CRoom*>& rooms) { rooms.push_back(new CShrineOfTheAncients()); };
    moduleInfo.roomFactory = roomFactory;

    return moduleInfo;
}
