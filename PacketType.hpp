#pragma once
#include <SFML/Network/Packet.hpp>

// TODO: make this shared
enum class PacketType {
	C2S_HEARTBEAT, S2C_NEW_CLIENT, C2S_MOVE_REQUEST, S2C_MOVE_RESULT, C2S_WHOAMI
};

sf::Packet& operator>>(sf::Packet& packet, PacketType&& packetType);
sf::Packet& operator<<(sf::Packet& packet, PacketType&& packetType);
sf::Packet& operator>>(sf::Packet& packet, PacketType& packetType);
sf::Packet& operator<<(sf::Packet& packet, PacketType& packetType);