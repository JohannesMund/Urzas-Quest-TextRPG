#pragma once

#include <string>

/**
 * @brief The CTask class Represents a Task
 * Tasks are placed in a room and are executed, as soon as the room is entered
 * Tasks show themselfes on the map with a '!'
 * @sa CRoom
 * @sa CRoom::addTask()
 * @remark Derive from CTask to create a new task
 */

class CTask
{
public:
    /**
     * @brief CTask Constructor
     */
    CTask();
    /**
     * @brief ~CTask Destructor
     */
    virtual ~CTask()
    {
    }

    /**
     * @brief execute executes the task
     */
    virtual void execute() = 0;

    /**
     * @brief isFinished
     * @return true if the task is finished
     * @remark tasks will be deleted when isFinished is true
     */
    bool isFinished();

    /**
     * @brief isAutoExecute
     * Set by the dereived class. determins, wether the task is automatically executed, when the player enters the
     * field, or whether the task provides a nav
     * @sa taskNav()
     * @return is the task auto executed
     */
    bool isAutoExecute() const;

    /**
     * @brief taskNav
     * @return a string to be added to the menu to execute the task manually
     * @sa isAutoExecute()
     * @remark only used, when _isAutoExecute == false
     */
    virtual std::string taskNav() const;

    /**
     * @brief moduleName
     * @return a moduleName for the task. handed over to the room, when attempting to place the task
     * @sa CRoom::isTaskPossible()
     */
    virtual std::string moduleName() const;

protected:
    bool _isFinished = false;
    bool _isAutoExecute = true;
};
