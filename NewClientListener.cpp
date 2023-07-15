#include "NewClientListener.hpp"
#include <spdlog/spdlog.h>
#include "EntityBuilder.hpp"

void NewClientListener::handle(S2CNewClient e) {
	spdlog::debug("received new client packet");
}