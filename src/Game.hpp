#pragma once
#include <entt/entt.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Screen.hpp"
#include "UIRenderer.hpp"
#include "ScreenStack.hpp"

namespace Game {
	void start();
	void update(float dt);
	void draw(sf::RenderWindow& window);
	void stop();

	entt::registry& getEntities();
	ResourceHolder<TextureType, sf::Texture>& getTextures();
};