#pragma once

#include <ctask.h>

class CBuildEquipmentTask : public CTask
{
public:
    CBuildEquipmentTask(const std::string_view& moduleName);

    virtual void execute() override;
    virtual std::string taskNav() const override;

private:
    void buildBoat();
    void buildRod();

    const std::string _moduleName;
};
