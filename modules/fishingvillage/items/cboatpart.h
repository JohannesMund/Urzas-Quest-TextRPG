#pragma once

#include <cjunkitem.h>

class CBoatPart : public CJunkItem
{
public:
    enum class EPart
    {
        eBoard,
        eNail,
        eRope
    };

    CBoatPart();
    EPart part() const;

    static CItem::ItemFilter partFilter(const EPart part);
    static std::string nameForPart(const EPart part);

    virtual nlohmann::json save() const override;

private:
    EPart _part;
};
