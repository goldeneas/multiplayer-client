#pragma once

#include <memory>
#include "Events.hpp"

class IEventListener {
public:
	using Pointer = std::unique_ptr<IEventListener>;
public:
	virtual ~IEventListener() = default;

    virtual void handle(PlayerJoin e) {};
    virtual void handle(PlayerLeave e) {};
	virtual void handle(ClientRefused e) {};
    virtual void handle(ClientAccepted e) {};
    virtual void handle(IncomingPacketPreprocess e) {};
    virtual void handle(IncomingHeartbeatRequest e) {};
};