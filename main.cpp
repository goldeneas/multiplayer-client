#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>
#include "Game.hpp"
#include "NetworkClient.hpp"

// TODO heartbeat with server on client check too
int main() {
    spdlog::set_level(spdlog::level::debug);

    sf::RenderWindow window(sf::VideoMode(1366, 768), "Multiplayer Zelda");
    ImGui::SFML::Init(window);

    // start
    Game::start();
    
    // loop
    sf::Clock deltaClock;
    while (window.isOpen()) {
        // get events
        sf::Event event{};
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time dt = deltaClock.restart();

        // update
        ImGui::SFML::Update(window, dt);
        NetworkClient::poll(dt.asSeconds());
        Game::update(dt.asSeconds());

        // draw
        window.clear();
        Game::draw(window);
        ImGui::SFML::Render(window);
        window.display();
    }

    // shutdown
    window.close();
    ImGui::SFML::Shutdown();
    return 0;
}