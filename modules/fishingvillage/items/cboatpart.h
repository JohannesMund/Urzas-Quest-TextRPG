#ifndef CBOATPART_H
#define CBOATPART_H

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

private:
    EPart _part;
};

#endif // CBOATPART_H
