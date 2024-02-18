#pragma once

#include "Shader.h"
#include "Buffer.h"
#include "Texture.h"

#include "ClosedGL/Scene/Scene.h"

#include "ClosedGL/Scene/OrthographicCamera.h"

#include "ClosedGL/Renderer/Texture.h"

namespace Renderer2D {

	struct Stats {
		static uint32_t drawCalls;
		static uint32_t polyCount;

		static void reset() {
			drawCalls = 0;
			polyCount = 0;
		}

	};

	static constexpr unsigned int layoutSize = 8 + 12 + 8;	// pos + color + textCoord
	static constexpr int BATCH_CAPACITY = 10;
	static constexpr int BATCH_INDICES = BATCH_CAPACITY * 6;
	static constexpr int BATCH_DATA = BATCH_CAPACITY * layoutSize;

	struct Polygon {
		float* data;
		uint32_t vertices;
		uint32_t count;

		Polygon(std::initializer_list<std::initializer_list<float>> v): vertices((uint32_t) v.size()), count((uint32_t) (v.size() * v.begin()->size())) {
			if (v.size() < 3)
				throw std::invalid_argument("Initializer list must contain at least 3 vertices.");

			data = new float[count];

			size_t i = 0;
			for (const auto it : v)
				for (const auto it2 : it)
					data[i++] = it2;

		}

		~Polygon() {
			delete[] data;
		}

	};


	void init();
	
	void insert(const Polygon& p);

	void clear(float r = 0.2f, float g = 0.2f, float b = 0.2f);


	void beginScene(const OrthographicCamera& camera);
	void endScene();

	void drawQuad(glm::vec2 position, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f));
	void drawQuad(const glm::mat4& transform, const glm::vec3& color = glm::vec3(1.0f));
	void drawQuad(const glm::mat4& transform, const Texture& texture, const glm::vec3& color = glm::vec3(1.0f));
	void draw();

};