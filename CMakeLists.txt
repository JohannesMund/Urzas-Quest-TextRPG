cmake_minimum_required(VERSION 3.5)

project(UrzasQuest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(URZAS_QUEST_SOURCES
    main.cpp

    console.h console.cpp
    colorize.h colorize.cpp
    cmenu.h cmenu.cpp

    ressources.h ressources.cpp
    randomizer.h randomizer.cpp
    enumiterator.h

    cgamemanagement.h cgamemanagement.cpp
    cgameprogression.h cgameprogression.cpp
    cplayer.h cplayer.cpp
    cmap.h cmap.cpp
    cbattle.h cbattle.cpp

    companion/companionfactory.h companion/companionfactory.cpp
    companion/ccompanion.h companion/ccompanion.cpp
    companion/cattackercompanion.h companion/cattackercompanion.cpp
    companion/cdefendercompanion.h companion/cdefendercompanion.cpp
    companion/chealercompanion.h companion/chealercompanion.cpp
    companion/cscarymonstercompanion.h companion/cscarymonstercompanion.cpp

    rooms/roomfactory.h rooms/roomfactory.cpp
    rooms/croom.h  rooms/croom.cpp
    rooms/cfield.h rooms/cfield.cpp
    rooms/cstartingroom.h rooms/cstartingroom.cpp
    rooms/cinjuredpet.h rooms/cinjuredpet.cpp
    rooms/cshrineoftheancients.h rooms/cshrineoftheancients.cpp

    rooms/town/ctown.h rooms/town/ctown.cpp
    rooms/town/ctownmodule.h rooms/town/ctownmodule.cpp
    rooms/town/cshop.h rooms/town/cshop.cpp
    rooms/town/cchurch.h rooms/town/cchurch.cpp
    rooms/town/cblacksmith.h rooms/town/cblacksmith.cpp
    rooms/town/cfarm.h rooms/town/cfarm.cpp
    rooms/town/ctavern.h rooms/town/ctavern.cpp
    rooms/ccapital.h rooms/ccapital.cpp

    enemies/cenemy.h enemies/cenemy.cpp
    enemies/cmobenemy.h enemies/cmobenemy.cpp
    enemies/cbountyenemy.h enemies/cbountyenemy.cpp
    enemies/clivingchest.h enemies/clivingchest.cpp    
    enemies/ctwoenemies.h enemies/ctwoenemies.cpp
    enemies/cenemyhorde.h enemies/cenemyhorde.cpp

    tasks/ctask.h tasks/ctask.cpp
    tasks/cbountyhunt.h tasks/cbountyhunt.cpp

    cinventory.h cinventory.cpp
    items/equipment/cequipment.h items/equipment/cequipment.cpp
    items/equipment/cweapon.h items/equipment/cweapon.cpp
    items/equipment/cshield.h items/equipment/cshield.cpp
    items/equipment/carmor.h items/equipment/carmor.cpp

    items/citem.h items/citem.cpp
    items/citemfactory.h items/citemfactory.cpp
    items/chealingpotion.h items/chealingpotion.cpp
    items/cjunkitem.h items/cjunkitem.cpp
    items/cphoenixfeather.h items/cphoenixfeather.cpp
    items/cheartcontainer.h items/cheartcontainer.cpp    
    items/cbomb.h items/cbomb.cpp
    items/csandwich.h items/csandwich.cpp

    items/story/cshaggyssandwich.h items/story/cshaggyssandwich.cpp
    items/story/curzasglasses.h items/story/curzasglasses.cpp
    items/story/claylasribbon.h items/story/claylasribbon.cpp

    encounters/cencounter.h encounters/cencounter.cpp
    encounters/cbattleencounter.h encounters/cbattleencounter.cpp
    encounters/cdeadhero.h encounters/cdeadhero.cpp
    encounters/cmysteriouschest.h encounters/cmysteriouschest.cpp
    encounters/cequipmentdealer.h encounters/cequipmentdealer.cpp

    dungeons/cdungeon.h dungeons/cdungeon.cpp
    dungeons/cdungeonmap.h dungeons/cdungeonmap.cpp
    dungeons/rooms/cdungeonroom.h dungeons/rooms/cdungeonroom.cpp
    dungeons/rooms/cdungeonroomnoroom.h dungeons/rooms/cdungeonroomnoroom.cpp
    dungeons/rooms/chealingwell.h dungeons/rooms/chealingwell.cpp
    dungeons/rooms/cdungeonmaproom.h dungeons/rooms/cdungeonmaproom.cpp

    modules/cave/moduleressources.h modules/cave/moduleressources.cpp
    modules/cave/ccavedungeon.h modules/cave/ccavedungeon.cpp
    modules/cave/ccave.h modules/cave/ccave.cpp
    modules/cave/ccavedungeonmap.h modules/cave/ccavedungeonmap.cpp
    modules/cave/ccavebosstask.h modules/cave/ccavebosstask.cpp    
    modules/cave/ccavebattleencounter.h modules/cave/ccavebattleencounter.cpp
    modules/cave/ccaveboss.h modules/cave/ccaveboss.cpp
    modules/cave/copencavetask.h modules/cave/copencavetask.cpp
    modules/cave/copencaveencounter.h modules/cave/copencaveencounter.cpp

    modules/ratfarm/moduleressources.h modules/ratfarm/moduleressources.cpp
    modules/ratfarm/cratfarmtask.h modules/ratfarm/cratfarmtask.cpp
    modules/ratfarm/cratfarmencounter.h modules/ratfarm/cratfarmencounter.cpp
    modules/ratfarm/cratfarmrat.h modules/ratfarm/cratfarmrat.cpp
    modules/ratfarm/cratfarmratboss.h modules/ratfarm/cratfarmratboss.cpp
    modules/ratfarm/cratfarmturnip.h modules/ratfarm/cratfarmturnip.cpp

    modules/bard/moduleressources.h modules/bard/moduleressources.cpp
    modules/bard/cdancingbard.h modules/bard/cdancingbard.cpp

    modules/lakeoftears/moduleressources.h modules/lakeoftears/moduleressources.cpp
    modules/lakeoftears/clakeoftearstask.h modules/lakeoftears/clakeoftearstask.cpp
    modules/lakeoftears/clakeoftearsbosstask.h modules/lakeoftears/clakeoftearsbosstask.cpp
    modules/lakeoftears/clakeoftearsencounter.h modules/lakeoftears/clakeoftearsencounter.cpp
    modules/lakeoftears/clakeoftearsboss.h modules/lakeoftears/clakeoftearsboss.cpp

    modules/sewer/moduleressources.h modules/sewer/moduleressources.cpp
    modules/sewer/csewerencounter.h modules/sewer/csewerencounter.cpp
    modules/sewer/csewertask.h modules/sewer/csewertask.cpp
    modules/sewer/csewerdungeonmap.h modules/sewer/csewerdungeonmap.cpp
    modules/sewer/csewerdungeon.h modules/sewer/csewerdungeon.cpp
    modules/sewer/csewerbattleencounter.h modules/sewer/csewerbattleencounter.cpp
    modules/sewer/csewerbossroom.h modules/sewer/csewerbossroom.cpp
    modules/sewer/csewerboss.h modules/sewer/csewerboss.cpp

    modules/layla/claylaencounter.h modules/layla/claylaencounter.cpp
    modules/layla/moduleressources.h modules/layla/moduleressources.cpp
    modules/layla/claylatask.h modules/layla/claylatask.cpp
    modules/layla/claylaboss.h modules/layla/claylaboss.cpp
    modules/layla/claylatowntask.h modules/layla/claylatowntask.cpp

    modules/fishingvillage/cfishingvillage.h modules/fishingvillage/cfishingvillage.cpp
    modules/fishingvillage/moduleressources.h modules/fishingvillage/moduleressources.cpp
    modules/fishingvillage/town/cfishrestaurant.h modules/fishingvillage/town/cfishrestaurant.cpp
    modules/fishingvillage/town/cfishingfritz.h modules/fishingvillage/town/cfishingfritz.cpp
    modules/fishingvillage/town/cgofishing.h modules/fishingvillage/town/cgofishing.cpp
    modules/fishingvillage/items/cfish.h modules/fishingvillage/items/cfish.cpp
    modules/fishingvillage/items/cfishingrodpart.h modules/fishingvillage/items/cfishingrodpart.cpp
    modules/fishingvillage/items/cfishingrod.h modules/fishingvillage/items/cfishingrod.cpp
    modules/fishingvillage/items/cboat.h modules/fishingvillage/items/cboat.cpp
    modules/fishingvillage/items/cboatpart.h modules/fishingvillage/items/cboatpart.cpp
    modules/fishingvillage/tasks/cbuildequipmenttask.h modules/fishingvillage/tasks/cbuildequipmenttask.cpp
    modules/fishingvillage/tasks/cfishingvilletowntask.h modules/fishingvillage/tasks/cfishingvilletowntask.cpp

    modules/rebellionhideout/csandwichshop.h modules/rebellionhideout/csandwichshop.cpp
    modules/rebellionhideout/moduleressources.h modules/rebellionhideout/moduleressources.cpp
    modules/rebellionhideout/cbagofingredients.h modules/rebellionhideout/cbagofingredients.cpp

    modules/layla2/enemies/claylabossguards.h modules/layla2/enemies/claylabossguards.cpp
    modules/layla2/moduleressources.h modules/layla2/moduleressources.cpp
    modules/layla2/enemies/claylabossorks.h modules/layla2/enemies/claylabossorks.cpp
    modules/layla2/encounters/clayla2encounter.h modules/layla2/encounters/clayla2encounter.cpp
    modules/layla2/encounters/clayla2goblinencounter.h modules/layla2/encounters/clayla2goblinencounter.cpp
    modules/layla2/tasks/clayla2goblinvillagetask.h modules/layla2/tasks/clayla2goblinvillagetask.cpp
    modules/layla2/enemies/cgoblinhorde.h modules/layla2/enemies/cgoblinhorde.cpp
    modules/layla2/tasks/clayla2capitaltask.h modules/layla2/tasks/clayla2capitaltask.cpp
)

add_executable(UrzasQuest ${URZAS_QUEST_SOURCES})


target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/companion)
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/items)
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/items/equipment)
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/items/story)
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/enemies)
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/rooms)
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/rooms/town)
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/tasks)
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/encounters)
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/dungeons)
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/dungeons/rooms)
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/modules)

include(GNUInstallDirs)
install(TARGETS UrzasQuest
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

