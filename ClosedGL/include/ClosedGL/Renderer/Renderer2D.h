#pragma once

#include "Shader.h"
#include "Buffer.h"
#include "Texture.h"

#include "ClosedGL/Scene/Scene.h"

#include "ClosedGL/Core/OrthographicCamera.h"

namespace Renderer2D {

	static constexpr unsigned int layoutSize = 8 + 12 + 8 + 4;	// pos + color + textCoord
	static constexpr int BATCH_CAPACITY = 100;
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


	// Todo: camera non va aggioranata altrove?
	void beginScene(const OrthographicCamera& camera);
	void endScene();

	void drawQuad(glm::vec2 position, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f));
	void drawQuad(const glm::mat4& transform, glm::vec3 color = glm::vec3(1.0f));
	void draw();

	size_t assignTextureSlot(const Texture& texture);

};