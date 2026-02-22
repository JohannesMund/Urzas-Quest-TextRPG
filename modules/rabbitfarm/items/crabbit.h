#pragma once

#include <citem.h>

class CRabbit : public CItem
{
public:
    CRabbit(const unsigned int uniqueId);
    static CItem::ItemFilter rabbitFilter();
    unsigned int uniqueId() const;

protected:
    virtual std::string translatorModuleName() const override;

private:
    const unsigned int _uniqueId;
};
