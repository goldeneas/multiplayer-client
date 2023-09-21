#include "ScreenStack.hpp"
#include <iostream>

/*
	creates a new screen
	returns a shared pointer to that screen
*/
Screen::Pointer ScreenStack::createScreen(Screen::Type type) {
	return screenFactories[type]();
}

/*
	starts a new screen
*/
void ScreenStack::pushScreen(Screen::Type type) {
	pendingChanges.emplace_back(MemoryAction::PUSH, type);
}

/*
	closes the given screen
*/
void ScreenStack::popScreen() {
	pendingChanges.emplace_back(MemoryAction::POP);
}

/*
	closes top-most screen and opens a new one
*/
void ScreenStack::switchLastScreenTo(Screen::Type type) {
	popScreen();
	pushScreen(type);
}

/*
	update the screen stack
	- update all screens (read the stack)
	- apply any pending changes (write to the stack while there are no readers)
	- clear pending changes
	these steps SHOULD make the ScreenStack thread-safe
*/
void ScreenStack::update(float dt) {
	// update screens
	for(Screen::Pointer& s : activeScreens)
		s->update(dt);

	// apply pending changes
	for(PendingChange change : pendingChanges)
		switch(change.action)
		{
			case MemoryAction::POP:
				activeScreens.pop_back();
				break;

			case MemoryAction::PUSH:
				activeScreens.push_back(createScreen(change.screenType));
				break;
		}

	// clear pending changes
	pendingChanges.clear();
}

/*
	draw all active screens
*/
void ScreenStack::draw(sf::RenderWindow& window) {
	for(Screen::Pointer& s : activeScreens)
		s->draw(window);
}

/*
	close all screens
*/
void ScreenStack::close() {
	for(Screen::Pointer& s : activeScreens)
		s->close();

	activeScreens.clear();
}