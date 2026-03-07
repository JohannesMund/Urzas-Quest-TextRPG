#include "cgenie.h"
#include "cgamemanagement.h"
#include "cgenietalkinteraction.h"
#include "colorize.h"
#include "console.h"
#include "wonderlamp/moduleressources.h"

CGenie::CGenie() : CBasicDjinn(Core::EGender::eMale)
{
    addInteraction(new CGenieTalkInteraction(this));
}

std::string CGenie::name() const
{
    return std::string(WonderLamp::genie());
}

std::string CGenie::describe() const
{
    if (_sympathy > 60)
    {
        return tr("{} is a handsome, mysterious man. he has long, black hair, her clothes look like taken directly "
                  "from the fairy tales. The upper body is naked, of course.  He is really handsome, there must be a "
                  "gym inside this bottle.",
                  name());
    }

    if (_sympathy < 40)
    {
        return tr(
            "{} exhales magic. But she is not human, and looks like the dude that constantly beat you up at school.",
            name());
    }

    return tr("{} is a mysterious, handsome man. He looks like he directly escaped a fairy tale book. He radiates "
              "magic and sex-appeal",
              name());
}

void CGenie::load(const nlohmann::json& json)
{
    for (const auto& interaction : json[TagNames::Npc::interactions])
    {
        if (CGameStateObject::compareObjectName(TagNames::WonderLamp::genieTalkInteraction, interaction))
        {
            loadInteraction<CGenieTalkInteraction>(interaction);
        }
    }
}

std::string CGenie::colorize(const std::string_view& s) const
{
    return WonderLamp::colorizeGenie(s);
}
