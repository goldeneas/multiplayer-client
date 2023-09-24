#include "PacketProcessor.hpp"
#include <spdlog/spdlog.h>
#include "EventBus.hpp"

PacketType PacketProcessor::process(sf::Packet& packet) {
	PacketType type;
	packet >> type;

	switch(type)
	{
        case PacketType::S2C_HANDSHAKE: {
            Client::ID assignedId;
            bool isHandshakeSuccessful;

            packet >> isHandshakeSuccessful;
            packet >> assignedId;

            if(isHandshakeSuccessful)
                EventBus::emit<ClientAccepted>(assignedId);
            else
                EventBus::emit<ClientRefused>();

            break;
        }

        case PacketType::S2C_HEARTBEAT: {
            EventBus::emit<IncomingHeartbeatRequest>();
            break;
        }

        case PacketType::S2C_PLAYERJOIN: {
            Client::ID id;
            packet >> id;
            EventBus::emit<PlayerJoin>(id);
            break;
        }

        case PacketType::S2C_PLAYERLEAVE: {
            Client::ID id;
            packet >> id;
            EventBus::emit<PlayerLeave>(id);
            break;
        }

		default:
			spdlog::warn("Tried handling unregistered packet type {}!", static_cast<int>(type));
			break;
	}

	return type;
}

PacketType PacketProcessor::getType(sf::Packet packet) {
    PacketType t;
    packet >> t;
    return t;
}