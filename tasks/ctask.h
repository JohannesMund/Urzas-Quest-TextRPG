#pragma once

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

protected:
    bool _isFinished = false;
};
