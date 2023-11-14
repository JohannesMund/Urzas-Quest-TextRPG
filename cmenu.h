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
        char key;
        bool operator==(const Action& other) const
        {
            return key == other.key;
        }
    };

    /**
     * define for a group of actions
     * is always a pair:
     * [A]ccept [R]eject <---> E[x]it
     */
    using MenuGroup = std::pair<std::vector<Action>, std::vector<Action>>;

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
    Action createAction(const std::string_view& name, const char key = 0);

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
    static Action yesAction();
    /**
     * @brief noAction Predefined Action "[N]o"
     */
    static Action noAction();

    /**
     * @brief acceptAction Predefined Action "[A]ccept"
     */
    static Action acceptAction();

    /**
     * @brief rejectAction Predefined Action "[R]eject"
     */
    static Action rejectAction();

    /**
     * @brief exitAction Predefined Action "E[x]it"
     */
    static Action exitAction();

    /**
     * @brief yes check, if action a is "[Y]es"
     * @sa yesAction()
     */
    static bool yes(const Action& a);

    /**
     * @brief no check, if action is "[N]o"
     * @sa noAction()
     * @return
     */
    static bool no(const Action& a);

    /**
     * @brief accept check, if action is "[A]ccept"
     * @sa acceptAction()
     * @return
     */
    static bool accept(const Action& a);

    /**
     * @brief reject check, if action is "[R]eject"
     * @sa rejectAction()
     * @return
     */
    static bool reject(const Action& a);

    /**
     * @brief exit check, if action is "E[x]it"
     * @sa exitAction()
     */
    static bool exit(const Action& a);

private:
    Action findActionByInput() const;
    std::string halfGroup2String(const std::vector<Action>& l) const;

    bool isNavPossible(const char c) const;
    std::string makeDisplayString(const std::string_view s, const char c) const;

    void addNav(const char c = 0);

    std::string _acceptableNavs;
    std::vector<MenuGroup> _menu;
};
