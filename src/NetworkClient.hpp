#pragma once
#include <string>
#include "SFML/Network.hpp"
#include "EventBus.hpp"
#include "PacketType.hpp"
#include "PacketWrappers.h"

namespace NetworkClient {
	void poll();
	void send(PacketWrapper& p, sf::IpAddress address, int port);

	void shutdown();
	void processIncomingPackets();
	void handshake(const std::string& address, int port);

	bool isReady();
    bool isHandshakeDone();
	Client::ID getId();
	sf::Socket::Status getStatus();
}