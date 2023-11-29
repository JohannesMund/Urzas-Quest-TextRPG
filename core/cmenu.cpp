#include "cmenu.h"
#include "colorize.h"
#include "console.h"

#include <algorithm>
#include <cctype>
#include <format>

CMenu::CMenu()
{
}

void CMenu::addMenuGroup(const std::vector<Action>& list1, const std::vector<Action>& list2)
{
    if (list1.empty() && list2.empty())
    {
        return;
    }

    MenuGroup grp;

    for (const auto& a : list1)
    {
        grp.first.push_back(a);
        addNav(a.key);
    }
    for (const auto& a : list2)
    {
        grp.second.push_back(a);
        addNav(a.key);
    }
    _menu.push_back(grp);
}

CMenu::Action CMenu::execute()
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

CMenu::Action CMenu::createAction(const std::string_view& s, const char c)
{
    Action menuAction;
    menuAction.name = s;

    if (c != 0 && isNavPossible(c))
    {
        menuAction.display = makeDisplayString(s, c);
        menuAction.key = std::tolower(c);
        addNav(std::tolower(c));
        return menuAction;
    }

    for (char cc : s)
    {
        if (isNavPossible(cc))
        {
            menuAction.display = makeDisplayString(s, cc);
            menuAction.key = std::tolower(cc);
            addNav(std::tolower(cc));
            return menuAction;
        }
    }
    return {};
}

void CMenu::clear()
{
    _menu.clear();
    _acceptableNavs.clear();
}

CMenu::Action CMenu::executeYesNoMenu()
{
    CMenu menu;
    menu.addMenuGroup({CMenu::yes(), CMenu::no()});
    return menu.execute();
}

CMenu::Action CMenu::executeAcceptRejectMenu()
{
    CMenu menu;
    menu.addMenuGroup({CMenu::accept(), CMenu::reject()});
    return menu.execute();
}

CMenu::Action CMenu::yes()
{
    return {"Yes", "[Y]es", 'y'};
}

CMenu::Action CMenu::no()
{
    return {"No", "[N]o", 'n'};
}

CMenu::Action CMenu::exit()
{
    return {"Exit", "E[x]it", 'x'};
}

CMenu::Action CMenu::accept()
{
    return {"Accept", "[A]ccept", 'a'};
}

CMenu::Action CMenu::reject()
{
    return {"Reject", "[R]eject", 'r'};
}

CMenu::Action CMenu::findActionByInput() const
{
    auto input = Console::getAcceptableInput(_acceptableNavs);
    for (const auto& group : _menu)
    {
        for (const auto& halfGroup : {group.first, group.second})
        {
            for (const auto& actiom : halfGroup)
            {
                if (actiom.key == input)
                {
                    return actiom;
                }
            }
        }
    }
    return {};
}

std::string CMenu::halfGroup2String(const std::vector<Action>& l) const
{
    std::string s;
    for (const auto& a : l)
    {
        s.append(a.display);
        s.append(" ");
    }
    return s;
}

bool CMenu::isNavPossible(const char c) const
{
    return _acceptableNavs.find(std::tolower(c)) == std::string::npos;
}

std::string CMenu::makeDisplayString(const std::string_view s, const char c) const
{
    if (isNavPossible(c) == false)
    {
        return {};
    }

    std::string displayString(s);

    if (CC::isColorized(displayString))
    {
        return std::format("[{}] {}", c, displayString);
    }

    char cc(c);

    auto it = displayString.find(cc);
    if (it == std::string::npos)
    {
        cc = std::toupper(cc);
        it = displayString.find(cc);
        if (it == std::string::npos)
        {
            return std::format("[{}] {}", c, displayString);
        }
    }

    displayString.replace(it, 1, std::format("[{}]", cc));
    return displayString;
}

void CMenu::addNav(const char c)
{
    if (c != 0)
    {
        if (isNavPossible(c))
        {
            _acceptableNavs.push_back(c);
        }
    }
}
