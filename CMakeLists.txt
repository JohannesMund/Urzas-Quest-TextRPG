cmake_minimum_required(VERSION 3.5)

set(TARGET_NAME UrzasQuest)

project(${TARGET_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(URZAS_QUEST_SOURCES_ROOT
  main.cpp
  ressources.h ressources.cpp
  moduleregister.h
)

include(core/core.cmake)
include(modules/modules.cmake)

add_executable(${TARGET_NAME} ${URZAS_QUEST_SOURCES_ROOT} ${URZAS_QUEST_SOURCES_CORE} ${URZAS_QUEST_SOURCES_MODULES})

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

foreach(DIR ${CORE_INCLUDE_DIRS};${MODULES_INCLUDE_DIRS})
  target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}${DIR})
endforeach()



include(GNUInstallDirs)
install(TARGETS ${TARGET_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(MSVC)
  target_compile_options(${TARGET_NAME} PRIVATE /W4)
else()
  target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
