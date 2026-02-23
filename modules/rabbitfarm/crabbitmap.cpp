#include "crabbitmap.h"

#include "cinventory.h"
#include "console.h"
#include "rabbitfarm/items/crabbit.h"
#include "randomizer.h"

#include <format>
#include <nlohmann/json.hpp>
#include <ranges>

CRabbitMap::CRabbitMap()
{
    for (int i = min(); i <= max(); i++)
    {
        _rabbits.emplace(i, nullptr);
    }
}

CRabbitMap::~CRabbitMap()
{
    for (auto r : _rabbits)
    {
        if (r.second != nullptr)
        {
            delete r.second;
        }
    }
}

void CRabbitMap::print()
{
    std::string line;
    for (int i = min(); i <= max(); i++)
    {
        auto r = _rabbits.at(i);

        if (r == nullptr)
        {
            line.append(".");
        }
        else
        {
            if (r->isRoasted())
            {
                line.append("x");
            }
            else
            {
                line.append("o");
            }
        }
        if (i % 15 == 0)
        {
            Console::printLn(std::format("|{}|", line), Console::EAlignment::eCenter);
            line.clear();
        }
    }
}

CRabbit* CRabbitMap::get(const int index) const
{
    if (inRange(index))
    {
        return _rabbits.at(index);
    }
    return nullptr;
}

void CRabbitMap::add(CRabbit* rabbit)
{
    auto index = rabbit->uniqueId();
    if (inRange(index))
    {
        _rabbits.at(index) = rabbit;
    }
}

std::optional<int> CRabbitMap::getRandomFreeIndex() const
{
    std::vector<int> freeIds;
    for (const auto& r : _rabbits | std::views::filter([](const auto p) { return p.second == nullptr; }))
    {
        freeIds.push_back(r.first);
    }
    if (freeIds.empty())
    {
        return {};
    }
    return Randomizer::getRandomEntry(freeIds);
}

int CRabbitMap::count()
{
    return std::count_if(_rabbits.begin(), _rabbits.end(), [](const auto r) { return r.second != nullptr; });
}

int CRabbitMap::countLiving()
{
    return std::count_if(
        _rabbits.begin(), _rabbits.end(), [](const auto r) { return r.second != nullptr && !r.second->isRoasted(); });
}

int CRabbitMap::min()
{
    return 1;
}

int CRabbitMap::max()
{
    return 151;
}

bool CRabbitMap::inRange(const int i)
{
    return i >= min() && i <= 151;
}

nlohmann::json CRabbitMap::save() const
{
    auto o = nlohmann::json::array();
    for (const auto& r : _rabbits)
    {
        if (r.second != nullptr)
        {
            o.push_back(r.second->save());
        }
    }
    return o;
}

void CRabbitMap::load(const nlohmann::json& json)
{
    for (auto o : json)
    {
        auto it = CItemFactory::loadItemFromSavGame(o);
        auto rabbit = static_cast<CRabbit*>(it);
        if (rabbit != nullptr)
        {
            _rabbits[rabbit->uniqueId()] = rabbit;
        }
    }
}
