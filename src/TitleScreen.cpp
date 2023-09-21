#include "TitleScreen.hpp"
#include "imgui.h"
#include "NetworkClient.hpp"
#include "spdlog/spdlog.h"

TitleScreen::TitleScreen(ScreenStack& screenStack, Screen::Context& context)
	: Screen(screenStack, context) {

}

void TitleScreen::update(float dt) {
	if(NetworkClient::isHandshakeDone())
		screenStack.switchLastScreenTo(Screen::Type::PLAY);
}

void TitleScreen::draw(sf::RenderWindow& window) {
	sf::Vector2u windowSize = window.getSize();
	ImGui::SetNextWindowPos(ImVec2(windowSize.x * 0.5f, windowSize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 1.0f));

	ImGui::Begin("##TitleScreenMenu", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration);

	if(ImGui::Button("Play", ImVec2(200, 30))) {
		NetworkClient::handshake("localhost", 39964);
	}

	ImGui::Spacing();
	
	if(ImGui::Button("Exit", ImVec2(200, 30)))
		std::exit(0);

	ImGui::End();
}

void TitleScreen::close() {

}