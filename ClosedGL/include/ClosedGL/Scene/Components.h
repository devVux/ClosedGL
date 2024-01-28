#pragma once

#include <memory>
#include "glm/glm.hpp"

struct TransformComponent {

	glm::mat4 transform;

	TransformComponent(const glm::mat4& t = glm::mat4(1.0f)): transform(t) { }

	void applyTranslation(const glm::vec3& v) {
		transform[3] += glm::vec4(v, 1.0f);
	}

	void setPosition(const glm::vec2& v) {
		transform[3] = glm::vec4(v, 0.0f, 1.0f);
	}

	operator glm::mat4() { return transform; }
	operator const glm::mat4&() const { return transform; }
	
};

struct SpriteComponent {

	glm::vec3 color;

	SpriteComponent(const glm::vec3& c = glm::vec3(1.0f)): color(c) { }

};

class Entity;

template <class T>
struct PhysicsComponent {
	
	T* body;
	std::shared_ptr<Entity> entity;

	PhysicsComponent(T* b, std::shared_ptr<Entity> e): body(b), entity(e) { }

};