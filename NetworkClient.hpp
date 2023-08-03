#pragma once
#include <string>
#include "SFML/Network.hpp"
#include "EventBus.hpp"
#include "PacketType.hpp"

namespace NetworkClient {
	void disconnect();
	void send(sf::Packet& packet);
	void connect(const std::string& address, int port);
	void poll(float dt);

	void heartbeat(float dt);
	void processIncomingPackets();

	bool isConnected();
	ClientConnection::ID getId();
	sf::Socket::Status getStatus();
}