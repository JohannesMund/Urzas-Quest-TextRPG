#pragma once

#include <map>

class CRabbit;
class CRabbitMap
{
public:
    CRabbitMap();
    ~CRabbitMap();

    void print();

    CRabbit* get(const int index) const;
    void add(CRabbit* rabbit);

    static int min();
    static int max();
    static bool inRange(const int i);

private:
    std::map<int, CRabbit*> _rabbits;
};