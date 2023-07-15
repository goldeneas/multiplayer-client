#pragma once
#include "IEventListener.hpp"

class NewClientListener : IEventListener {
	void handle(S2CNewClient e) override;
};