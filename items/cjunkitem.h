#pragma once

#include "citem.h"

class CJunkItem : public CItem
{
public:
    CJunkItem();

    static ItemFilter junkItemFilter();
};
