#include "randomizer.h"

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>

unsigned int Randomizer::getRandom(const unsigned int max)
{
    return std::rand() % max;
}

void Randomizer::init()
{
    std::srand(std::time(nullptr));
}

unsigned int Randomizer::getRandomEngineSeed()
{
    return std::chrono::system_clock::now().time_since_epoch().count();
}
