#pragma once

typedef unsigned int ID;

#include "pch.h"

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

		size_t size() const { return mStride * mElements.size(); }
		
		uint32_t stride() const { return mStride; }
		const std::vector<VertexBufferElement>& elements() const { return mElements; }

	private:

		uint32_t mStride { 0 };
		std::vector<VertexBufferElement> mElements;

};

class VertexBuffer {

	public:
	
		VertexBuffer();
		VertexBuffer(const VertexBuffer& other);
		~VertexBuffer();

		void bind() const;
		void unbind() const;

		void push(const float* vertices, unsigned int size, GLenum mode = GL_STATIC_DRAW) const;
		void insert(const float* vertices, unsigned int offset, unsigned int size) const;
		
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
		~IndexBuffer();

		void bind() const;
		void unbind() const;

		void push(const unsigned int* indices, unsigned int size, GLenum mode = GL_STATIC_DRAW);
		void insert(const unsigned int* indices, unsigned int offset, unsigned int size);
	
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

		IndexBuffer* mIndexBuffer { 0 };

};
