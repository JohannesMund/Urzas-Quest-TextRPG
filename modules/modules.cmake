set(URZAS_QUEST_SOURCES_MODULES ${URZAS_QUEST_SOURCES_MODULES} modules/modules.cmake)
set(MODULES_INCLUDE_DIRS /modules)

set(MODULE_LIST 
    bard 
    blackivorytower 
    cave 
    fishingvillage 
    lakeoftears 
    leila 
    leila2 
    leilarescue 
    ratfarm 
    rebellionhideout 
    sewer 
    shrineoftheancients
)

foreach(MODULE ${MODULE_LIST})
    set(MODULE_CMAKE_FILE modules/${MODULE}/module.cmake)
    set(URZAS_QUEST_SOURCES_MODULES ${URZAS_QUEST_SOURCES_MODULES} ${MODULE_CMAKE_FILE})
    set(URZAS_QUEST_MODULE_RESSOURCES ${URZAS_QUEST_MODULE_RESSOURCES} ${MODULE})
    include(${MODULE_CMAKE_FILE})
endforeach()
