#include "HeartbeatListener.hpp"
#include "NetworkClient.hpp"
#include "IPacketWrapper.hpp"

void HeartbeatListener::handle(IncomingHeartbeatRequest e) {
    C2SHeartbeat hb;
    NetworkClient::send(hb);
}