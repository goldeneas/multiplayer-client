#pragma once
#include <SFML/Network/Packet.hpp>

// make this shared
// also new client isn't working
enum class PacketType {
	C2S_HEARTBEAT, S2C_NEW_CLIENT
};

sf::Packet& operator>>(sf::Packet& packet, PacketType&& packetType);
sf::Packet& operator<<(sf::Packet& packet, PacketType&& packetType);
sf::Packet& operator>>(sf::Packet& packet, PacketType& packetType);
sf::Packet& operator<<(sf::Packet& packet, PacketType& packetType);