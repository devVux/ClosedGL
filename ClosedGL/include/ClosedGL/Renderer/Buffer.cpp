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

void IndexBuffer::push(unsigned int* indices, unsigned int size, GLenum mode) {
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
	for (GLuint i = 0; i < layout.elements().size(); i++) {
		const VertexBufferElement& element = layout.elements().at(i);
		glVertexAttribPointer(i, element.count, element.type, GL_FALSE, layout.stride(), (void*) offset);
		glEnableVertexAttribArray(i);
		offset += element.count * VertexBufferElement::size(element.type);
	}

}

FrameBuffer::FrameBuffer() {
	invalidate();
}

FrameBuffer::~FrameBuffer() {
	glDeleteFramebuffers(1, &mBufferID);
	glDeleteTextures(1, &mColorAttachment);
	glDeleteTextures(1, &mDepthAttachment);
}

void FrameBuffer::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, mBufferID);
}

void FrameBuffer::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::invalidate() {
	
	if (mBufferID != 0) {
		glDeleteFramebuffers(1, &mBufferID);
		glDeleteTextures(1, &mColorAttachment);
		glDeleteTextures(1, &mDepthAttachment);
	}


	glCreateFramebuffers(1, &mBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, mBufferID);


	// Color attachment
	glCreateTextures(GL_TEXTURE_2D, 1, &mColorAttachment);
	glBindTexture(GL_TEXTURE_2D, mColorAttachment);

	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, (uint32_t) mSize.x, (uint32_t) mSize.y);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mColorAttachment, 0);


	// Depth attachment
	glCreateTextures(GL_TEXTURE_2D, 1, &mDepthAttachment);
	glBindTexture(GL_TEXTURE_2D, mDepthAttachment);

	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, (uint32_t) (uint32_t) mSize.x, (uint32_t) mSize.y);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, mDepthAttachment, 0);


	assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE && "Framebuffer is incomplete!");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}
