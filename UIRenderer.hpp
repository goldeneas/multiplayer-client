#pragma once

#include <list>
#include <memory>
#include <utility>
#include "IWidget.hpp"

#include <iostream>

class UIRenderer {
private:
	std::list<std::unique_ptr<IWidget>> widgets;
public:
	void draw();

	template<typename Widget, typename... Args>
	void add(Args&&... args) { widgets.push_back(std::make_unique<Widget>(std::forward<Args>(args)...)); }
};