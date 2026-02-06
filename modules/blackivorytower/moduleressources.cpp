#include "moduleressources.h"
#include "cblackivorytower.h"
#include "cgamemanagement.h"
#include "cgameprogression.h"
#include "colorize.h"
#include "croom.h"
#include "ressources.h"

#include <format>

std::string BlackIvoryTower::darkIvoryTower()
{
    return std::format("{0}Dark {1}Ivory {0}Tower of the {2}", CC::fgDarkGray(), CC::fgLightGray(), lunatics());

    return std::string();
}

std::string BlackIvoryTower::lunatic()
{
    return std::format(
        "{}Lu{}na{}ti{}c{}", CC::fgYellow(), CC::fgLightRed(), CC::fgLightGreen(), CC::fgLightCyan(), CC::ccReset());
}

std::string BlackIvoryTower::lunatics()
{
    return std::format("{}{}s{}", lunatic(), CC::fgLightCyan(), CC::ccReset());
}

std::string BlackIvoryTower::moduleName()
{
    return "BlackIvoryTowerofLunatics";
}

Module::ModuleInfo BlackIvoryTower::moduleInfo()
{
    const auto roomFactory = [](const std::string_view& objectName) -> CRoom*
    {
        if (TagNames::BlackIvoryTower::blackIvoryTower.compare(objectName) == 0)
        {
            return new CBlackIvoryTower();
        }

        return nullptr;
    };

    Module::ModuleInfo moduleInfo = Module::ModuleInfo();

    moduleInfo.moduleName = moduleName();
    moduleInfo.translatorFile = "blackivorytower";
    moduleInfo.gameStage = Module::EGameStage::eFoundCult;

    moduleInfo.questLogFunction = []() { return std::format("Climb up the {}", darkIvoryTower()); };
    moduleInfo.initWorldMapFunction = [](std::vector<CRoom*>& rooms) { rooms.push_back(new CBlackIvoryTower()); };
    moduleInfo.roomFactory = roomFactory;

    return moduleInfo;
}