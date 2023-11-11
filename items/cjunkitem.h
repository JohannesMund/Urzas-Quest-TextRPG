#pragma once

#include "citem.h"

class CJunkItem : public CItem
{
public:
    CJunkItem();

    static std::function<bool(const CItem*)> junkItemFilter();
};
