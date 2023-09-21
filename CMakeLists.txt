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
        Client.hpp
        ClientSync.cpp
        ClientSync.hpp
        Components.hpp
        EntityBuilder.cpp
        EntityBuilder.hpp
        EventBus.cpp
        EventBus.hpp
        Events.hpp
        Game.cpp
        Game.hpp
        IEventListener.hpp
        IWidget.hpp
        main.cpp
        NetworkClient.cpp
        NetworkClient.hpp
        NetworkWidget.cpp
        NetworkWidget.hpp
        PacketBuilder.hpp
        PacketProcessor.cpp
        PacketProcessor.hpp
        PacketType.cpp
        PacketType.hpp
        PingListener.hpp
        PlayScreen.cpp
        PlayScreen.hpp
        ResourceHolder.hpp
        Resources.hpp
        Screen.hpp
        ScreenStack.cpp
        ScreenStack.hpp
        Systems.cpp
        Systems.hpp
        TitleScreen.cpp
        TitleScreen.hpp
        UIRenderer.cpp
        UIRenderer.hpp
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
        PacketListener.h
)

target_link_libraries(multiplayer_client
    sfml-window sfml-audio sfml-graphics sfml-network sfml-system
        ${SPDLOG_LIBRARY}
        ${FMT_LIBRARY}
        ${OPENGL_LIBRARY}
)
