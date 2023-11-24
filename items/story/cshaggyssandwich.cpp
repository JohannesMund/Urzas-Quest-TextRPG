#include "cshaggyssandwich.h"
#include "colorize.h"

#include <format>

CShaggysSandwich::CShaggysSandwich() :
    CSandwich({CSandwich::EIngredients::eSalami,      CSandwich::EIngredients::eSalami,
               CSandwich::EIngredients::eMortardella, CSandwich::EIngredients::eSalami,
               CSandwich::EIngredients::eBacon,       CSandwich::EIngredients::eBacon,
               CSandwich::EIngredients::eCheddar,     CSandwich::EIngredients::eGouda,
               CSandwich::EIngredients::eMozzarella,  CSandwich::EIngredients::eUnknown,
               CSandwich::EIngredients::eMortardella, CSandwich::EIngredients::eMortardella,
               CSandwich::EIngredients::ePeperoni,    CSandwich::EIngredients::ePeperoni,
               CSandwich::EIngredients::eCheddar,     CSandwich::EIngredients::eCheddar,
               CSandwich::EIngredients::eSalami,      CSandwich::EIngredients::eSalami,
               CSandwich::EIngredients::eMortardella, CSandwich::EIngredients::eSalami,
               CSandwich::EIngredients::eBacon,       CSandwich::EIngredients::eBacon,
               CSandwich::EIngredients::eCheddar,     CSandwich::EIngredients::eGouda,
               CSandwich::EIngredients::eMozzarella,  CSandwich::EIngredients::eMortardella,
               CSandwich::EIngredients::eMortardella, CSandwich::EIngredients::eMortardella,
               CSandwich::EIngredients::ePeperoni,    CSandwich::EIngredients::ePeperoni,
               CSandwich::EIngredients::eCheddar,     CSandwich::EIngredients::eCheddar,
               CSandwich::EIngredients::eBacon,       CSandwich::EIngredients::eOlives})
{
    _name = std::format("{0}Sha{1}key {2}Sha{1}ggy{0}'s Sa{1}ndw{2}ich{3}",
                        CC::fgYellow(),
                        CC::fgLightGreen(),
                        CC::fgWhite(),
                        CC::ccReset());
}

CItem::ItemFilter CShaggysSandwich::shaggysSandwichFilter()
{
    return [](const CItem* item) { return dynamic_cast<const CShaggysSandwich*>(item) != nullptr; };
}
