set(URZAS_QUEST_SOURCES_MODULES ${URZAS_QUEST_SOURCES_MODULES} modules/modules.cmake)
foreach(MODULE bard shrineoftheancients cave ratfarm lakeoftears sewer leila leila2 leilarescue fishingvillage rebellionhideout blackivorytower)
    set(MODULE_CMAKE_FILE modules/${MODULE}/module.cmake)
    set(URZAS_QUEST_SOURCES_MODULES ${URZAS_QUEST_SOURCES_MODULES} ${MODULE_CMAKE_FILE})
    include(${MODULE_CMAKE_FILE})
endforeach()
set(MODULES_INCLUDE_DIRS /modules)
 
