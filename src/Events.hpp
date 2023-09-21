#pragma once
#include <SFML/Config.hpp>
#include <SFML/Network.hpp>
#include "Client.hpp"

struct ClientAccepted {
    Client::ID id;
    explicit ClientAccepted(Client::ID id) : id(id) {};
};

struct ClientRefused {

};

struct PlayerJoin {
    Client::ID id;
    explicit PlayerJoin(Client::ID id) : id(id) {};
};

struct PlayerLeave {
    Client::ID id;
    explicit PlayerLeave(Client::ID id) : id(id) {};
};

struct OutgoingPacketPreprocess {
    sf::Packet& p;

    explicit OutgoingPacketPreprocess(sf::Packet& p) : p(p) {};
};