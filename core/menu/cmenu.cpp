#include "cmenu.h"
#include "cgamestateobject.h"
#include "colorize.h"
#include "console.h"

#include <algorithm>
#include <cctype>
#include <format>

CMenu::CMenu() : CMenu(TagNames::Translator::core)
{
}
CMenu::CMenu(const std::string_view& moduleName) : _objectName(moduleName)
{
}

void CMenu::addMenuGroup(const CMenu::ActionList& list1, const CMenu::ActionList& list2)
{
    if (list1.empty() && list2.empty())
    {
        return;
    }

    MenuGroup grp;

    for (const auto& a : list1)
    {
        grp.first.push_back(a);
        addNav(a._key);
    }
    for (const auto& a : list2)
    {
        grp.second.push_back(a);
        addNav(a._key);
    }
    _menu.push_back(grp);
}

CMenuAction CMenu::execute()
{
    for (const auto& group : _menu)
    {
        if (group.first.empty())
        {
            if (group.second.empty())
            {
                continue;
            }
            Console::printLn(halfGroup2String(group.second), Console::EAlignment::eRight);
        }
        else
        {
            if (group.second.empty())
            {
                Console::printLn(halfGroup2String(group.first));
            }
            else
            {
                Console::printLnWithSpacer(halfGroup2String(group.first), halfGroup2String(group.second));
            }
        }
    }

    return findActionByInput();
}

CMenuAction CMenu::createAction(const std::string_view& s, const unsigned char c)
{

    if (c != 0 && isNavPossible(c))
    {
        const auto display = makeDisplayString(s, c);
        addNav(std::tolower(c));
        return CMenuAction(s, display, std::tolower(c));
    }

    for (unsigned char cc : s)
    {
        if (isNavPossible(cc))
        {
            const auto display = makeDisplayString(s, cc);
            addNav(std::tolower(cc));
            return CMenuAction(s, display, std::tolower(cc));
        }
    }
    return {};
}

CMenuAction CMenu::createShopAction(const std::string_view& name, const int cost, const unsigned char key)
{
    return createAction(std::format("{} ({} Gold)", name, cost), key);
}

void CMenu::clear()
{
    _menu.clear();
    _acceptableNavs.clear();
}

CMenuAction CMenu::executeYesNoMenu()
{
    CMenu menu;
    menu.addMenuGroup({CMenu::yes(), CMenu::no()});
    return menu.execute();
}

CMenuAction CMenu::executeAcceptRejectMenu()
{
    CMenu menu;
    menu.addMenuGroup({CMenu::accept(), CMenu::reject()});
    return menu.execute();
}

CMenuAction CMenu::yes()
{
    return CMenuAction("Yes", "[Y]es", 'y');
}

CMenuAction CMenu::no()
{
    return CMenuAction("No", "[N]o", 'n');
}

CMenuAction CMenu::exit()
{
    return CMenuAction("Exit", "E[x]it", 'x');
}

CMenuAction CMenu::accept()
{
    return CMenuAction("Accept", "[A]ccept", 'a');
}

CMenuAction CMenu::reject()
{
    return CMenuAction("Reject", "[R]eject", 'r');
}

CMenuAction CMenu::ret()
{
    return CMenuAction("Return", "[R]eturn", 'r');
}

CMenuAction CMenu::findActionByInput() const
{
    auto input = Console::getAcceptableInput(_acceptableNavs);
    for (const auto& group : _menu)
    {
        for (const auto& halfGroup : {group.first, group.second})
        {
            for (const auto& actiom : halfGroup)
            {
                if (actiom._key == input)
                {
                    return actiom;
                }
            }
        }
    }
    return {};
}

std::string CMenu::halfGroup2String(const CMenu::ActionList& l) const
{
    std::string s;
    for (const auto& a : l)
    {
        s.append(a._display);
        s.append(" ");
    }
    return s;
}

bool CMenu::isNavPossible(const unsigned char c) const
{
    return _acceptableNavs.find(std::tolower(c)) == std::string::npos;
}

std::string CMenu::makeDisplayString(const std::string_view s, const unsigned char c) const
{
    if (isNavPossible(c) == false)
    {
        return {};
    }

    std::string displayString(s);
    char cc(c);

    if (CC::isColorized(displayString))
    {
        return std::format("[{}] {}", cc, displayString);
    }

    auto it = displayString.find(cc);
    if (it == std::string::npos)
    {
        cc = std::toupper(cc);
        it = displayString.find(cc);
        if (it == std::string::npos)
        {
            return std::format("[{}] {}", cc, displayString);
        }
    }

    displayString.replace(it, 1, std::format("[{}]", cc));
    return displayString;
}

void CMenu::addNav(const unsigned char c)
{
    if (c != 0)
    {
        if (isNavPossible(c))
        {
            _acceptableNavs.push_back(c);
        }
    }
}
