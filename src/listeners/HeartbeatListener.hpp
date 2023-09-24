#pragma once
#include "IEventListener.hpp"

class HeartbeatListener : public IEventListener {
    void handle(IncomingHeartbeatRequest e) override;
};
