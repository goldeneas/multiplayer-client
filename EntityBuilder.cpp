#include "EntityBuilder.hpp"
#include "Components.hpp"

void EntityBuilder::player(entt::registry& entities, sf::Texture& texture) {
	const auto entity = entities.create();

	entities.emplace<CPosition>(entity);
	entities.emplace<CVelocity>(entity);
	entities.emplace<CController>(entity);
	entities.emplace<CDraw>(entity, texture);
}

void EntityBuilder::client(entt::registry& entities, sf::Uint32 id, sf::Texture& texture) {
	const auto entity = entities.create();

	entities.emplace<CNetworkClient>(entity, id);
	entities.emplace<CPosition>(entity);
	entities.emplace<CDraw>(entity, texture);
}