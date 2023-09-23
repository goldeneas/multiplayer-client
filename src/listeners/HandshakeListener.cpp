#include "HandshakeListener.hpp"
#include <spdlog/spdlog.h>
#include "NetworkClient.hpp"

void HandshakeListener::handle(ClientAccepted e) {
    if(NetworkClient::getHandshakeStatus() != HandshakeStatus::WAITING) {
        spdlog::error("Tried setting handshake status to accepted, but we're not in waiting mode!");
        return;
    }

    NetworkClient::setId(e.assignedId);
    NetworkClient::setHandshakeStatus(HandshakeStatus::ACCEPTED);
    spdlog::info("Server has accepted our handshake!");
}

void HandshakeListener::handle(ClientRefused e) {
    if(NetworkClient::getHandshakeStatus() != HandshakeStatus::WAITING) {
        spdlog::error("Tried setting handshake status to accepted, but we're not in waiting mode!");
        return;
    }

    NetworkClient::setHandshakeStatus(HandshakeStatus::REFUSED);
    spdlog::info("Server has refused our handshake.");
}