#include "PlayScreen.hpp"
#include "Systems.hpp"
#include "EntityBuilder.hpp"

PlayScreen::PlayScreen(ScreenStack& screenStack, Screen::Context& context)
	: Screen(screenStack, context) {

	EntityBuilder::player();
}

void PlayScreen::update(float dt) {
	auto& entities = context.entities;

	Systems::controller(entities);
	Systems::move(entities, dt);
}

void PlayScreen::draw(sf::RenderWindow& window) {
	auto& entities = context.entities;

	Systems::draw(entities, window);
}

void PlayScreen::close() {

}
