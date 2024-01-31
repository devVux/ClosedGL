#pragma once

#include "Shader.h"
#include "Buffer.h"
#include "Texture.h"

#include <vector>

#include "ClosedGL/Scene/OrthographicCamera.h"

class Batch {

	public:

		struct Polygon {
			float* data;
			uint32_t vertices;
			uint32_t count;

			Polygon(std::initializer_list<std::initializer_list<float>> v): vertices((uint32_t) v.size()), count((uint32_t) (v.size()* v.begin()->size())) {
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
		
		static constexpr unsigned int layoutSize = 8 + 12 + 8 + 4;	// pos + color + textCoord
		static constexpr int BATCH_CAPACITY = 100;
		static constexpr int BATCH_INDICES  = BATCH_CAPACITY * 6;
		static constexpr int BATCH_DATA		= BATCH_CAPACITY * layoutSize;

	public:

		~Batch() {
			delete mVertexArray;
			delete mBuffer;
			delete mIndexBuffer;

			delete[] mIndices;
		}

		void init();

		void begin();
		void flush();
		void push(float* data, unsigned int count);
		void insert(const Polygon& q);
		void insert(float* data, uint32_t count);
		void end();
		void draw();


	private:

		VertexArray* mVertexArray;
		VertexBuffer* mBuffer;
		IndexBuffer* mIndexBuffer;

		unsigned int* mIndices;
		unsigned int mCurrentPos;

};


