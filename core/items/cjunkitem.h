#pragma once

#include "citem.h"

class CJunkItem : public CItem
{
public:
    CJunkItem(const std::string& objectName = "CJunkItem");

    static ItemFilter junkItemFilter();
};
