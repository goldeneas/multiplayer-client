#pragma once
#include <entt.hpp>
#include <SFML/Graphics.hpp>

namespace EntityBuilder {
	void player(entt::registry& entities, sf::Texture& texture);
	void client(entt::registry& entities, sf::Uint32 id, sf::Texture& texture);
}