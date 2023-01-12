cmake_minimum_required(VERSION 3.14)
project(PlatformerSFML)

set(CMAKE_CXX_STANDARD 14)

if(WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()


find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
set(SOURCE_FILES src/main.cpp src/Game.cpp src/Game.h src/GameStates/MainMenu.cpp src/GameStates/MainMenu.h src/GameStates/GameState.h src/GameStates/GamePlay.cpp src/GameStates/GamePlay.h src/GameObjects/Player.cpp src/GameObjects/Platform.cpp src/GameObjects/Laser.cpp src/GameObjects/Laser.h src/GameObjects/Coin.cpp src/GameObjects/Coin.h src/GameStates/GameOverMenu.cpp src/GameStates/GameOverMenu.h src/GameStates/GameWon.cpp src/GameStates/GameWon.h src/GameObjects/Score.cpp src/GameObjects/Score.h src/GameObjects/AnimationState.h src/GameObjects/Enemy.cpp src/GameObjects/Enemy.h src/GameObjects/Life.cpp src/GameObjects/Life.h src/GameStates/OptionMenu.cpp src/GameStates/OptionMenu.h)
add_executable(PlatformerSFML ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

target_link_libraries (PlatformerSFML sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)