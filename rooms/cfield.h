#pragma once

#include "croom.h"

class CField : public CRoom
{
public:
    CField();

    virtual std::string mapSymbol() const;
};
