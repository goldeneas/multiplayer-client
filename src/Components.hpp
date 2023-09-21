#pragma once
#include <SFML/Graphics/Sprite.hpp>

struct CNetworkClient {
	CNetworkClient(sf::Uint32 id) : id(id) {};

	sf::Uint32 id;
};

struct CPosition {
	float x;
	float y;
};

struct CVelocity {
	float speed = 400;
	float verticalAxis;			// between -1 and 1
	float horizontalAxis;		// between -1 and 1
};

struct CDraw {
	CDraw(sf::Texture& texture) { sprite.setTexture(texture); }

	sf::Sprite sprite;
};

struct CController {
	bool up;
	bool left;
	bool down;
	bool right;
};