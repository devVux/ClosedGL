#pragma once

#include <memory>
#include "glm/glm.hpp"

#include <Physiks/Body.h>
#include "ClosedGL/Core/Clock.h"
#include "ClosedGL/Scene/Entity.h"
#include "ClosedGL/Utils/Utils.h"

#include "ClosedGL/Renderer/Texture.h"

struct TransformComponent {

	glm::mat4 transform;

	TransformComponent(const glm::mat4& t = glm::mat4(1.0f)): transform(t) { }

	void translate(const glm::vec3& v) {
		transform[3] += glm::vec4(v, 1.0f);
	}

	void setPosition(const glm::vec2& v) {
		transform[3] = glm::vec4(v, 0.0f, 1.0f);
	}

	operator glm::mat4() { return transform; }
	operator const glm::mat4& () const { return transform; }

};

struct SpriteComponent {

	glm::vec3 color;

	SpriteComponent(const glm::vec3& c = glm::vec3(1.0f)): color(c) { }

};

struct PhysicsComponent {

	Body* body;
	Entity* entity;

	PhysicsComponent(Body* b, Entity* e): body(b), entity(e) { }

};

struct MeshComponent {

	Texture* texture;
	Coords coords;

	MeshComponent(Texture* t): texture(t), coords({ 0, 0, t->width(), t->height() }) { }
	MeshComponent(SubTexture* t): texture(t->texture()), coords(t->coords()) { }

	operator const Texture&() const { return *texture; }

};

struct MotionComponent {

	Body* body;
	float speed;
	bool loop;

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


		float x = std::lerp(from.x, to.x, (float) t);
		float y = std::lerp(from.y, to.y, (float) t);

		body->setPosition({ x, y });

		oldTs = ts;

	}

	private:

		Timestep oldTs;
		Timestep t;

		Vec2 to;
		Vec2 from;
		bool reverse { false };

};