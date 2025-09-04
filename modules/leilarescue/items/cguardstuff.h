#include <cjunkitem.h>

#include <enumiterator.h>

class CGuardStuff : public CJunkItem
{
public:
    enum class EPart
    {
        eBatch,
        eSword,
        eSash,
        eHelmet,
        eBoot,
        eFirstAidKit,
        eUnknown
    };

    CGuardStuff();
    EPart part() const;

    static CItem::ItemFilter guardStuffFilter(const EPart part);

    static std::string nameForPart(const EPart part);

    static bool hasAll();
    static bool has(const EPart part);
    static std::vector<std::string> listMissingParts();

    typedef EnumIterator<EPart, EPart::eBatch, EPart::eUnknown> partIterator;

private:
    EPart _part;
};