#include "UIRenderer.hpp"

void UIRenderer::draw() {
	for(auto& widget : widgets)
		(*widget).draw();
}