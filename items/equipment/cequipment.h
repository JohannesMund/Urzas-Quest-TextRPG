#pragma once

#include <citem.h>

#include <string>
#include <vector>

class CEquipment : public CItem
{
public:
    enum class EType
    {
        eSword,
        eShield,
        eArmor,
        eOther
    };

    enum class EQuality
    {
        eJunk,
        eFair,
        eGood,
        eAwesomne
    };

    CEquipment();

    virtual bool isEnhancable() const;
    virtual std::string name() const override;
    virtual std::string typeName() const = 0;

    virtual unsigned int level() const;
    virtual unsigned int upgradeCost() const;
    virtual void enhance();

    /**
     * @brief equipmentFiler
     * @return a filter function to filter equipment items from std containers
     */
    static std::function<bool(const CItem*)> equipmentFilter();
    static bool isEquipment(const CItem* item);

    /**
     * @brief enhancableEquipmentFilter
     * @return a filter function to filter equipment items that can be enhanced from std containers
     */
    static std::function<bool(const CItem*)> enhancableEquipmentFilter();

    static std::function<CEquipment*(CItem*)> equipmentTransformation();

    virtual std::function<bool(const CItem*)> equipmentTypeFilter() const = 0;

protected:
    bool doesEquipmentEffectFire() const;

    unsigned int _level = 0;
    std::vector<std::string> _namesByLevel;
    unsigned int _levelCap = 0;

    EType _type;
    EQuality _quality;
};
