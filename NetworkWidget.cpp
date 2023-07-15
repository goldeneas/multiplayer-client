#include "NetworkWidget.hpp"

#include "imgui.h"
#include "imgui_stdlib.h"
#include "NetworkClient.hpp"

void NetworkWidget::draw() {
	ImGui::Begin("Network", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::Text("Ip Address");
	ImGui::InputText("##ipInput", &ipInput);
	ImGui::Spacing();
	ImGui::Text("Port");
	ImGui::InputInt("##portInput", &portInput, 0, 0);
	ImGui::Separator();
	ImGui::Text("Connection established: %s", NetworkClient::isConnected() ? "true" : "false");

	if(NetworkClient::getStatus() == sf::Socket::Error) {
		ImGui::Text("Could not connect to server!");
	}

	ImGui::End();
}