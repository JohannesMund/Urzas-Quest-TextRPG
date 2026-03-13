#pragma once

#include <map>
#include <nlohmann/json_fwd.hpp>
#include <optional>

class CRabbit;
class CRabbitMap
{
public:
    CRabbitMap();
    ~CRabbitMap();

    void print();

    CRabbit* get(const int index) const;
    CRabbit* getRandom();
    void add(CRabbit* rabbit);
    std::optional<int> getRandomFreeIndex() const;
    size_t count();
    size_t countLiving();

    static size_t min();
    static size_t max();
    static bool inRange(const size_t i);

    nlohmann::json save() const;
    void load(const nlohmann::json& json);

private:
    std::map<int, CRabbit*> _rabbits;
};