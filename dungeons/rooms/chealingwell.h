#pragma once

#include <cdungeonroom.h>

class CHealingWell : public CDungeonRoom
{
public:
    CHealingWell();

    virtual void execute() override;
    virtual std::string mapSymbol() const override;

    virtual void setQuestion(const std::string_view& question);
    virtual void setEffect(const std::string_view& effect);

    virtual bool isSpecialRoom() const override;

private:
    std::string _question;
    std::string _effect;
};
