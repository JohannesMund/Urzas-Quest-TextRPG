#include "cjeannie.h"
#include "cgamemanagement.h"
#include "cjeannietalkinteraction.h"
#include "colorize.h"
#include "console.h"
#include "wonderlamp/moduleressources.h"

CJeannie::CJeannie() : CBasicDjinn(Core::EGender::eFemale)
{
    addInteraction(new CJeannieTalkInteraction(this));
}

std::string CJeannie::name() const
{
    return std::string(WonderLamp::genie());
}

std::string CJeannie::describe() const
{
    if (_sympathy > 60)
    {
        return tr("{} is a lovely, mysterious woman. She has long blond hair, her clothes look like taken directly "
                  "from the fairy tales and leave nothing to the fantasy. This magical woman is extraordiarily "
                  "beautiful, her smile is breathtakeing and her laughter enchants you everytime you hear it.",
                  name());
    }

    if (_sympathy < 40)
    {
        return tr("{} exhales magic. But she is not human, and her cloths look slutty.", name());
    }

    return tr("{} is a mysterious, pretty woman. She looks like she directly escaped a fairy tale book. She radiates "
              "magic and sex-appeal",
              name());
}

void CJeannie::load(const nlohmann::json& json)
{
    CBasicDjinn::load(json);

    for (const auto& interaction : json[TagNames::Npc::interactions])
    {
        if (CGameStateObject::compareObjectName(TagNames::WonderLamp::jeannieTalkInteraction, interaction))
        {
            auto talkInteraction = new CJeannieTalkInteraction(this);
            talkInteraction->load(interaction);
            addInteraction(talkInteraction);
        }
    }
}

std::string CJeannie::colorize(const std::string_view& s) const
{
    return WonderLamp::colorizeJeannie(s);
}
