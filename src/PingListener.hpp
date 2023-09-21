#pragma once
#include "IEventListener.hpp"

class PingListener : IEventListener {
	void handle(C2CTick e) override;
};