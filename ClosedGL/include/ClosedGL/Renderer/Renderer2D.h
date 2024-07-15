#pragma once

#include "Shader.h"
#include "Buffer.h"
#include "Texture.h"

#include "ClosedGL/Scene/Scene.h"

#include "ClosedGL/Scene/OrthographicCamera.h"

#include "ClosedGL/Renderer/Texture.h"


namespace Renderer2D {

	inline constexpr int INDICES_PER_QUAD = 6;
	inline constexpr int BATCH_CAPACITY = 10;
	inline constexpr int BATCH_INDICES = BATCH_CAPACITY * INDICES_PER_QUAD;


	struct Quad {

		static constexpr int stride = 2 + 3;
		std::array<float, 4 * stride> points;

		Quad() {
			points.fill(0);
		}

		Quad& setColor(glm::vec3 color) {
			setEvery(color, COLOR_POS);
			return *this;
		}
		Quad& setPosition(const std::initializer_list<glm::vec2>& positions) {
			if (positions.size() != 4)
				return *this;
			setEvery(*(positions.begin() + 0), COORDINATES_POS + 0 * stride, 1);
			setEvery(*(positions.begin() + 1), COORDINATES_POS + 1 * stride, 1);
			setEvery(*(positions.begin() + 2), COORDINATES_POS + 2 * stride, 1);
			setEvery(*(positions.begin() + 3), COORDINATES_POS + 3 * stride, 1);
			return *this;												   
		}

		float* data() { return points.data(); }
		constexpr uint32_t count() const { return static_cast<uint32_t>(points.size()); }
		constexpr uint32_t size() const { return static_cast<uint32_t>(points.size() * sizeof(float)); }

		private:

			static constexpr uint32_t COORDINATES_POS = 0;
			static constexpr uint32_t COLOR_POS = 2;


			template <typename T>
			requires requires(T t) { { t.length() } -> std::same_as<int>; }
			void setEvery(const T& val, const uint32_t pos, int times = 4) {
				for (int i = 0; i < times; ++i)
					for (int j = 0; j < val.length(); ++j)
						if (pos + j < points.size()) {
							uint32_t row = i * stride;
							uint32_t col = pos + j;
							points[row + col] = val[j];
						}
			}

	};


	void init();
	
	void insert(const Quad& q);


	void beginScene(const OrthographicCamera& camera);
	void endScene();

	void drawQuad(glm::vec2 position, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f));
	void draw();

};