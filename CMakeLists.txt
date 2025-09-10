include(core/core.cmake)
include(modules/modules.cmake)
include(FetchContent)
include(GNUInstallDirs)

cmake_minimum_required(VERSION 3.11)
cmake_policy(SET CMP0135 NEW)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(TARGET_NAME UrzasQuest)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

project(${TARGET_NAME} LANGUAGES CXX)

set(URZAS_QUEST_SOURCES_ROOT
  main.cpp  
  ressources.h ressources.cpp
  moduleregister.h
  globals.h
)

add_executable(${TARGET_NAME} ${URZAS_QUEST_SOURCES_ROOT} ${URZAS_QUEST_SOURCES_CORE} ${URZAS_QUEST_SOURCES_MODULES})

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

foreach(DIR ${CORE_INCLUDE_DIRS};${MODULES_INCLUDE_DIRS})
  target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}${DIR})
endforeach()


install(TARGETS ${TARGET_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_link_libraries(${TARGET_NAME} PRIVATE nlohmann_json::nlohmann_json)

if(MSVC)
  target_compile_options(${TARGET_NAME} PRIVATE /W4)
else()
  target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
