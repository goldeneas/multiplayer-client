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
	void send(PacketWrapper& p);

	void shutdown();
	void handshake(const std::string& address, int port);

	bool isSetup();
	Client::ID getId();
    void setId(Client::ID assignedId);
    HandshakeStatus getHandshakeStatus();
    void setHandshakeStatus(HandshakeStatus s);
}