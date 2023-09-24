#pragma once
#include <SFML/Config.hpp>
#include <SFML/Network.hpp>
#include "Client.hpp"

struct ClientAccepted {
    Client::ID assignedId;
    explicit ClientAccepted(Client::ID assignedId) : assignedId(assignedId) {};
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

struct IncomingHeartbeatRequest {};

struct IncomingPacketPreprocess {
    sf::Packet& p;

    explicit IncomingPacketPreprocess(sf::Packet& p) : p(p) {};
};