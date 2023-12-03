cmake_minimum_required(VERSION 3.5)

project(UrzasQuest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(URZAS_QUEST_SOURCES_ROOT
	main.cpp
	ressources.h ressources.cpp
    moduleregister.h
)
set(URZAS_QUEST_SOURCES_CORE
	core/console.h core/console.cpp
    core/colorize.h core/colorize.cpp
    core/cmenu.h core/cmenu.cpp

    
    core/randomizer.h core/randomizer.cpp
    core/enumiterator.h

    core/cgamemanagement.h core/cgamemanagement.cpp
    core/cgameprogression.h core/cgameprogression.cpp
    core/cplayer.h core/cplayer.cpp
    core/cmap.h core/cmap.cpp
    core/cbattle.h core/cbattle.cpp

    core/companion/companionfactory.h core/companion/companionfactory.cpp
    core/companion/ccompanion.h core/companion/ccompanion.cpp
    core/companion/cattackercompanion.h core/companion/cattackercompanion.cpp
    core/companion/cdefendercompanion.h core/companion/cdefendercompanion.cpp
    core/companion/chealercompanion.h core/companion/chealercompanion.cpp
    core/companion/cscarymonstercompanion.h core/companion/cscarymonstercompanion.cpp

    core/rooms/roomfactory.h core/rooms/roomfactory.cpp
    core/rooms/croom.h  core/rooms/croom.cpp
    core/rooms/cfield.h core/rooms/cfield.cpp
    core/rooms/cstartingroom.h core/rooms/cstartingroom.cpp
    core/rooms/cinjuredpet.h core/rooms/cinjuredpet.cpp

    core/rooms/town/ctown.h core/rooms/town/ctown.cpp
    core/rooms/town/ctownmodule.h core/rooms/town/ctownmodule.cpp
    core/rooms/town/cshop.h core/rooms/town/cshop.cpp
    core/rooms/town/cchurch.h core/rooms/town/cchurch.cpp
    core/rooms/town/cblacksmith.h core/rooms/town/cblacksmith.cpp
    core/rooms/town/cfarm.h core/rooms/town/cfarm.cpp
    core/rooms/town/ctavern.h core/rooms/town/ctavern.cpp
    core/rooms/ccapital.h core/rooms/ccapital.cpp

    core/enemies/cenemy.h core/enemies/cenemy.cpp
    core/enemies/cmobenemy.h core/enemies/cmobenemy.cpp
    core/enemies/cbountyenemy.h core/enemies/cbountyenemy.cpp
    core/enemies/clivingchest.h core/enemies/clivingchest.cpp    
    core/enemies/ctwoenemies.h core/enemies/ctwoenemies.cpp
    core/enemies/cenemyhorde.h core/enemies/cenemyhorde.cpp

    core/tasks/ctask.h core/tasks/ctask.cpp
    core/tasks/cbountyhunt.h core/tasks/cbountyhunt.cpp

    core/cinventory.h core/cinventory.cpp
    core/items/equipment/cequipment.h core/items/equipment/cequipment.cpp
    core/items/equipment/cweapon.h core/items/equipment/cweapon.cpp
    core/items/equipment/cshield.h core/items/equipment/cshield.cpp
    core/items/equipment/carmor.h core/items/equipment/carmor.cpp

    core/items/citem.h core/items/citem.cpp
    core/items/citemfactory.h core/items/citemfactory.cpp
    core/items/chealingpotion.h core/items/chealingpotion.cpp
    core/items/cjunkitem.h core/items/cjunkitem.cpp
    core/items/cphoenixfeather.h core/items/cphoenixfeather.cpp
    core/items/cheartcontainer.h core/items/cheartcontainer.cpp    
    core/items/cbomb.h core/items/cbomb.cpp
    core/items/csandwich.h core/items/csandwich.cpp

    core/items/story/cshaggyssandwich.h core/items/story/cshaggyssandwich.cpp
    core/items/story/curzasglasses.h core/items/story/curzasglasses.cpp
    core/items/story/claylasribbon.h core/items/story/claylasribbon.cpp

    core/encounters/cencounter.h core/encounters/cencounter.cpp
    core/encounters/cbattleencounter.h core/encounters/cbattleencounter.cpp
    core/encounters/cdeadhero.h core/encounters/cdeadhero.cpp
    core/encounters/cmysteriouschest.h core/encounters/cmysteriouschest.cpp
    core/encounters/cequipmentdealer.h core/encounters/cequipmentdealer.cpp

    core/dungeons/cdungeon.h core/dungeons/cdungeon.cpp
    core/dungeons/cdungeonmap.h core/dungeons/cdungeonmap.cpp
    core/dungeons/rooms/cdungeonroom.h core/dungeons/rooms/cdungeonroom.cpp
    core/dungeons/rooms/cdungeonroomnoroom.h core/dungeons/rooms/cdungeonroomnoroom.cpp
    core/dungeons/rooms/chealingwell.h core/dungeons/rooms/chealingwell.cpp
    core/dungeons/rooms/cdungeonmaproom.h core/dungeons/rooms/cdungeonmaproom.cpp    
)

set(URZAS_QUEST_SOURCES_MODULES

    modules/shrineoftheancients/cshrineoftheancients.h modules/shrineoftheancients/cshrineoftheancients.cpp
    modules/shrineoftheancients/moduleressources.h modules/shrineoftheancients/moduleressources.cpp

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

    modules/blackivorytower/moduleressources.h modules/blackivorytower/moduleressources.cpp
    modules/blackivorytower/cblackivorytower.h modules/blackivorytower/cblackivorytower.cpp
    modules/blackivorytower/clunatic.h modules/blackivorytower/clunatic.cpp
    modules/blackivorytower/cdarkmobi.h modules/blackivorytower/cdarkmobi.cpp
    )

add_executable(UrzasQuest ${URZAS_QUEST_SOURCES_ROOT} ${URZAS_QUEST_SOURCES_CORE} ${URZAS_QUEST_SOURCES_MODULES})


target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/core)
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/core/companion)
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/core/items)
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/core/items/equipment)
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/core/items/story)
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/core/enemies)
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/core/rooms)
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/core/rooms/town)
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/core/tasks)
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/core/encounters)
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/core/dungeons)
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/core/dungeons/rooms)
target_include_directories(UrzasQuest PRIVATE ${CMAKE_SOURCE_DIR}/modules)

include(GNUInstallDirs)
install(TARGETS UrzasQuest
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

