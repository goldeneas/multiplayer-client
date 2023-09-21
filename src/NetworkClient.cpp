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
    HandshakeStatus handshakeStatus = HandshakeStatus::IDLE;
}

void NetworkClient::poll() {
	if(!isSetup())
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
			EventBus::emit<IncomingPacketPreprocess>(p);
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
    HandshakeStatus currentStatus = getHandshakeStatus();
    if(currentStatus == HandshakeStatus::ACCEPTED ||  currentStatus == HandshakeStatus::WAITING) {
        spdlog::warn("Tried handshaking server, but we are still talking with the it!");
        return;
    }

    socket.setBlocking(false);
	status = socket.bind(sf::Socket::AnyPort);
    localPort = socket.getLocalPort();
    localAddress = sf::IpAddress::getLocalAddress();

	if(status != sf::Socket::Status::Done) {
        reset();
		spdlog::info("Could not bind socket to {}!", localPort);
		return;
	}

    C2SHandshake hs;
    hs.clientPort = localPort;
    hs.clientAddress = localAddress.toString();
    send(hs, address, port);

    remotePort = port;
    remoteAddress = address;
    handshakeStatus = HandshakeStatus::WAITING;

    spdlog::info("Trying to handshake with server at {}:{}...", address, port);
}

void NetworkClient::send(PacketWrapper& packet, sf::IpAddress address, int port) {
	if(!isSetup()) {
		spdlog::warn("Tried sending packet to server, but our client is not ready yet!");
		return;
	}

	spdlog::debug("Sending packet to server. [ID: {}]", static_cast<int>(packet.type));

    sf::Packet p = packet.build();
	socket.send(p, address, port);
}

void NetworkClient::shutdown() {
	if(getHandshakeStatus() != HandshakeStatus::ACCEPTED) {
		spdlog::error("Tried shutting down client, but server hasn't accepted us yet!");
		return;
	}

    // todo: tell server that we have left

    reset();
    spdlog::info("Client has been shutdown.");
}

void NetworkClient::reset() {
    localPort = 0;
    localAddress = "";

    status = sf::Socket::NotReady;
    handshakeStatus = HandshakeStatus::IDLE;
}

void NetworkClient::setHandshakeStatus(HandshakeStatus s) {
    handshakeStatus = s;
}

HandshakeStatus NetworkClient::getHandshakeStatus() {
    return handshakeStatus;
}

bool NetworkClient::isSetup() {
    return status == sf::Socket::Status::Done;
}

void NetworkClient::setId(Client::ID assignedId) {
    if(getHandshakeStatus() == HandshakeStatus::ACCEPTED) {
        spdlog::error("Tried setting client's id while we've already been accepted!");
        return;
    }

    id = assignedId;
}

Client::ID NetworkClient::getId() {
	if(id == -1)
		spdlog::error("Tried getting ID of our client, but it hasn't been setup yet!");

	return id;
}