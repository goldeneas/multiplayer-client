#pragma once
#include "IEventListener.hpp"

class ClientSync : public IEventListener {
	void handle(S2CNewClient e) override;
};