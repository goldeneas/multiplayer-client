#include "NetworkClient.hpp"
#include <thread>
#include <spdlog/spdlog.h>
#include "PacketBuilder.hpp"
#include "PacketProcessor.hpp"

namespace NetworkClient {
	constexpr int HEARTBEAT_INTERVAL = 2;

	sf::TcpSocket socket;
	sf::SocketSelector selector;
	sf::TcpSocket::Status status = sf::Socket::Disconnected;

	float timeSinceLastHeartbeat = 0;
}

// TODO: time to multithread :)
// calls to selector wait also lock our rendering thread
// FPS are capped at 144fps currently, but this isn't such a good option
// it will take a while, and errors, and locks
void NetworkClient::poll(float dt) {
	if(!isConnected())
		return;

	if(selector.wait(sf::seconds(0.0069f)))
		processIncomingPackets();

	heartbeat(dt);
}

void NetworkClient::processIncomingPackets() {
	//if(!selector.isReady(socket))
	//	return;

	sf::Packet p;
	switch(socket.receive(p)) {
		case sf::Socket::Done: {
			// first, emit general "packet received" event
			EventBus::emit<S2CPacketPreprocess>(p);
			// then, process the packet and emit correct, specific event
			PacketType t = PacketProcessor::process(p);
			spdlog::info("Server sent packet [TYPE: {}]", static_cast<int>(t));
			break;
		}

		case sf::Socket::Disconnected:
			spdlog::warn("Received packet with disconnected state. Are we not connected anymore?");
			disconnect();
			break;

		default:
			spdlog::error("A packet has been received, but it has an unhandled SFML state!");
			break;
	}
}

void NetworkClient::disconnect() {
	if(!isConnected()) {
		spdlog::error("Tried disconnecting client, but connection hasn't been established yet!");
		return;
	}

	EventBus::emit<C2SDisconnection>();
	selector.remove(socket);
	socket.disconnect();

	status = sf::Socket::Disconnected;
	spdlog::info("Disconnected from server");
}

void NetworkClient::connect(const std::string& address, int port) {
	if(isConnected()) {
		spdlog::error("Tried connecting client, but connection has already been established!");
		return;
	}

	status = socket.connect(address, port);
	if(status != sf::Socket::Status::Done) {
		spdlog::info("Could not establish connection with host: {}:{}", address, port);
		return;
	}

	selector.add(socket);

	EventBus::emit<C2SConnection>();
	spdlog::info("Connection established with host: {}:{}", address, port);
}

void NetworkClient::send(sf::Packet& p) {
	if(!isConnected()) {
		spdlog::warn("Tried sending packet to server, but connection has not been established yet!");
		return;
	}

	spdlog::debug("Sending packet to server");

	socket.send(p);
}

bool NetworkClient::isConnected() {
	return getStatus() == sf::Socket::Done;
}

sf::Socket::Status NetworkClient::getStatus() {
	return status;
}

void NetworkClient::heartbeat(float dt) {
	timeSinceLastHeartbeat += dt;

	if(timeSinceLastHeartbeat >= HEARTBEAT_INTERVAL) {
		sf::Packet beat = PacketBuilder::build(PacketType::C2S_HEARTBEAT);
		send(beat);

		timeSinceLastHeartbeat = 0;
	}
}