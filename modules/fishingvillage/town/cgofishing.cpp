#include "cgofishing.h"
#include "colorconsole.h"
#include "console.h"
#include "fishingvillage/moduleressources.h"

CGoFishing::CGoFishing()
{
}

void CGoFishing::execute()
{
    Console::printLn("There is a long jetty with some boats. You can walk down the jetty and try fishing yourself.");
    Console::printLn("If you had a fishing rod, you could use it for fishing");
    Console::printLn(
        "If you had a boat, you could leave it here and use it whenever you want to go out on the lake and fish.");
    Console::printLn("You have neither");
}
