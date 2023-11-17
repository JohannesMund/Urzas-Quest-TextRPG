#pragma once

#include "ressources.h"

#include <citem.h>

#include <string>
#include <vector>

#include "ressources.h"

class CEquipment : public CItem
{
public:
    CEquipment(const Ressources::Items::EType type, const Ressources::Items::EQuality quality);

    virtual bool isEnhancable() const;
    virtual std::string name() const override;
    virtual std::string typeName() const = 0;
    virtual unsigned int value() const override;

    virtual unsigned int level() const;
    virtual unsigned int upgradeCost() const;
    virtual void enhance();

    /**
     * @brief equipmentFiler
     * @return a filter function to filter equipment items from std containers
     */
    static CItem::ItemFilter equipmentFilter();
    static bool isEquipment(const CItem* item);

    /**
     * @brief enhancableEquipmentFilter
     * @return a filter function to filter equipment items that can be enhanced from std containers
     */
    static CItem::ItemFilter enhancableEquipmentFilter();

    static std::function<CEquipment*(CItem*)> equipmentTransformation();

    virtual CItem::ItemFilter equipmentTypeFilter() const = 0;

protected:
    bool doesEquipmentEffectFire() const;
    unsigned int qualityModifier() const;

    std::string nameByLevel(const unsigned int level) const;

    unsigned int _level = 0;
    std::vector<std::string> _namesByLevel;
    unsigned int _levelCap = 0;

    Ressources::Items::EType _type;
    Ressources::Items::EQuality _quality;
};
