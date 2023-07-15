#include "PacketProcessor.hpp"
#include <spdlog/spdlog.h>
#include "EventBus.hpp"

PacketType PacketProcessor::process(sf::Packet& packet) {
	PacketType type;
	packet >> type;

	switch(type)
	{
		case PacketType::S2C_NEW_CLIENT:
			EventBus::emit<S2CNewClient>(packet);
			break;

		default:
			spdlog::warn("Tried handling unregistered packet type {}!", static_cast<int>(type));
			break;
	}

	return type;
}