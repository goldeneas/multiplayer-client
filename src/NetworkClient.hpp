#pragma once
#include <string>
#include "SFML/Network.hpp"
#include "EventBus.hpp"
#include "PacketType.hpp"
#include "PacketWrappers.hpp"

enum class HandshakeStatus {
    IDLE,
    WAITING,
    ACCEPTED,
    REFUSED
};

namespace NetworkClient {
	void poll();
    void reset();
	void send(PacketWrapper& p, sf::IpAddress address, int port);

	void shutdown();
	void processIncomingPackets();
	void handshake(const std::string& address, int port);

	bool isSetup();

    HandshakeStatus getHandshakeStatus();
    void setHandshakeStatus(HandshakeStatus s);

    void setId(Client::ID assignedId);
	Client::ID getId();
}