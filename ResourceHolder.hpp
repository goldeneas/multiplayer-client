#pragma once
#include <memory>
#include <cassert>
#include <stdexcept>
#include <unordered_map>
#include <SFML/Graphics/Texture.hpp>

// path to the default resources folder
const std::string RESOURCES_PATH = "resources/";

template<typename Identifier, class Resource>
class ResourceHolder {
private:
	/*
		store link between each unique identifier to a resource
		ex. Texture::PLAYER -> player.png
	*/
	std::unordered_map<Identifier, std::unique_ptr<Resource>> resources;
public:
	/*
		loads a specific resource and assigns an identifier to it
	*/
	void load(Identifier id, const std::string& filename) {
		std::unique_ptr<Resource> resource = std::make_unique<Resource>();

		if(!resource->loadFromFile(RESOURCES_PATH + filename))
			throw std::runtime_error("Could not load resource: " + filename);

		insert(id, std::move(resource));
	}

	/*
		get resource with specified id
	*/
	Resource& get(Identifier id) {
		return *resources.at(id);
	}
private:
	/*
		link unique identifier to a resource
		isKeyUnique is used to determine whether an identifier has already been inserted in the map
		(an unordered_map only stores unique keys)
	*/
	void insert(Identifier id, std::unique_ptr<Resource> resource) {
		bool isIdentifierUnique = (resources.count(id) == 0 ? true : false);
		assert(isIdentifierUnique == true);

		resources.emplace(id, std::move(resource));
	}
};