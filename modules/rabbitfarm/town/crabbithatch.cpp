#include "crabbithatch.h"

#include "cgamemanagement.h"
#include "console.h"
#include "rabbitfarm/ckatnothingh.h"
#include "rabbitfarm/items/crabbit.h"
#include "rabbitfarm/moduleressources.h"

CRabbitHatch::CRabbitHatch(CKatNothingH* kat) : CTownModule(TagNames::RabbitFarm::rabbitHatch), _kat(kat)
{
    for (int i = 0; i <= 150; i++)
    {
        _rabbits.emplace(i, nullptr);
    }
}

void CRabbitHatch::execute()
{
}

CMenuAction CRabbitHatch::townModuleNav(CMenu& menu) const
{
    return menu.createAction({"Rabbit Hatch"});
}

std::string CRabbitHatch::translatorModuleName() const
{
    return std::string(RabbitFarm::moduleName());
}

std::string CRabbitHatch::translatorObjectName() const
{
    return std::string(TagNames::RabbitFarm::rabbitHatch);
}

void CRabbitHatch::donate()
{
}

void CRabbitHatch::watch()
{
}

void CRabbitHatch::talk()
{
}

void CRabbitHatch::deliverRabbit()
{
    auto rabbits = CGameManagement::getInventoryInstance()->getItemsByFilter(CRabbit::rabbitFilter());
    if (!rabbits.size())
    {
        Console::printLn(tr("Turns out, you do not have a rabbit. You better go now."));
        return;
    }

    auto item = CGameManagement::getInventoryInstance()->takeItem(rabbits.at(0));
    if (!item.has_value())
    {
        assert(!"Take does not seem to work");
    }

    auto rabbit = dynamic_cast<CRabbit*>(*item);
    if (rabbit == nullptr)
    {
        assert(!"Rabbit is not a rabbit");
    }

    _rabbits[rabbit->uniqueId()] = rabbit;

    _kat->addSympathy(50);
}
