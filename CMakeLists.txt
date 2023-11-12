cmake_minimum_required(VERSION 3.5)

project(UrzasQuest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(URZAS_QUEST_SOURCES
    main.cpp

    console.h console.cpp
    colorconsole.h colorconsole.cpp
    cmenu.h cmenu.cpp

    ressources.h ressources.cpp
    randomizer.h randomizer.cpp

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

    enemies/cenemy.h enemies/cenemy.cpp
    enemies/cmobenemy.h enemies/cmobenemy.cpp
    enemies/cbountyenemy.h enemies/cbountyenemy.cpp
    enemies/clivingchest.h enemies/clivingchest.cpp

    tasks/ctask.h tasks/ctask.cpp
    tasks/cbountyhunt.h tasks/cbountyhunt.cpp

    cinventory.h cinventory.cpp
    items/equipment/cequipment.h items/equipment/cequipment.cpp
    items/equipment/csword.h items/equipment/csword.cpp
    items/equipment/cshield.h items/equipment/cshield.cpp
    items/equipment/carmor.h items/equipment/carmor.cpp
    items/equipment/cjunkshield.h items/equipment/cjunkshield.cpp
    items/equipment/cjunksword.h items/equipment/cjunksword.cpp
    items/equipment/cjunkarmor.h items/equipment/cjunkarmor.cpp

    items/citem.h items/citem.cpp
    items/itemfactory.h items/itemfactory.cpp
    items/chealingpotion.h items/chealingpotion.cpp
    items/cjunkitem.h items/cjunkitem.cpp
    items/cphoenixfeather.h items/cphoenixfeather.cpp
    items/cheartcontainer.h items/cheartcontainer.cpp    
    items/cbomb.h items/cbomb.cpp


    encounters/cencounter.h encounters/cencounter.cpp
    encounters/cbattleencounter.h encounters/cbattleencounter.cpp
    encounters/cdeadhero.h encounters/cdeadhero.cpp
    encounters/cmysteriouschest.h encounters/cmysteriouschest.cpp

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

    modules/ratfarm/moduleressources.h modules/ratfarm/moduleressources.cpp
    modules/ratfarm/cratfarmtask.h modules/ratfarm/cratfarmtask.cpp
    modules/ratfarm/cratfarmencounter.h modules/ratfarm/cratfarmencounter.cpp
    modules/ratfarm/cratfarmrat.h modules/ratfarm/cratfarmrat.cpp
    modules/ratfarm/cratfarmratboss.h modules/ratfarm/cratfarmratboss.cpp
    modules/ratfarm/cratfarmturnip.h modules/ratfarm/cratfarmturnip.cpp

    modules/forest/curzasglasses.h modules/forest/curzasglasses.cpp

    modules/bard/moduleressources.h modules/bard/moduleressources.cpp
    modules/bard/cdancingbard.h modules/bard/cdancingbard.cpp

)

add_executable(UrzasQuest ${URZAS_QUEST_SOURCES})


target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/companion)
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/items)
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/items/equipment)
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
