#include "pch.h"
#include "Renderer2D.h"
#include "RenderCommands.h"

#include "ClosedGL/Core/Managers/TextureManager.h"

namespace Renderer2D {

	struct RendererStorage {
		Shader* pShader { nullptr };
		VertexArray* pVertexArray { nullptr };
		VertexBuffer* pBuffer { nullptr };
		IndexBuffer* pIndexBuffer { nullptr };
		uint32_t ssbo { 0 };
		
		unsigned int mCurrentPos { 0 };

	};

	static RendererStorage storage;
	
	void init() {

		storage.pShader = new Shader;
		storage.pVertexArray = new VertexArray;
		storage.pBuffer = new VertexBuffer;
		storage.pIndexBuffer = new IndexBuffer;

		// Batch init
		storage.pVertexArray->bind();


		BufferLayout layout;
		layout.push(GL_FLOAT, 2);
		layout.push(GL_FLOAT, 3);


		storage.pBuffer->push(nullptr, BATCH_CAPACITY * layout.stride(), GL_DYNAMIC_DRAW);
		storage.pBuffer->setLayout(layout);


		storage.pVertexArray->addBuffer(*storage.pBuffer);
		storage.pVertexArray->setIndexBuffer(storage.pIndexBuffer);


		// TODO: support relative imports
		storage.pShader->fromFile("F:\\dev\\ClosedGL\\ClosedGL\\assets\\shaders\\simple.shader");
		storage.pShader->bind();


		//glCreateBuffers(1, &storage.ssbo);
		//glNamedBufferStorage(
		//	storage.ssbo,
		//	sizeof(uint64_t) * TextureManager::size(),
		//	(const void*) TextureManager::handles().data(),
		//	GL_DYNAMIC_STORAGE_BIT
		//);





		static constexpr auto initIndexBufferIndices = [](uint32_t* indices) {
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
		};

		uint32_t indices[BATCH_INDICES];
		initIndexBufferIndices(indices);
		storage.pIndexBuffer->push(indices, BATCH_INDICES * sizeof(uint32_t));

	}

	void insert(const Quad& q) {

		static constexpr auto storageOverflowsWith = [](const Quad& q) {
			return storage.mCurrentPos + q.count() > BATCH_CAPACITY * storage.pBuffer->layout().stride();
		};

		if (storageOverflowsWith(q))
			storage.mCurrentPos = 0;

		storage.pBuffer->insert(q.points.data(), storage.mCurrentPos * sizeof(float), q.size());
		storage.mCurrentPos += q.count();

		RenderCommands::Stats::incrementPolyCount();
	}



	void beginScene(const OrthographicCamera& camera) {

		storage.pShader->bind();
		storage.pShader->setUniformMatrix4("uProj", camera.projection());
		storage.pShader->setUniformMatrix4("uView", camera.view());
		
		storage.pVertexArray->bind();

		storage.mCurrentPos = 0;
		
		RenderCommands::Stats::reset();
	}

	void endScene() {
		draw();
	}

	void drawQuad(glm::vec2 position, glm::vec2 size, glm::vec3 color) {
		
		Quad q;
		q.setPosition({
			{ position[0],				position[1]				},
			{ position[0] + size[0],	position[1]				},
			{ position[0] + size[0],	position[1] + size[1]	},
			{ position[0],				position[1] + size[1]	},
		})
		.setColor(color);
		
		
		insert(q);

	}

	void draw() {

		storage.pVertexArray->bind();
		storage.pIndexBuffer->bind();
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, storage.ssbo);
		
		glDrawElements(
			GL_TRIANGLES,
			storage.pIndexBuffer->count(),
			GL_UNSIGNED_INT,
			0
		);

		RenderCommands::Stats::incrementDrawCalls();

	}

};