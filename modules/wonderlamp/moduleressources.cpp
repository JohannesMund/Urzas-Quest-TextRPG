#include "moduleressources.h"
#include "cfindwonderlamp.h"
#include "cgamemanagement.h"
#include "colorize.h"
#include "ctranslator.h"
#include "items/cgem.h"
#include "items/cwonderlamp.h"
#include "randomizer.h"

#include <string>

namespace
{
template <typename... Args>
std::string tr(const std::string_view& textId, Args&&... formatArgs)
{
    return CTranslator::tr(WonderLamp::moduleName(), TagNames::Translator::ressources, textId, formatArgs...);
}
} // namespace

Module::ModuleInfo WonderLamp::moduleInfo()
{
    const auto itemFactory = [](const std::string_view& objectName) -> CItem*
    {
        if (TagNames::WonderLamp::wonderlamp.compare(objectName) == 0)
        {
            return new CWonderLamp();
        }
        if (TagNames::WonderLamp::gem.compare(objectName) == 0)
        {
            return new CGem();
        }

        return nullptr;
    };

    Module::ModuleInfo moduleInfo = Module::ModuleInfo();

    moduleInfo.moduleName = moduleName();
    moduleInfo.translatorFile = "wonderlamp";
    moduleInfo.gameStage = Module::EGameStage::eNone;

    moduleInfo.initFunction = []() { CGameManagement::getInstance()->registerEncounter(new CFindWonderLamp()); };
    moduleInfo.itemFactory = itemFactory;

    return moduleInfo;
}
std::string WonderLamp::moduleName()
{
    return std::string(TagNames::WonderLamp::wonderlamp);
}

std::string WonderLamp::colorizeJeannie(const std::string_view& s)
{
    return CC::colorizeString(s, CC::fgMagenta(), CC::fgLightMagenta());
}

std::string WonderLamp::jeannie()
{
    return std::format("{} {}", colorizeJeannie(tr("Bewitching")), colorizeJeannie(tr("Jeanny")));
}
std::string WonderLamp::colorizeGenie(const std::string_view& s)
{
    return CC::colorizeString(s, CC::fgMagenta(), CC::fgLightMagenta());
}
std::string WonderLamp::genie()
{
    return std::format("{} {}", colorizeGenie(tr("Charming")), colorizeGenie(tr("Genie")));
}
std::string WonderLamp::wonderlamp()
{
    return tr("{0}Wo{1}nd{0}er{1}la{0}mp{2}", CC::fgYellow(), CC::fgLightYellow(), CC::ccReset());
}

std::string WonderLamp::wonderLampEncounter()
{
    return tr("A pile of rubbish in a dark allay");
}

std::string WonderLamp::getRandomGem()
{
    return Randomizer::getRandomStringFromVector({
        tr("{}Ruby{}", CC::fgRed(), CC::ccReset()),
        tr("{}Saphire{}", CC::fgBlue(), CC::ccReset()),
        tr("{}Emerald{}", CC::fgGreen(), CC::ccReset()),
        tr("{}Diamond{}", CC::fgWhite(), CC::ccReset()),
        tr("{}Topaz{}", CC::fgYellow(), CC::ccReset()),
        tr("{}Amethyst{}", CC::fgLightBlue(), CC::ccReset()),
    });
}

std::string WonderLamp::djinn()
{
    return tr("{}Dj{}inn{}", CC::fgLightBlue(), CC::fgLightMagenta(), CC::ccReset());
}