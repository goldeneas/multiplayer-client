#include "PlayScreen.hpp"
#include "Systems.hpp"
#include "EntityBuilder.hpp"

PlayScreen::PlayScreen(ScreenStack& screenStack, Screen::Context& context)
	: Screen(screenStack, context) {

	auto& textures = getContext().textures;
	auto& entities = getContext().entities;

	textures.load(Texture::Player, "player.png");

	EntityBuilder::player(entities, textures.get(Texture::Player));
}

void PlayScreen::update(float dt) {
	auto& entities = getContext().entities;

	Systems::controller(entities);
	Systems::move(entities, dt);
}

void PlayScreen::draw(sf::RenderWindow& window) {
	auto& entities = getContext().entities;

	Systems::draw(entities, window);
}

void PlayScreen::close() {

}
