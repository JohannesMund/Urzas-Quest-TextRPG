#include "crabbitmap.h"

#include "console.h"
#include "rabbitfarm/items/crabbit.h"

#include <format>

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
