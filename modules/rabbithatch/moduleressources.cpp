#include "moduleressources.h"
#include "colorize.h"
#include "rabbithatch/crabbithatch.h"
#include "randomizer.h"

#include <format>

namespace
{
template <typename... Args>
std::string tr(const std::string_view& textId, Args&&... formatArgs)
{
    return CTranslator::tr(RabbitHatch::moduleName(), TagNames::Translator::ressources, textId, formatArgs...);
}
} // namespace

Module::ModuleInfo RabbitHatch::moduleInfo()
{

    const auto roomFactory = [](const std::string_view& objectName) -> CRoom*
    {
        if (TagNames::RabbitHatch::rabbitHatch.compare(objectName) == 0)
        {
            return new CRabbitHatch();
        }
        return nullptr;
    };

    Module::ModuleInfo moduleInfo = Module::ModuleInfo();

    moduleInfo.moduleName = moduleName();
    moduleInfo.translatorFile = "rabbithatch";
    moduleInfo.gameStage = Module::EGameStage::eNone;

    moduleInfo.roomFactory = roomFactory;

    moduleInfo.initWorldMapFunction = [](std::vector<CRoom*>& rooms) { rooms.push_back(new CRabbitHatch()); };

    return moduleInfo;
}

std::string RabbitHatch::makeRabbitName()
{
    bool secondColor = (Randomizer::getRandom(3) == 1);
    bool thirdColor = (secondColor && (Randomizer::getRandom(5) == 1));
    bool pattern = (Randomizer::getRandom(3) == 1);
    bool attribute = (Randomizer::getRandom(3) == 1);

    std::vector<std::string> colors = {tr("{}light gray{}", CC::fgLightGray(), CC::ccReset()),
                                       tr("{}dark gray{}", CC::fgDarkGray(), CC::ccReset()),
                                       tr("{}black{}", CC::fgBlack(), CC::ccReset()),
                                       tr("white", CC::fgDarkGray(), CC::ccReset()),
                                       tr("{}red{}", CC::fgYellow(), CC::ccReset()),
                                       tr("{}blue{}", CC::fgLightCyan(), CC::ccReset())};

    std::vector<std::string> patterns = {tr("striped"), tr("spotted"), tr("speckled"), tr("smoked"), tr("smeared")};
    std::vector<std::string> attributes = {
        tr("{}fire{}", CC::fgRed(), CC::ccReset()),
        tr("i{}c{}e", CC::fgRed(), CC::ccReset()),
        tr("{}dragon{}", CC::fgGreen(), CC::ccReset()),
        tr("{}wolf{}", CC::fgLightGray(), CC::ccReset()),
        tr("{0}d{1}r{0}a{1}g{0}o{1}n{2}", CC::fgYellow(), CC::fgBlack(), CC::ccReset())};

    std::vector<std::string> rabbits = {tr("Rabbit"), tr("Hare"), tr("Cony"), tr("Bunny"), tr("Buck")};
    std::string s = Randomizer::getRandomStringFromVector(colors);
    s.append(" ");
    if (secondColor)
    {
        s.append(Randomizer::getRandomStringFromVector(colors));
        s.append(" ");
    }
    if (thirdColor)
    {
        s.append(Randomizer::getRandomStringFromVector(colors));
        s.append(" ");
    }
    if (pattern)
    {
        s.append(Randomizer::getRandomStringFromVector(patterns));
        s.append(" ");
    }
    if (attribute)
    {
        s.append(Randomizer::getRandomStringFromVector(attributes));
        s.append(" ");
    }
    s.append(Randomizer::getRandomStringFromVector(rabbits));

    return s;
}

std::string RabbitHatch::moduleName()
{
    return "RabbitHatch";
}

std::string RabbitHatch::katNothingH()
{
    return std::format("{}K{}a{}t {}Nothing{}H{}",
                       CC::fgGreen(),
                       CC::fgLightYellow(),
                       CC::fgYellow(),
                       CC::fgDarkGray(),
                       CC::fgWhite(),
                       CC::ccReset());
}

std::string RabbitHatch::rabbitHatchName()
{
    return std::format("{}Rabbit {}Hatch{}", CC::fgLightGray(), CC::fgYellow(), CC::ccReset());
}

std::string RabbitHatch::apple()
{
    return tr("{}A{}pple{}", CC::fgLightYellow(), CC::fgRed(), CC::ccReset());
}

std::string RabbitHatch::katsBoots()
{
    return tr("{}B{}oo{}ts{}", CC::fgGreen(), CC::fgYellow(), CC::fgLightYellow(), CC::ccReset());
}

std::string RabbitHatch::coolAndStrong()
{
    return tr("{}cool{} and {}strong{}", CC::fgCyan(), CC::ccReset(), CC::fgMagenta(), CC::ccReset());
}

std::string RabbitHatch::slasher()
{
    return tr(
        "{0}R{1}abbit {2}S{1}linging {0}S{1}lasher{3}", CC::fgRed(), CC::fgBlack(), CC::fgMagenta(), CC::ccReset());
}

int RabbitHatch::rabbitRoastPrice()
{
    return 1500;
}
