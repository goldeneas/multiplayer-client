#include "ClientSync.hpp"
#include <spdlog/spdlog.h>
#include "EntityBuilder.hpp"

void ClientSync::handle(S2CNewClient e) {
	spdlog::debug("Server has told us that a new client has connected! [ID: {}]", e.id);
	EntityBuilder::client(e.id);
}