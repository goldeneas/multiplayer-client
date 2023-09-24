#pragma once
#include <SFML/Network/Packet.hpp>

// TODO: make this shared
enum class PacketType {
    UNDEFINED, C2S_HANDSHAKE, S2C_HANDSHAKE, S2C_PLAYERJOIN, S2C_PLAYERLEAVE,
    S2C_HEARTBEAT, C2S_HEARTBEAT
};

sf::Packet& operator>>(sf::Packet& packet, PacketType&& packetType);
sf::Packet& operator<<(sf::Packet& packet, PacketType&& packetType);
sf::Packet& operator>>(sf::Packet& packet, PacketType& packetType);
sf::Packet& operator<<(sf::Packet& packet, PacketType& packetType);