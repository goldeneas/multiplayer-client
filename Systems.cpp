#include "Systems.hpp"
#include "Components.hpp"

void Systems::move(entt::registry& entities, float dt) {
	const auto& movables = entities.view<CPosition, CVelocity>();

	movables.each([&entities, &dt](const auto entity, auto& position, auto& velocity) {
		velocity.verticalAxis = 0;
		velocity.horizontalAxis = 0;

		if(entities.any_of<CController>(entity)) {
			auto& controller = entities.get<CController>(entity);

			if(controller.up)		velocity.verticalAxis = -1;
			if(controller.left)		velocity.horizontalAxis = -1;
			if(controller.down)		velocity.verticalAxis = +1;
			if(controller.right)	velocity.horizontalAxis = +1;

			if(velocity.horizontalAxis != 0 && velocity.verticalAxis != 0) {
				velocity.verticalAxis /= std::sqrt(2.f);
				velocity.horizontalAxis /= std::sqrt(2.f);
			}
		}

		position.y += velocity.speed * velocity.verticalAxis * dt;
		position.x += velocity.speed * velocity.horizontalAxis * dt;
	});
}

void Systems::draw(entt::registry& entities, sf::RenderWindow& window) {
	auto drawables = entities.view<CDraw>();

	drawables.each([&entities, &window](const auto entity, auto& draw) {

		if(entities.any_of<CPosition>(entity)) {
			auto& position = entities.get<CPosition>(entity);
			auto& sprite = draw.sprite;

			sprite.setPosition({ position.x, position.y });
		}


		window.draw(draw.sprite);
	});
}

void Systems::controller(entt::registry& entities) {
	const auto& controllers = entities.view<CController>();

	controllers.each([](auto& controller) {
		controller.up = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
		controller.left = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		controller.down = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		controller.right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	});
}