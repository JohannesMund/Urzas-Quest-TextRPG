#pragma once

#include <map>
#include <nlohmann/json_fwd.hpp>

class CRabbit;
class CRabbitMap
{
public:
    CRabbitMap();
    ~CRabbitMap();

    void print();

    CRabbit* get(const int index) const;
    void add(CRabbit* rabbit);
    int getRandomFreeIndex() const;

    static int min();
    static int max();
    static bool inRange(const int i);

    nlohmann::json save() const;
    void load(const nlohmann::json& json);

private:
    std::map<int, CRabbit*> _rabbits;
};