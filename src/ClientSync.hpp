#pragma once
#include "IEventListener.hpp"

class ClientSync : public IEventListener {
	void handle(PlayerJoin e) override;
};