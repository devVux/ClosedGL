#pragma once

#include <memory>
#include <cmath>
#include "glm/glm.hpp"

#include <Physiks/Body.h>
#include "ClosedGL/Core/Clock.h"
#include "ClosedGL/Scene/Entity.h"
#include "ClosedGL/Utils/Utils.h"

#include "ClosedGL/Renderer/Texture.h"

struct TransformComponent {

	glm::mat4 transform;

	TransformComponent(const glm::mat4& t = glm::mat4(1.0f)): transform(t) { }

	void translate(const glm::vec2& v) {
		transform = glm::translate(glm::mat4(1.0f), { v.x, v.y, 1.0f });
	}

	void scale(const glm::vec2& v) {
		transform = glm::scale(glm::mat4(1.0f), { v.x, v.y, 1.0f });
	}

	void rotate(float angle, const glm::vec2& axis) {
		transform = glm::rotate(glm::mat4(1.0f), angle, { axis.x, axis.y, 0.0f });
	}


	
	operator glm::mat4() { return transform; }
	operator const glm::mat4& () const { return transform; }

	static std::string type() { return "Transform"; }

};

struct SpriteComponent {

	Texture* texture { nullptr };
	Coords coords;
	glm::vec3 color;

	SpriteComponent(const glm::vec3& c = glm::vec3(1.0f)): color(c) { }
	SpriteComponent(Texture* t, const glm::vec3& c = glm::vec3(1.0f)): texture(t), color(c) {
		if (t != nullptr)
			coords = { 0, 0, t->width(), t->height() };
	}
	SpriteComponent(SubTexture* t, const glm::vec3& c = glm::vec3(1.0f)): texture(t->texture()) {
		if (t != nullptr)
			coords = { 0, 0, t->texture()->width(), t->texture()->height() };
	}

	void addTexture(Texture* t) {
		texture = t;
		coords = { 0.0f, 0.0f, t->width(), t->height() };
	}

	operator const Texture&() const { return *texture; }

	static std::string type() { return "Sprite"; }

};

struct PhysicsComponent {

	Body* body;
	Entity* entity;

	PhysicsComponent(Body* b, Entity* e): body(b), entity(e) { }

	static std::string type() { return "Physics"; }

};


struct MotionComponent {

	Body* body;
	float speed;
	bool loop;

	MotionComponent() = default;
	MotionComponent(Body* b, const Vec2& targetPos, bool doLoop = false, float s = 1.0f): body(b), to(targetPos), loop(doLoop), from(body->position()), speed(s) {


	}

	// TODO: check weather is finished in order to avoid unnecessary calls
	void move(Timestep ts) {

		if (ts >= 1.0)
			ts = oldTs;

		// While animating forwards, we check if the animation ended (t >= 1)
		// If so, we reverse subtracting by delta
		if (!reverse) {
			t += ts.delta;
			t = std::min(t.delta, 1.0);
			reverse = t >= 1;
		} else if (reverse && loop) {
			t -= ts.delta;
			t = std::max(t.delta, -1.0);
			reverse = t >= 0;
		}


		//float x = std::lerp(from.x, to.x, (float) t);
		//float y = std::lerp(from.y, to.y, (float) t);

		//body->setPosition({ x, y });

		oldTs = ts;

	}

	static std::string type() { return "Motion"; }

	private:

		Timestep oldTs;
		Timestep t;

		Vec2 to;
		Vec2 from;
		bool reverse { false };

};