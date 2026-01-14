project(Game)

include(FetchContent)

FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
)
FetchContent_MakeAvailable(sfml)

set(SPDLOG_HEADER_ONLY ON CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_EXAMPLE OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_BENCH OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.16.0
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
  simdjson
  GIT_REPOSITORY https://github.com/simdjson/simdjson.git
  GIT_TAG v4.2.4
)
FetchContent_MakeAvailable(simdjson)

add_executable(Game
    src/Input/Input.cpp
    src/Renderer/FontManager.cpp
    src/Renderer/TextureManager.cpp
    src/States/CreditsMenuState.cpp
    src/States/GameplayState.cpp
    src/States/MainMenuState.cpp
    src/States/OptionsMenuState.cpp
    src/States/StateManager.cpp
    src/Utils/Log.cpp
    src/Game.cpp
    src/Level.cpp
    src/Main.cpp
    src/Settings.cpp
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res
     DESTINATION ${CMAKE_BINARY_DIR}/Game)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(Game PUBLIC
        DEBUG
        LOGGING_ENABLED
    )
endif()

target_include_directories(Game PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(Threads REQUIRED)

target_link_libraries(Game
    SFML::System
    SFML::Window
    SFML::Graphics
    Threads::Threads
    spdlog::spdlog_header_only
    simdjson
)
