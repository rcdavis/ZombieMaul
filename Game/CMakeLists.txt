project(Game)

add_executable(Game
    src/Entity/Entity.cpp
    src/Entity/EntityManager.cpp
    src/Entity/Guard.cpp
    src/Entity/Person.cpp
    src/Entity/Player.cpp
    src/Input/Input.cpp
    src/Messaging/EventManager.cpp
    src/Renderer/Animation.cpp
    src/Renderer/AnimationManager.cpp
    src/Renderer/AnimationPlayer.cpp
    src/Renderer/FontManager.cpp
    src/Renderer/TextureManager.cpp
    src/States/CreditsMenuState.cpp
    src/States/GameOverState.cpp
    src/States/GameplayState.cpp
    src/States/MainMenuState.cpp
    src/States/OptionsMenuState.cpp
    src/States/PauseMenuState.cpp
    src/States/StateManager.cpp
    src/Utils/Debug.cpp
    src/Utils/Json.cpp
    src/Utils/Math.cpp
    src/Utils/Log.cpp
    src/Game.cpp
    src/IntervalTrigger.cpp
    src/Level.cpp
    src/Main.cpp
    src/RNG.cpp
    src/Settings.cpp
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res
     DESTINATION ${CMAKE_BINARY_DIR}/Game)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(Game PUBLIC
        DEBUG
        LOGGING_ENABLED
    )
else()
    target_compile_definitions(Game PUBLIC
        NDEBUG
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
