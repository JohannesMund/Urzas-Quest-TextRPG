set(URZAS_QUEST_SOURCES_CORE	
	core/core.cmake

	core/console.h core/console.cpp
    core/colorize.h core/colorize.cpp
    core/cgamestateobject.h core/cgamestateobject.cpp
    core/cmenu.h core/cmenu.cpp
    core/randomizer.h core/randomizer.cpp
    core/enumiterator.h
    core/exceptions.h
    core/cgamemanagement.h core/cgamemanagement.cpp
    core/cgameprogression.h core/cgameprogression.cpp
    core/cplayer.h core/cplayer.cpp
    core/cmap.h core/cmap.cpp
    core/cbattle.h core/cbattle.cpp

    core/save/csavefile.h core/save/csavefile.cpp
    core/save/localdirectory.h core/save/localdirectory.cpp
    core/save/exceptions.h

    core/companion/companionfactory.h core/companion/companionfactory.cpp
    core/companion/ccompanion.h core/companion/ccompanion.cpp
    core/companion/csupportcompanion.h core/companion/csupportcompanion.cpp
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

    core/tasks/taskfactory.h core/tasks/taskfactory.cpp
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

set(CORE_INCLUDE_DIRS 
    /core 
    /core/companion 
    /core/items 
    /core/items/equipment 
    /core/items/story 
    /core/enemies 
    /core/rooms 
    /core/rooms/town 
    /core/tasks 
    /core/encounters 
    /core/dungeons 
    /core/dungeons/rooms
)



