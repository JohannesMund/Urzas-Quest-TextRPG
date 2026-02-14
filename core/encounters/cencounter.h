#pragma once

#include "ctranslatable.h"

#include <functional>
#include <string>

/**
 * @brief The CEncounter class represents an Encounter
 * Encpounters are executed randomly everytime a room is entered, when no task is available
 * @sa Ressources::Config::encounterChance
 * @remark Encounters must be registered
 * @sa EncounterRegister::encounterRegister()
 * @remark Derive from CEncounter to create a new encounter
 */

class CEncounter : public CTranslatable
{
public:
    enum EEncounterType
    {
        eNone = 0,
        eField = 1,
        eTown = 2,
        eDungeon = 4,
        eAll = 0xff
    };

    /**
     * @brief CEncounter Constructor
     */
    CEncounter();

    /**
     * @brief ~CEncounter Destructor
     */
    virtual ~CEncounter()
    {
    }

    /**
     * @brief execute executes the task
     */
    virtual void execute(const std::string_view& moduleName = {});

    /**
     * @brief encounterChance implement to set the probability for the encounter to occur
     * @remark the encounterChance is relative to the encounterChance of the BattleEncounter
     * @sa Ressources::Config::fightChance
     * @return  the chance for this encounter to occur, relative to CBattleEncounter
     */
    virtual unsigned int encounterChance(const EEncounterType& tp, const std::string_view& moduleName = {}) const = 0;

    /**
     * @brief name Name of the encounter
     * @return a string to be displayed, when the encounter executes.
     */
    virtual std::string name() const = 0;

    /**
     * @brief moduleName
     * name of the module, the encounter belongs to (if any)
     * @return the name of the module
     */
    virtual std::string moduleName() const;

    /**
     * @brief nameFilter
     * @param name
     * @return a name filter function to be used in std containers
     */
    static std::function<bool(const CEncounter*)> moduleNameFilter(const std::string_view& name);

    /**
     * @brief canBeExecuted
     * @return true if the encounter can be executed
     * @remark can be overwritten, basis version checks _isSingleExecution && _hasBeenExecuted
     */
    virtual bool canBeExecuted(const EEncounterType& tp) const;

protected:
    /**
     * @brief _isSingleExecution
     * Set to true, if the encounter shall be executed only once
     */
    bool _isSingleExecution = false;

    /**
     * @brief _hasBeenExecuted
     * Set to true, after the encounter has been executed
     * @sa _isSingleExecution
     */
    bool _hasBeenExecuted = false;

    /**
     * @brief _type
     * An Or-Conjunction of EEncounterType values, used to determin in what context an encounter can occur,
     */
    unsigned int _type;

private:
    virtual std::string translatorObjectName() const;
};
