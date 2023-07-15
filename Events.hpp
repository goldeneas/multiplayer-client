#pragma once
#include <SFML/Network.hpp>
#include <SFML/Config.hpp>

struct S2CNewClient {
	sf::Packet& p;
};

struct S2CPacketPreprocess {
	sf::Packet& p;
};

struct C2SConnection {};

struct C2SDisconnection {};

struct C2SMovement {};