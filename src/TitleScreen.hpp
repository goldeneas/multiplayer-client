#pragma once
#include "Screen.hpp"
#include "ScreenStack.hpp"

class TitleScreen : public Screen {
public:
	TitleScreen(ScreenStack& screenStack, Screen::Context& context);

	void update(float dt)				override;
	void draw(sf::RenderWindow& window) override;
	void close()						override;
};