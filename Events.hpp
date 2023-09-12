#pragma once
#include <SFML/Config.hpp>
#include <SFML/Network.hpp>
#include "ClientConnection.hpp"

struct S2CNewClient {
	ClientConnection::ID id = -1;
	S2CNewClient(sf::Packet& p) { p >> id; }
};

struct S2CPacketPreprocess {
	sf::Packet& p;
};

struct C2SConnection {};

struct C2SDisconnection {};

struct C2SMovement {};