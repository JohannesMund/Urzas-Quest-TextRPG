#include "cfishingfritz.h"
#include "colorconsole.h"
#include "console.h"
#include "fishingvillage/moduleressources.h"

#include <format>

CFishingFritz::CFishingFritz()
{
    Console::printLn(std::format("{}", FishingVillageRessources::fishingFritz()), Console::EAlignment::eCenter);
    Console::printLn(std::format("Fishing fresh fish since 832 ad. dragonis", FishingVillageRessources::fishingFritz()),
                     Console::EAlignment::eCenter);
    Console::br();
    Console::printLn("Closed for now.");
}

void CFishingFritz::execute()
{
}
