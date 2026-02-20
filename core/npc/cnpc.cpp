#include "cnpc.h"
#include "colorize.h"
#include "console.h"
#include "jsontagnames.h"

CMenuAction CNpc::npcNav(CMenu& menu)
{
    return menu.createAction({CC::unColorizeString(name())}, false);
}

CNpc::CNpc(const std::string_view& objectName, const bool isFemale) : CGameStateObject(objectName), _female(isFemale)
{
}

bool CNpc::addSympathy(const int i)
{
    int originalSympathy = _sympathy;

    _sympathy += i;
    if (_sympathy < 0)
    {
        _sympathy = 0;
    }

    if (_sympathy > 1000)
    {
        _sympathy = 1000;
    }

    int diff = _sympathy - originalSympathy;

    if (diff > 0)
    {
        Console::printLn(coreTr("{} now likes you {} better", name(), diff > 100 ? "much" : ""));
    }

    if (diff < 0)
    {
        Console::printLn(coreTr("{} now likes you {} less", name(), diff < -100 ? "much" : ""));
    }

    return false;
}

nlohmann::json CNpc::save() const
{
    nlohmann::json o;
    o[TagNames::Npc::sympathy] = _sympathy;
    return o;
}

void CNpc::load(const nlohmann::json& json)
{
    _sympathy = json[TagNames::Npc::sympathy];
}

std::string CNpc::heShe() const
{
    return _female ? coreTr("she") : coreTr("he");
}

std::string CNpc::hisHer() const
{
    return _female ? coreTr("her") : coreTr("his");
}

CMenuAction CNpc::executeNpcMenu(CMenu& menu)
{

    auto talkActionString = coreTr("Talk to {}", CC::unColorizeString(name()));
    auto thinkAboutActionString = coreTr("Think about {}", CC::unColorizeString(name()));

    auto talkAction = menu.createAction({talkActionString, 'T'});
    auto thinkAboutAction = menu.createAction({thinkAboutActionString, 'i'});
    menu.addMenuGroup({talkAction, thinkAboutAction});

    auto input = menu.execute();

    if (input == talkAction)
    {
        talk();
    }

    if (input == thinkAboutAction)
    {
        thinkAbout();
    }

    return input;
}

std::string CNpc::translatorObjectName() const
{
    return std::string(TagNames::Translator::npc);
}
