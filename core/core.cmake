set(URZAS_QUEST_SOURCES_CORE	
	core/core.cmake
	core/ressources/core.json
    
    
    core/cgamemanagement.h core/cgamemanagement.cpp
    core/cgameprogression.h core/cgameprogression.cpp
    core/cplayer.h core/cplayer.cpp
    core/cmap.h core/cmap.cpp
    core/cbattle.h core/cbattle.cpp
    core/defaultsettings.h
    
    core/gamestate/cgamestateobject.h core/gamestate/cgamestateobject.cpp
    core/gamestate/cgamesettings.h core/gamestate/cgamesettings.cpp    
    core/gamestate/csavefile.h core/gamestate/csavefile.cpp     

    core/menu/cmenu.h core/menu/cmenu.cpp
    core/menu/cmenuaction.h core/menu/cmenuaction.cpp
    core/menu/menuaction.h

    core/utils/enumiterator.h
    core/utils/localdirectory.h core/utils/localdirectory.cpp
    core/utils/randomizer.h core/utils/randomizer.cpp
    core/utils/console.h core/utils/console.cpp
    core/utils/colorize.h core/utils/colorize.cpp    
    core/utils/clog.h core/utils/clog.cpp
    core/utils/exceptions.h 

    core/utils/json/cjsondocument.h core/utils/json/cjsondocument.cpp
    core/utils/json/jsonexceptions.h
    core/utils/json/jsontagnames.h

    core/translator/ctranslator.h core/translator/ctranslator.cpp
    core/translator/ctranslatable.h core/translator/ctranslatable.cpp
    core/translator/ctranslationfile.h core/translator/ctranslationfile.cpp
    core/translator/translatorexceptions.h
        
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

    core/items/cinventory.h core/items/cinventory.cpp
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

set(CORE_RESSOURCE_DIR
    /core/ressources/)

set(CORE_INCLUDE_DIRS 
    /core 
    /core/companion
    /core/dungeons 
    /core/dungeons/rooms
    /core/encounters
    /core/enemies 
    /core/gamestate 
    /core/items 
    /core/items/equipment 
    /core/items/story 
    /core/menu
    /core/rooms 
    /core/rooms/town 
    /core/tasks 
    /core/utils 
    /core/utils/json
    /core/translator
)



