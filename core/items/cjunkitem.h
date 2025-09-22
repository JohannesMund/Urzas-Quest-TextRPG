#pragma once

#include "cgamestatetagnames.h"
#include "citem.h"

class CJunkItem : public CItem
{
public:
    CJunkItem(const std::string_view& objectName = TagNames::Item::junkItem);

    static ItemFilter junkItemFilter();
};
