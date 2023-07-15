#pragma once

class IWidget {
public:
	virtual ~IWidget() {}
	virtual void draw() = 0;
};