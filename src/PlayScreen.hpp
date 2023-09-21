#pragma once
#include "Screen.hpp"
#include "ScreenStack.hpp"

class PlayScreen : public Screen {
public:
	PlayScreen(ScreenStack& screenStack, Screen::Context& context);

	void update(float dt)				override;
	void draw(sf::RenderWindow& window) override;
	void close()						override;
};