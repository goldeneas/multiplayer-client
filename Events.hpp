#pragma once
#include <SFML/Config.hpp>
#include <SFML/Network.hpp>
#include "Client.hpp"

struct S2CNewClient {
	Client::ID id = -1;
	explicit S2CNewClient(sf::Packet& p) { p >> id; }
};

struct S2CPacketPreprocess {
	sf::Packet& p;
    explicit S2CPacketPreprocess(sf::Packet& p) : p(p) {}
};

struct C2SConnection {};

struct C2SDisconnection {};

struct C2SMovement {};