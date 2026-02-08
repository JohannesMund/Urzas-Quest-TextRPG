#pragma once

#include "ctask.h"
#include "menuaction.h"

class CBuildEquipmentTask : public CTask
{
public:
    CBuildEquipmentTask(const std::string_view& moduleName);

    virtual void execute() override;
    virtual Menu::MenuAction taskNav() const override;

private:
    void buildBoat();
    void buildRod();

    const std::string _moduleName;
};
