#pragma once

#include <string>
#include <vector>

/**
 * @brief The CMenu class Represents a menu to capture user inputs
 */

class CMenu
{

public:
    /**
     * @brief The Action class
     * Represents one Action (Name (e.g. Exit), Displaystring (e.g. E[x]it) (Hot-)key (e.g. 'x')
     */
    struct Action
    {
        std::string name;
        std::string display;
        unsigned char key = 0;
        bool operator==(const Action& other) const
        {
            return key == other.key;
        }
        bool operator!=(const Action& other) const
        {
            return key != other.key;
        }
    };

    /**
     * define for a group of actions
     * is always a pair:
     * [A]ccept [R]eject <---> E[x]it
     */
    using ActionList = std::vector<Action>;
    using MenuGroup = std::pair<ActionList, ActionList>;

    /**
     * @brief CMenu Constructor
     */
    CMenu();

    /**
     * @brief addMenuGroup adds a Menu group
     * @remark actions should be created using createAction or a static preefined action
     * @sa createAction()
     * @param list1 the left part of the menu
     * @param list2 the right part of the menu
     * @remark either list can be empty
     */
    void addMenuGroup(const std::vector<Action>& list1, const std::vector<Action>& list2 = {});

    /**
     * @brief execute Executes the menu
     * Displays the menu, wait for the user input, return the selected action
     * @return the selected action
     */
    Action execute();

    /**
     * @brief createAction Creates an action
     * according to the input string, display string and hotkey is created
     * @param name the Name of the action (e.g. Exit)
     * @param key the hotkey, can be 0, the hotkey is determined according to the name and the hotkeys already used in
     * the menu
     * @return the new action
     */
    Action createAction(const std::string_view& name, const unsigned char key = 0);

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
    static Action executeYesNoMenu();

    /**
     * @brief executeAcceptRejectMenu execute a menu with Accept/Reject
     * @sa acceptAction()
     * @sa rejectAction()
     * @return the selection of the player
     */
    static Action executeAcceptRejectMenu();

    /**
     * @brief yesAction Predefined Action "[Y]es"
     */
    static Action yes();
    /**
     * @brief noAction Predefined Action "[N]o"
     */
    static Action no();

    /**
     * @brief acceptAction Predefined Action "[A]ccept"
     */
    static Action accept();

    /**
     * @brief rejectAction Predefined Action "[R]eject"
     */
    static Action reject();

    /**
     * @brief exitAction Predefined Action "E[x]it"
     */
    static Action exit();

    /**
     * @brief exitAction Predefined Action "[R]eturn"
     */
    static Action ret();

private:
    Action findActionByInput() const;
    std::string halfGroup2String(const std::vector<Action>& l) const;

    bool isNavPossible(const unsigned char c) const;
    std::string makeDisplayString(const std::string_view s, const unsigned char c) const;

    void addNav(const unsigned char c = 0);

    std::string _acceptableNavs;
    std::vector<MenuGroup> _menu;
};
