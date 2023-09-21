#pragma once

#include <string>
#include <SFML/Network.hpp>
#include "IWidget.hpp"

class NetworkWidget : public IWidget {
private:
	int portInput = 39964;
	std::string ipInput = "localhost";
public:
	void draw() override;
};