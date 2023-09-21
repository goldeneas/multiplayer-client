#include "HandshakeListener.hpp"
#include <spdlog/spdlog.h>
#include "../NetworkClient.hpp"

void HandshakeListener::handle(ClientAccepted e) {
    NetworkClient::setId(e.assignedId);
    NetworkClient::setHandshakeStatus(HandshakeStatus::ACCEPTED);

    spdlog::debug("Server has accepted our handshake!");
}

void HandshakeListener::handle(ClientRefused e) {
    NetworkClient::setHandshakeStatus(HandshakeStatus::REFUSED);
    spdlog::debug("Server has refused our handshake.");
}