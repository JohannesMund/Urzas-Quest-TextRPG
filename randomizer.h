#pragma once

#include "itemfactory.h"
#include <random>
#include <vector>

class CRoom;
namespace Randomizer
{
void init();

unsigned int getRandom(const unsigned int max);

unsigned int getRandomEngineSeed();

} // namespace Randomizer
