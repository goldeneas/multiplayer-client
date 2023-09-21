#pragma once
#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

namespace Systems {
	void move(entt::registry& entities, float dt);
	void draw(entt::registry& entities, sf::RenderWindow& window);
	void controller(entt::registry& entities);
}