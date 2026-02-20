#include "moduleressources.h"
#include "colorize.h"
#include "rabbithatch/crabbithatch.h"

#include <format>

Module::ModuleInfo RabbitHatch::moduleInfo()
{

    const auto roomFactory = [](const std::string_view& objectName) -> CRoom*
    {
        if (TagNames::RabbitHatch::rabbitHatch.compare(objectName) == 0)
        {
            return new CRabbitHatch();
        }
        return nullptr;
    };

    Module::ModuleInfo moduleInfo = Module::ModuleInfo();

    moduleInfo.moduleName = moduleName();
    moduleInfo.translatorFile = "rabbithatch";
    moduleInfo.gameStage = Module::EGameStage::eNone;

    moduleInfo.roomFactory = roomFactory;

    moduleInfo.initWorldMapFunction = [](std::vector<CRoom*>& rooms) { rooms.push_back(new CRabbitHatch()); };

    return moduleInfo;
}

std::string RabbitHatch::moduleName()
{
    return "RabbitHatch";
}

std::string RabbitHatch::katNothingH()
{
    return std::format("{}K{}a{}t {}Nothing{}H{}",
                       CC::fgGreen(),
                       CC::fgLightYellow(),
                       CC::fgYellow(),
                       CC::fgDarkGray(),
                       CC::fgWhite(),
                       CC::ccReset());
}

std::string RabbitHatch::rabbitHatchName()
{
    return std::format("{}Rabbit {}Hatch{}", CC::fgLightGray(), CC::fgYellow(), CC::ccReset());
}
