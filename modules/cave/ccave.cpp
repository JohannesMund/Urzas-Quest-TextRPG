#include "ccave.h"
#include "ccavebosstask.h"
#include "ccavedungeon.h"
#include "ccavedungeonmap.h"
#include "cgamemanagement.h"
#include "chealingwell.h"
#include "cmenu.h"
#include "colorize.h"
#include "console.h"
#include "moduleressources.h"

#include <format>

CCave::CCave() : CRoom(TagNames::Cave::cave)
{
    _showInFogOfWar = true;
    _encounterType = CEncounter::EEncounterType::eNone;
    _isRandomTaskPossible = false;
}

void CCave::execute()
{
    CRoom::execute();

    if (_isOpen)
    {
        if (CGameManagement::getProgressionInstance()->isModuleFinished(Cave::moduleName()))
        {
            Console::printLn(
                std::format("You remember this cave, you remember {} who lurked inside this cave. You also "
                            "remember, that this guy should no longer be a problem. Or is he? ",
                            Cave::getColoredBossString()));
            Console::printLn("Do you want to have a look, whether there is another Boss?");
            initDungeon();
        }
        else
        {
            Console::printLn("After all your battles and Adventures, you feel confident enought to enter this dark, "
                             "mysterious cave.");
            Console::printLn("Do you dare to enter?");
            initDungeon();
        }
    }

    else
    {
        Console::printLn(
            std::format("On a small hill, there is the entry to a cave. A deep, {}dark {}cave{}. You have a look and "
                        "all you can see is black. A Disgusting smell and strange noises come out of the cave. You "
                        "decide, that you are not enough of a hero to enter this hell hole.",
                        CC::fgLightGray(),
                        CC::fgDarkGray(),
                        CC::ccReset()));
        Console::br();
        Console::confirmToContinue();
        Console::br();
    }
}

std::string CCave::bgColor() const
{
    return CC::bgBlack();
}

std::string CCave::fgColor() const
{
    return CC::fgDarkGray();
}

void CCave::setOpen(const bool bOpen)
{
    _isOpen = bOpen;
}

CMap::RoomFilter CCave::caveFilter()
{
    return [](const CRoom* room) { return dynamic_cast<const CCave*>(room) != nullptr; };
}

bool CCave::isTaskPossible(const std::string_view& moduleName) const
{
    if (!moduleName.empty())
    {
        return moduleName.compare(Cave::moduleName()) == 0;
    }

    return CRoom::isTaskPossible(moduleName);
}

nlohmann::json CCave::save() const
{
    auto o = CRoom::save();
    o[TagNames::Cave::isOpen] = _isOpen;
    return o;
}

void CCave::load(const nlohmann::json& json)
{
    _isOpen = json.value<bool>(TagNames::Cave::isOpen, false);
    CRoom::load(json);
}

void CCave::initDungeon()
{

    if (CMenu::executeYesNoMenu() == CMenu::yes())
    {
        std::vector<CRoom*> rooms;
        rooms.push_back(
            CDungeon::makeHealingWell(Cave::getWellDescription(1), Cave::getWellQuestion(1), Cave::getWellEffect(1)));

        rooms.push_back(
            CDungeon::makeHealingWell(Cave::getWellDescription(2), Cave::getWellQuestion(2), Cave::getWellEffect(2)));

        rooms.push_back(
            CDungeon::makeHealingWell(Cave::getWellDescription(3), Cave::getWellQuestion(3), Cave::getWellEffect(3)));

        auto mapRoom = CDungeon::makeMapRoom(Cave::getMapRoomDescription());
        rooms.push_back(static_cast<CRoom*>(mapRoom));

        CCaveDungeonMap map(25, 10);
        map.setStartingPosition({0, 0});
        map.init(rooms);

        CCaveDungeon dungeon;
        dungeon.setDungeonMap(&map);
        dungeon.setMapRooom(mapRoom);

        dungeon.execute();
    }
}

char CCave::getMapSymbol() const
{

    return 'C';
}
