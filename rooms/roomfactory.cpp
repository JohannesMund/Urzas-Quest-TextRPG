#include "roomfactory.h"
#include "cave/ccave.h"
#include "cfield.h"
#include "cinjuredpet.h"
#include "croom.h"
#include "cshrineoftheancients.h"
#include "ctown.h"

CRoom* RoomFactory::makeRoom()
{
    return new CField();
}

CTown* RoomFactory::makeTown()
{
    return new CTown();
}

CInjuredPet* RoomFactory::makeInjuredPet()
{
    return new CInjuredPet();
}

CShrineOfTheAncients* RoomFactory::makeShrine()
{
    return new CShrineOfTheAncients();
}
