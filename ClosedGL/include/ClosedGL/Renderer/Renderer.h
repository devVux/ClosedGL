#pragma once

#include "Buffer.h"
#include "Shader.h"

#include "ClosedGL/Core/Actor.h"

#include "ClosedGL/Renderer/Batch.h"
#include "ClosedGL/Core/PerspectiveCamera.h"
#include "ClosedGL/Core/OrthographicCamera.h"

#include "Texture.h"

#include <array>

class Renderer {
	
	public:

		void init();

		void clear(float r = 0.2f, float g = 0.2f, float b = 0.2f) const;


		void beginScene(const OrthographicCamera& camera);
		void submit(const Shader& shader, const VertexArray& vertexArray);
		void endScene();


		void beginBatch(const OrthographicCamera& camera);
		void drawQuad(glm::vec2 position, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f));
		void drawQuad(glm::vec2 position, glm::vec2 size, const Texture& texture);
		void drawQuad(glm::vec2 position, glm::vec2 size, const SubTexture& subTexture);

		void drawQuad(glm::mat4 transform, glm::vec3 color = glm::vec3(1.0f));

		void endBatch();


		void draw(const VertexArray& vertexArray);

		const Stats& stats() const { return mStats; }

	private:

		size_t assignTextureSlot(const Texture& texture);

	private:

		glm::mat4 mView;
		glm::mat4 mProjection;

		Shader* pShader;
		VertexArray* pVertexArray;
		Texture* pWhiteTexture;

		// TODO: passa a heap allocated textures
		std::array<const Texture*, 32> mTextureSlots { nullptr };

		Batch mBatch;

		Stats mStats;

};