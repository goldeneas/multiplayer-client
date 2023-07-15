#pragma once
#include <map>
#include <memory>
#include <vector>
#include <functional>
#include <unordered_map>
#include "Screen.hpp"

class ScreenStack {
private:
	/*
		defines action in a pending stack change
	*/
	enum MemoryAction { PUSH, POP };

	/*
		defines a pending change
		this is used to push or pop screens in the stack
		pushing and popping only happens after the update loop ends because we want to
		ensure that we only write to activeScreens when nobody is reading (thread-safing)
	*/
	struct PendingChange {
		PendingChange(MemoryAction action, Screen::Type screenType = Screen::Type::NONE)
			: action(action), screenType(screenType) {};
		
		/*
			the screen type used together with PUSH operation
		*/
		Screen::Type screenType;

		/*
			the action type to insert in the pending changes
		*/
		MemoryAction action;
	};
private:
	/*
		hold a reference to a context used by all screens managed by this screenstack
	*/
	Screen::Context& screenContext;

	/*
		pending-write changes for the screen stack
	*/
	std::vector<PendingChange> pendingChanges;

	/*
		a "stack" of screens
		each screen in the stack will be updated, drawn and closed when needed
	*/
	std::vector<Screen::Pointer> activeScreens;

	/*
		factory pattern
		each screen type has a lambda linked to it
		the lambda creates and returns a shared_ptr to a new screen of said type
	*/
	std::unordered_map<Screen::Type, std::function<Screen::Pointer()>> screenFactories;
private:
	/*
		creates a new screen
		returns a shared pointer to that screen
	*/
	Screen::Pointer createScreen(Screen::Type type);
public:
	/*
		constructor
	*/
	explicit ScreenStack(Screen::Context& context) : screenContext(context) {};

	/*
		links a Screen::Type to a Screen class
		T = the class we want to link to that type
	*/
	template<class T>
	void registerScreen(Screen::Type type) {
		// if the compiler complains about not being able to treat a child's pointer as the parent's
		// remember to specify a !public! inheritance of Screen in the child class
		screenFactories[type] = [this]() -> Screen::Pointer { return std::make_unique<T>(*this, screenContext); };
	}

	/*
		gets number of active screens
    */
	int size() { return activeScreens.size(); }

	/*
		starts a new screen
	*/
	void pushScreen(Screen::Type type);

	/*
		closes the given screen
	*/
	void popScreen();

	/*
		closes top-most screen and opens a new one
	*/
	void switchLastScreenTo(Screen::Type type);

	/*
		update all active screens
	*/
	void update(float dt);

	/*
		draw all active screens
	*/
	void draw(sf::RenderWindow& window);

	/*
		close all screens
	*/
	void close();
};