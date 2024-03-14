#pragma once

typedef unsigned int ID;

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>

struct VertexBufferElement {
	GLenum type;
	unsigned int count;
	GLboolean normalized;

	static unsigned int size(unsigned int type) {
		switch (type) {
			default:
			case GL_FLOAT: return 4;
		}
	}

};

class BufferLayout {

	public:

		void push(GLenum type, unsigned int count) {
			mElements.push_back({ type, count, GL_FALSE });
			mStride += count * VertexBufferElement::size(type);
		}

		//unsigned int size() const { return mStride * mElements.size(); }
		
		unsigned int stride() const { return mStride; }
		const std::vector<VertexBufferElement>& elements() const { return mElements; }

	private:

		unsigned int mStride { 0 };
		std::vector<VertexBufferElement> mElements;

};

class VertexBuffer {

	public:
	
		VertexBuffer();
		VertexBuffer(const VertexBuffer& other);
		~VertexBuffer();

		void bind() const;
		void unbind() const;

		void push(float* vertices, unsigned int size, GLenum mode = GL_STATIC_DRAW) const;
		void insert(float* vertices, unsigned int offset, unsigned int size) const;
		
		void clear();

		void setLayout(const BufferLayout& layout) { mLayout = layout; }
		BufferLayout layout() const { return mLayout; }

		ID id() const { return mBufferId; }

	private:

		ID mBufferId;

		BufferLayout mLayout;

};

class IndexBuffer {

	public:

		IndexBuffer();
		//IndexBuffer(const IndexBuffer& other);
		~IndexBuffer();

		void bind() const;
		void unbind() const;

		void push(unsigned int* indices, unsigned int size, GLenum mode = GL_STATIC_DRAW);
		void insert(unsigned int* indices, unsigned int offset, unsigned int size);

		unsigned int count() const { return mCount; }
		#ifdef _DEBUG
			unsigned int* data() const { return pData; }
		#endif

		ID id() const { return mBufferId; }

	private:

		ID mBufferId;

		unsigned int mCount;

		#ifdef _DEBUG
			unsigned int* pData;
		#endif

};





class VertexArray {
	
	public:

		VertexArray();
		~VertexArray();

		void bind() const;
		void unbind() const;

		void addBuffer(const VertexBuffer& vertexBuffer);

		void setIndexBuffer(IndexBuffer* buffer) { mIndexBuffer = buffer; }
		const IndexBuffer& indexBuffer() const { return *mIndexBuffer; }

		ID id() const { return mArrayId; }

	private:

		ID mArrayId;

		IndexBuffer* mIndexBuffer;

};


class FrameBuffer {

	public:

		FrameBuffer();
		~FrameBuffer();

		void bind();
		void unbind();

		void invalidate();

		ID id() const { return mBufferID; }
		glm::vec2 size() const { return mSize; }
		float width() const { return mSize.x; }
		float height() const { return mSize.y; }

		void resize(glm::vec2 size) {
			mSize = size;
			invalidate();
		}

		uint32_t colorAttachment() const { return mColorAttachment; }

	private:

		ID mBufferID { 0 };

		glm::vec2 mSize { 1, 1 };

		uint32_t mColorAttachment;
		uint32_t mDepthAttachment;

};