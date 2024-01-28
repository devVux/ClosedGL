#include "pch.h"
#include "Buffer.h"


VertexBuffer::VertexBuffer() {
	glCreateBuffers(1, &mBufferId);
}

VertexBuffer::VertexBuffer(const VertexBuffer& other): mBufferId(other.mBufferId), mLayout(other.mLayout) {
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &mBufferId);
}

void VertexBuffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, mBufferId);
}

void VertexBuffer::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::push(float* vertices, unsigned int size, GLenum mode) const {
	glBindBuffer(GL_ARRAY_BUFFER, mBufferId);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, mode);
}

void VertexBuffer::insert(float* vertices, unsigned int offset, unsigned int size) const {
	glBindBuffer(GL_ARRAY_BUFFER, mBufferId);
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices);
}





IndexBuffer::IndexBuffer() {
	glCreateBuffers(1, &mBufferId);
}

//IndexBuffer::IndexBuffer(const IndexBuffer& other): mBufferId(other.mBufferId), mCount(other.mCount) {
//
//}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &mBufferId);
#ifdef _DEBUG
	delete[] pData;
#endif
}

void IndexBuffer::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferId);
}

void IndexBuffer::unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::insert(unsigned int* indices, unsigned int offset, unsigned int size) {
	glBindBuffer(GL_ARRAY_BUFFER, mBufferId);
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, indices);
}

void IndexBuffer::push(unsigned int* indices, unsigned int size, GLenum mode /*= GL_DYNAMIC_DRAW*/) {
	mCount = size / sizeof(GLuint);
	#ifdef _DEBUG
		pData = new unsigned int[mCount];
		for (size_t i = 0; i < mCount; i++)
			pData[i] = indices[i];
	#endif
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, mode);
}




VertexArray::VertexArray() {
	glCreateVertexArrays(1, &mArrayId);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &mArrayId);
}

void VertexArray::bind() const {
	glBindVertexArray(mArrayId);
}

void VertexArray::unbind() const {
	glBindVertexArray(0);
}

void VertexArray::addBuffer(const VertexBuffer& vertexBuffer) {

	const BufferLayout& layout = vertexBuffer.layout();

	vertexBuffer.bind();

	unsigned int offset = 0;
	for (size_t i = 0; i < layout.elements().size(); i++) {
		const VertexBufferElement& element = layout.elements().at(i);
		glVertexAttribPointer(i, element.count, element.type, GL_FALSE, layout.stride(), (void*) offset);
		glEnableVertexAttribArray(i);
		offset += element.count * VertexBufferElement::size(element.type);
	}

}
