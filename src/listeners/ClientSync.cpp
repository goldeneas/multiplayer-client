#include "ClientSync.hpp"
#include <spdlog/spdlog.h>
#include "../EntityBuilder.hpp"

void ClientSync::handle(PlayerJoin e) {
	spdlog::debug("Server has told us that a new client has connected! [ID: {}]", e.id);
	EntityBuilder::client(e.id);
}