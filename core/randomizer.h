#pragma once

#include "citemfactory.h"

#include <random>
#include <string>
#include <vector>

class CRoom;
namespace Randomizer
{
void init();

unsigned int getRandom(const unsigned int max);

unsigned int getRandomEngineSeed();

std::string getRandomStringFromVector(const std::vector<std::string>& vector);

template <typename T>
T getRandomEntry(const std::vector<T>& vector)
{
    return vector.at(getRandom(vector.size()));
}

} // namespace Randomizer
