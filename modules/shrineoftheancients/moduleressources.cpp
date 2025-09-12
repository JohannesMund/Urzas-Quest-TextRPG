#include "moduleressources.h"
#include "cgamemanagement.h"
#include "croom.h"
#include "cshrineoftheancients.h"

void ShrineRessources::initModule()
{
}

void ShrineRessources::deInitModule()
{
    CGameManagement::getProgressionInstance()->reRegisterModuleForNextStage(moduleName());
}

void ShrineRessources::initWorldMap(std::vector<CRoom*>& rooms)
{
    rooms.push_back(new CShrineOfTheAncients());
}

CRoom* ShrineRessources::roomFactory(const std::string_view& objectName)
{
    if (TagNames::Shrine::shrine.compare(objectName) == 0)
    {
        return new CShrineOfTheAncients();
    }

    return nullptr;
}

std::string ShrineRessources::moduleName()
{
    return "ShrineOfTheAncients";
}

std::string ShrineRessources::questLog()
{
    return "Visit the shrine of the ancients.";
}
