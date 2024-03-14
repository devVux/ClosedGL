#pragma once


#include <ClosedGL.h>
#include <string>

struct GameObject {

	Entity entity;
	std::string label;

	GameObject(Entity e, std::string&& title): entity(e), label(title) { }

	template <class T, class ...Args>
	void addComponent(Args&&... args) {
		entity.addComponent<T>(std::forward<Args>(args)...);
	}

	template <class T>
	void removeComponent() {
		entity.removeComponent<T>();
	}

	template <class T>
	bool hasComponent() const {
		return SceneManager::hasComponent<T>(entity);
	}

	bool operator==(const GameObject& other) const { return entity == other.entity; }

};




