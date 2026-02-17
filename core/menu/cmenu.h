#pragma once

#include "cmenuaction.h"

#include <string>
#include <vector>

/**
 * @brief The CMenu class Represents a menu to capture user inputs
 */
class CGameStateObject;
class CMenu
{

public:
    /**
     * define for a group of actions
     * is always a pair:
     * [A]ccept [R]eject <---> E[x]it
     */
    using ActionList = std::vector<CMenuAction>;
    using MenuGroup = std::pair<ActionList, ActionList>;

    /**
     * @brief CMenu Constructor
     */
    CMenu(const std::string_view& moduleName);
    CMenu();
    /**
     * @brief addMenuGroup adds a Menu group
     * @remark actions should be created using createAction or a static preefined action
     * @sa createAction()
     * @param list1 the left part of the menu
     * @param list2 the right part of the menu
     * @remark either list can be empty
     */
    void addMenuGroup(const ActionList& list1, const ActionList& list2 = {});

    /**
     * @brief execute Executes the menu
     * Displays the menu, wait for the user input, return the selected action
     * @return the selected action
     */
    CMenuAction execute();

    /**
     * @brief createAction Creates an action
     * according to the input string, display string and hotkey is created
     * @param name the Name of the action (e.g. Exit)
     * @param key the hotkey, can be 0, the hotkey is determined according to the name and the hotkeys already used in
     * @param translate translate the action (default: true)
     * the menu
     * @remark the actiom will be translated(
     * @remark the key might be changed by the menu. never compare the key after execute, always compare the action.
     * @return the new action
     */
    CMenuAction createAction(const Menu::MenuAction& action, const bool translate = true);
    /**
     * @brief overload
     * @remark uses createAction to create a shop action (i.e. Buy (100 Gold)
     * @param[in] cost the number to be added in the brackets
     */
    CMenuAction createShopAction(const Menu::MenuAction& action, const int cost, const bool translate = true);

    /**
     * @brief clear
     * clears the menu
     */
    void clear();

    /**
     * @brief executeYesNoMenu execute a menu with Yes/No
     * @sa yesAction()
     * @sa noAction()
     * @return the selection of the player
     */
    static CMenuAction executeYesNoMenu();

    /**
     * @brief executeAcceptRejectMenu execute a menu with Accept/Reject
     * @sa acceptAction()
     * @sa rejectAction()
     * @return the selection of the player
     */
    static CMenuAction executeAcceptRejectMenu();

    /**
     * @brief yesAction Predefined Action "[Y]es"
     */
    static CMenuAction yes();
    /**
     * @brief noAction Predefined Action "[N]o"
     */
    static CMenuAction no();

    /**
     * @brief acceptAction Predefined Action "[A]ccept"
     */
    static CMenuAction accept();

    /**
     * @brief rejectAction Predefined Action "[R]eject"
     */
    static CMenuAction reject();

    /**
     * @brief exitAction Predefined Action "E[x]it"
     */
    static CMenuAction exit();

    /**
     * @brief exitAction Predefined Action "[R]eturn"
     */
    static CMenuAction ret();

    /**
     * @brief translation for MenuActions
     * @remark make sure not to translate actions twice.
     */
    static Menu::MenuAction tr(const std::string_view& moduleName, const Menu::MenuAction& action);

private:
    CMenuAction findActionByInput() const;
    std::string halfGroup2String(const ActionList& l) const;

    bool isNavPossible(const unsigned char c) const;
    std::string makeDisplayString(const std::string_view s, const unsigned char c) const;

    void addNav(const unsigned char c = 0);
    void resetNavs();

    std::string _acceptableNavs;
    std::vector<MenuGroup> _menu;
    const std::string _moduleName;

    Menu::MenuAction tr(const Menu::MenuAction& action);
};
