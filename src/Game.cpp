#include "Game.hpp"
#include "EventBus.hpp"
#include "PlayScreen.hpp"
#include "TitleScreen.hpp"
#include "NetworkWidget.hpp"
#include "listeners/ClientSync.hpp"
#include "listeners/HandshakeListener.hpp"

namespace Game {
    Screen::Context context;
	ScreenStack screens(context);

	UIRenderer gui;
}

void Game::start() {
    EventBus::registerListener<ClientSync>();
    EventBus::registerListener<HandshakeListener>();

	screens.registerScreen<PlayScreen>(Screen::Type::PLAY);
	screens.registerScreen<TitleScreen>(Screen::Type::TITLE);
	screens.pushScreen(Screen::Type::TITLE);

	gui.add<NetworkWidget>();

	auto& textures = context.textures;
	textures.load(TextureType::PLAYER, "player.png");
	textures.load(TextureType::CLIENT, "client.png");
}

void Game::update(float dt) {
	screens.update(dt);
}

void Game::draw(sf::RenderWindow& window) {
	screens.draw(window);
	gui.draw();
}

void Game::stop() {
	screens.close();
}

entt::registry& Game::getEntities() {
	return context.entities;
}

ResourceHolder<TextureType, sf::Texture>& Game::getTextures() {
	return context.textures;
}
