#pragma once

#include "citem.h"
#include "json/jsontagnames.h"

class CJunkItem : public CItem
{
public:
    CJunkItem(const std::string_view& objectName = TagNames::Item::junkItem);

    static ItemFilter junkItemFilter();
};
