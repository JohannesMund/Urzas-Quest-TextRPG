#pragma once

#include <cdungeonroom.h>

class CHealingWell : public CDungeonRoom
{
public:
    CHealingWell();

    virtual void execute() override;
    virtual void setQuestion(const std::string_view& question);
    virtual void setEffect(const std::string_view& effect);

    virtual bool isSpecialRoom() const override;

protected:
    virtual std::string translatorModuleName() const override;

private:
    virtual char getMapSymbol() const override;

    std::string _question;
    std::string _effect;
};
