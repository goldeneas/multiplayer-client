cmake_minimum_required(VERSION 3.26)
project(multiplayer_client)

set(CMAKE_CXX_STANDARD 20)

set(IMGUI_DIR /opt/nicola/imgui-1.89.9)
set(IMGUI_ADDITIONAL_DIR /opt/nicola/imgui-additional)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

find_library(OPENGL_LIBRARY OpenGl)
find_library(FMT_LIBRARY fmt)
find_library(SPDLOG_LIBRARY spdlog)
find_library(SFML_LIBRARY sfml)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        /opt/homebrew/Cellar/sfml/2.6.0/include
        /opt/homebrew/Cellar/spdlog/1.12.0/include
        /opt/homebrew/Cellar/entt/3.12.2/include
        /opt/homebrew/Cellar/fmt/10.1.1/include
        /opt/nicola/imgui-1.89.9/
        /opt/nicola/imgui-additional/
)

link_directories(
        /opt/homebrew/Cellar/sfml/2.6.0/lib
        /opt/homebrew/Cellar/spdlog/1.12.0/lib
        /opt/homebrew/Cellar/fmt/10.1.1/lib
)

add_executable(multiplayer_client
        src/Client.hpp
        src/listeners/ClientSync.cpp
        src/listeners/ClientSync.hpp
        src/Components.hpp
        src/EntityBuilder.cpp
        src/EntityBuilder.hpp
        src/EventBus.cpp
        src/EventBus.hpp
        src/Events.hpp
        src/Game.cpp
        src/Game.hpp
        src/IEventListener.hpp
        src/IWidget.hpp
        src/main.cpp
        src/NetworkClient.cpp
        src/NetworkClient.hpp
        src/NetworkWidget.cpp
        src/NetworkWidget.hpp
        src/PacketProcessor.cpp
        src/PacketProcessor.hpp
        src/PacketType.cpp
        src/PacketType.hpp
        src/PlayScreen.cpp
        src/PlayScreen.hpp
        src/ResourceHolder.hpp
        src/Resources.hpp
        src/Screen.hpp
        src/ScreenStack.cpp
        src/ScreenStack.hpp
        src/Systems.cpp
        src/Systems.hpp
        src/TitleScreen.cpp
        src/TitleScreen.hpp
        src/UIRenderer.cpp
        src/UIRenderer.hpp
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui.h
        ${IMGUI_DIR}/imconfig.h
        ${IMGUI_ADDITIONAL_DIR}/imgui-SFML.cpp
        ${IMGUI_ADDITIONAL_DIR}/imgui-SFML.h
        ${IMGUI_ADDITIONAL_DIR}/imgui_stdlib.h
        ${IMGUI_ADDITIONAL_DIR}/imgui_stdlib.cpp
        src/PacketWrappers.hpp
        src/PacketWrappers.hpp
        src/PacketWrappers.hpp
        src/listeners/HandshakeListener.cpp
        src/listeners/HandshakeListener.hpp
)

target_link_libraries(multiplayer_client
    sfml-window sfml-audio sfml-graphics sfml-network sfml-system
        ${SPDLOG_LIBRARY}
        ${FMT_LIBRARY}
        ${OPENGL_LIBRARY}
)
