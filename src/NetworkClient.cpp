#include "NetworkClient.hpp"
#include <thread>
#include <spdlog/spdlog.h>
#include "PacketProcessor.hpp"

namespace NetworkClient {
	sf::UdpSocket socket;
	sf::TcpSocket::Status status = sf::Socket::NotReady;

    unsigned short localPort;
    sf::IpAddress localAddress;

    unsigned short remotePort;
    sf::IpAddress remoteAddress;

    Client::ID id = -1;
    bool isHandshakeSuccessful = false;
}

void NetworkClient::poll() {
	if(!isReady())
		return;

    processIncomingPackets();
}

void NetworkClient::processIncomingPackets() {
	sf::Packet p;
    sf::Socket::Status receiveStatus;
    unsigned short senderPort;
    sf::IpAddress senderAddress;

    receiveStatus = socket.receive(p, senderAddress, senderPort);
    if(p.getDataSize() == 0)
        return;

    if(senderAddress != remoteAddress && senderPort != remotePort) {
        spdlog::warn("Received packet from unrecognised source ({}:{})", senderAddress.toString(), senderPort);
        return;
    }

	switch(receiveStatus) {
		case sf::Socket::Done: {
			EventBus::emit<OutgoingPacketPreprocess>(p);
			PacketType t = PacketProcessor::process(p);
			spdlog::info("Server sent packet [TYPE: {}]", static_cast<int>(t));
			break;
		}

		case sf::Socket::Disconnected:
			spdlog::warn("Socket receive returned disconnected status. Are we not connected anymore?");
			shutdown();
			break;

		default:
			spdlog::error("A packet has been received, but it has an unhandled SFML state!");
			break;
	}
}

void NetworkClient::handshake(const std::string& address, int port) {
    if(isHandshakeDone()) {
        spdlog::warn("Tried handshaking server, but we have already completed our handshake!");
        return;
    }

    socket.setBlocking(false);
	status = socket.bind(sf::Socket::AnyPort);
    localPort = socket.getLocalPort();
    localAddress = sf::IpAddress::getLocalAddress();

	if(status != sf::Socket::Status::Done) {
        localPort = 0;
        localAddress = "";

		spdlog::info("Could not bind socket to {}!", localPort);
		return;
	}

    C2SHandshake hs;
    hs.clientPort = localPort;
    hs.clientAddress = localAddress.toString();
    send(hs, address, port);

    remotePort = port;
    remoteAddress = address;

    spdlog::info("Trying to handshake with server at {}:{}...", address, port);
}

void NetworkClient::send(PacketWrapper& packet, sf::IpAddress address, int port) {
	if(!isReady()) {
		spdlog::warn("Tried sending packet to server, but our client is not ready yet!");
		return;
	}

	spdlog::debug("Sending packet to server. [ID: {}]", static_cast<int>(packet.type));

    sf::Packet p = packet.build();
	socket.send(p, address, port);
}

void NetworkClient::shutdown() {
	if(!isReady()) {
		spdlog::error("Tried shutting down client, but socket is not ready yet!");
		return;
	}

    // todo: tell server that we have left

    status = sf::Socket::NotReady;
    spdlog::info("Client has been shutdown.");
}

bool NetworkClient::isHandshakeDone() {
    return isHandshakeSuccessful;
}

bool NetworkClient::isReady() {
    return status == sf::Socket::Status::Done;
}

sf::Socket::Status NetworkClient::getStatus() {
	return status;
}

Client::ID NetworkClient::getId() {
	if(id == -1)
		spdlog::error("Tried getting ID of our client, but it hasn't been setup yet!");

	return id;
}