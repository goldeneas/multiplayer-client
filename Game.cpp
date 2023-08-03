#include "Game.hpp"
#include "EventBus.hpp"
#include "PlayScreen.hpp"
#include "TitleScreen.hpp"
#include "NetworkWidget.hpp"
#include "ClientSync.hpp"

namespace Game {
	sf::TcpSocket socket;

	Screen::Context context;
	ScreenStack screens(context);

	UIRenderer gui;
}

void Game::start() {
	EventBus::registerListener<ClientSync>();

	screens.registerScreen<PlayScreen>(Screen::Type::PLAY);
	screens.registerScreen<TitleScreen>(Screen::Type::TITLE);
	screens.pushScreen(Screen::Type::TITLE);

	gui.add<NetworkWidget>();

	auto& textures = context.textures;
	textures.load(Texture::PLAYER, "player.png");
	textures.load(Texture::CLIENT, "client.png");
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

ResourceHolder<Texture, sf::Texture>& Game::getTextures() {
	return context.textures;
}
