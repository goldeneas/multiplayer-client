#include "EntityBuilder.hpp"
#include <entt.hpp>
#include "Game.hpp"
#include "Components.hpp"

void EntityBuilder::player() {
	auto& entities = Game::getEntities();
	auto& textures = Game::getTextures();

	const auto entity = entities.create();
	auto& texture = textures.get(Texture::PLAYER);

	entities.emplace<CPosition>(entity);
	entities.emplace<CVelocity>(entity);
	entities.emplace<CController>(entity);
	entities.emplace<CDraw>(entity, texture);
}

void EntityBuilder::client(ClientConnection::ID id) {
	auto& entities = Game::getEntities();
	auto& textures = Game::getTextures();

	const auto entity = entities.create();
	auto& texture = textures.get(Texture::CLIENT);

	entities.emplace<CNetworkClient>(entity, id);
	entities.emplace<CPosition>(entity);
	entities.emplace<CDraw>(entity, texture);
}