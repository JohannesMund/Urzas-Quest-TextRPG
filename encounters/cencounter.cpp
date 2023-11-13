#include "cencounter.h"
#include "console.h"

#include <format>

CEncounter::CEncounter()
{
}

void CEncounter::execute(const std::string_view&)
{
    Console::printLn("Encounter", Console::EAlignment::eCenter);
    Console::printLn(name(), Console::EAlignment::eCenter);
    Console::br();
}

std::string CEncounter::moduleName() const
{
    return {};
}

std::function<bool(const CEncounter*)> CEncounter::moduleNameFilter(const std::string_view& name)
{
    return [&name](const CEncounter* encounter) { return encounter->moduleName().compare(name) == 0; };
}

bool CEncounter::canBeExecuted(const EEncounterType& type) const
{
    if ((_type & type) != type)
    {
        return false;
    }
    return !(_isSingleExecution && _hasBeenExecuted);
}
