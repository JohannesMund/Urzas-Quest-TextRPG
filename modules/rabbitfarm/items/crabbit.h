#pragma once

#include <citem.h>

class CRabbit : public CItem
{
public:
    CRabbit(const unsigned int uniqueId);
    static CItem::ItemFilter rabbitFilter();
    unsigned int uniqueId() const;

    void roast();
    bool isRoasted() const;

    virtual nlohmann::json save() const override;
    virtual void load(const nlohmann::json& json) override;

protected:
    virtual std::string translatorModuleName() const override;

private:
    unsigned int _uniqueId;
    bool _isRoasted = false;
};
