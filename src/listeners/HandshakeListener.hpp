#pragma once
#include "Events.hpp"
#include "IEventListener.hpp"

class HandshakeListener : public IEventListener {
public:
    void handle(ClientRefused e) override;
    void handle(ClientAccepted e) override;
};
