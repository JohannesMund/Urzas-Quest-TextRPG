#pragma once
#include <map>
#include <string>

namespace Core
{
enum class EGender
{
    eMale,
    eFemale
};

enum class EDirections
{
    eNone,
    eNorth,
    eEast,
    eSouth,
    eWest
};

enum class EAlignment
{
    eHorizontal,
    eVertical
};

static const std::map<EDirections, std::string> dirMap = {{EDirections::eNorth, "North"},
                                                          {EDirections::eSouth, "South"},
                                                          {EDirections::eWest, "West"},
                                                          {EDirections::eEast, "East"},
                                                          {EDirections::eNone, "None"}};

static std::string_view direction2String(const EDirections d)
{
    return dirMap.at(d);
}

} // namespace Core
