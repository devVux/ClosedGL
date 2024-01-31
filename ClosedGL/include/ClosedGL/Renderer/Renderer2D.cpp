#include "pch.h"
#include "Renderer2D.h"


namespace Renderer2D {

	uint32_t Renderer2D::RendererStats::drawCalls = 0;
	uint32_t Renderer2D::RendererStats::polyCount = 0;

	struct RendererStorage {
		Shader* pShader;
		VertexArray* pVertexArray;
		VertexBuffer* pBuffer;
		IndexBuffer* pIndexBuffer;
		
		Texture* pWhiteTexture;
		std::array<const Texture*, 32> mTextureSlots;
		
		unsigned int mCurrentPos = 0;

		Scene scene;

		~RendererStorage() {
			delete pShader;
			delete pVertexArray;
			delete pBuffer;
			delete pIndexBuffer;

			for (const auto& texture : mTextureSlots)
				delete texture;

		}

	};

	namespace VerticesDisposition {
		static const glm::vec4 a { 0.0f, 0.0f, 0.0f, 1.0f };
		static const glm::vec4 b { 1.0f, 0.0f, 0.0f, 1.0f };
		static const glm::vec4 c { 1.0f, 1.0f, 0.0f, 1.0f };
		static const glm::vec4 d { 0.0f, 1.0f, 0.0f, 1.0f };
	};

	static RendererStorage storage;
	
	void init() {

	   // Batch init
		storage.pVertexArray = new VertexArray;
		storage.pVertexArray->bind();

		storage.pBuffer = new VertexBuffer;
		storage.pBuffer->push(nullptr, BATCH_DATA * sizeof(float), GL_DYNAMIC_DRAW);

		BufferLayout layout;
		layout.push(GL_FLOAT, 2);
		layout.push(GL_FLOAT, 3);
		layout.push(GL_FLOAT, 2);
		layout.push(GL_FLOAT, 1);
		storage.pBuffer->setLayout(layout);

		storage.pIndexBuffer = new IndexBuffer;

		storage.pVertexArray->addBuffer(*storage.pBuffer);
		storage.pVertexArray->setIndexBuffer(storage.pIndexBuffer);



		// Renderer init
		storage.pWhiteTexture = new Texture;
		uint32_t white = 0xffffffff;
		storage.pWhiteTexture->setData(&white);
		storage.mTextureSlots[0] = storage.pWhiteTexture;

		storage.pShader = new Shader;
		storage.pShader->fromFile("F:\\dev\\ClosedGL\\ClosedGL\\assets\\shaders\\simple.shader");
		storage.pShader->bind();

		int samplers[32];
		for (size_t i = 0; i < 32; i++) {
			glActiveTexture(GL_TEXTURE0 + 0);
			samplers[i] = (int) i;
		}

		storage.pShader->setUniformIntArray("uTextures", samplers, 32);





		uint32_t indices[BATCH_INDICES];

		uint32_t offset = 0;
		for (size_t i = 0; i < BATCH_INDICES; i += 6) {

			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 0;
			indices[i + 4] = offset + 2;
			indices[i + 5] = offset + 3;

			offset += 4;

		}

		storage.pIndexBuffer->push(indices, BATCH_INDICES * sizeof(uint32_t));

	}

	void insert(const Polygon& p) {

		if (storage.mCurrentPos + p.count > BATCH_CAPACITY * layoutSize)
			storage.mCurrentPos = 0;

		storage.pBuffer->insert(p.data, storage.mCurrentPos * sizeof(float), p.count * sizeof(float));
		storage.mCurrentPos += p.count;
		Renderer2D::RendererStats::polyCount++;
	}

	void clear(float r, float g, float b) {
		glClearColor(r, g, b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void beginScene(const OrthographicCamera& camera) {
	//storage.scene.beginScene(camera);

		storage.pShader->bind();
		storage.pShader->setUniformMatrix4("uProj", camera.projection());
		storage.pShader->setUniformMatrix4("uView", camera.view());

		storage.pVertexArray->bind();

		storage.mCurrentPos = 0;
		Renderer2D::RendererStats::reset();

	}

	void endScene() {
		draw();
	}

	void drawQuad(glm::vec2 position, glm::vec2 size, glm::vec3 color) {

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f)) *
			glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

		//Polygon quad {
		//	{ position.x,			position.y,				1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f },
		//	{ position.x + size.x,	position.y,				1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 0.0f },
		//	{ position.x + size.x,	position.y + size.y,	1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 0.0f },
		//	{ position.x,			position.y + size.y,	1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f },
		//};
		
		drawQuad(transform, color);

	}


	void drawQuad(const glm::mat4& transform, glm::vec3 color) {

		// TODO: export lambda
		const glm::vec4 a = transform * VerticesDisposition::a;
		const glm::vec4 b = transform * VerticesDisposition::b;
		const glm::vec4 c = transform * VerticesDisposition::c;
		const glm::vec4 d = transform * VerticesDisposition::d;

		Polygon quad {
			{ a[0],	a[1],	color.r, color.g, color.b,  1.0f, 0.0f, 0.0f },
			{ b[0],	b[1],	color.r, color.g, color.b,  0.0f, 0.0f, 0.0f },
			{ c[0],	c[1],	color.r, color.g, color.b,  1.0f, 1.0f, 0.0f },
			{ d[0],	d[1],	color.r, color.g, color.b,  0.0f, 1.0f, 0.0f },
		};

		Renderer2D::insert(quad);

	}
	

	void drawQuad(const glm::mat4& transform, glm::vec4 color) {

		// TODO: export lambda
		const glm::vec4 a = transform * VerticesDisposition::a;
		const glm::vec4 b = transform * VerticesDisposition::b;
		const glm::vec4 c = transform * VerticesDisposition::c;
		const glm::vec4 d = transform * VerticesDisposition::d;

		Polygon quad {
			{ a[0],	a[1],	color.r, color.g, color.b,  1.0f, 0.0f, 0.0f },
			{ b[0],	b[1],	color.r, color.g, color.b,  0.0f, 0.0f, 0.0f },
			{ c[0],	c[1],	color.r, color.g, color.b,  1.0f, 1.0f, 0.0f },
			{ d[0],	d[1],	color.r, color.g, color.b,  0.0f, 1.0f, 0.0f },
		};

		Renderer2D::insert(quad);

	}



	void draw() {

		storage.pVertexArray->bind();
		storage.pIndexBuffer->bind();

		glDrawElements(GL_TRIANGLES, storage.pIndexBuffer->count(), GL_UNSIGNED_INT, 0);
		Renderer2D::RendererStats::drawCalls++;

	}

	size_t assignTextureSlot(const Texture& texture) {

		size_t index = 1;

		while (index < storage.mTextureSlots.size() && storage.mTextureSlots[index] && *storage.mTextureSlots[index] != texture)
			index++;

		if (index < storage.mTextureSlots.size() && !storage.mTextureSlots[index])
			storage.mTextureSlots[index] = &texture;

		return index;

	}


};