cmake_minimum_required(VERSION 3.16)
project(yasnake LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

include_directories(src)

add_executable(yasnake 
    src/main.cpp
    src/game.cpp
    src/player.cpp
    src/statemanager.cpp
    src/states/gamestate.cpp
    src/states/matchstate.cpp
    src/states/menustate.cpp
    src/states/pausestate.cpp
    src/states/scorestate.cpp
)
target_link_libraries(yasnake PRIVATE sfml-graphics)
target_compile_features(yasnake PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET yasnake
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:yasnake>
        VERBATIM)
endif()

install(TARGETS yasnake)
