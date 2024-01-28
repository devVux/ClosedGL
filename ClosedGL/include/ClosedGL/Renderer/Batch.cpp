#include "pch.h"
#include "Batch.h"

#include "Renderer.h"


void Batch::init() {
	
	assert(sInitialized && "init() already called!");

	mVertexArray = new VertexArray;
	mVertexArray->bind();

	mBuffer = new VertexBuffer;
	mBuffer->push(nullptr, BATCH_DATA * sizeof(float), GL_DYNAMIC_DRAW);

	BufferLayout layout;
	layout.push(GL_FLOAT, 2);
	layout.push(GL_FLOAT, 3);
	layout.push(GL_FLOAT, 2);
	layout.push(GL_FLOAT, 1);
	mBuffer->setLayout(layout);

	mIndexBuffer = new IndexBuffer;
	
	mVertexArray->addBuffer(*mBuffer);
	mVertexArray->setIndexBuffer(mIndexBuffer);

}

void Batch::begin() {
	
	mCurrentPos = 0;

	uint32_t offset = 0;
	for (size_t i = 0; i < BATCH_INDICES; i += 6) {
		
		mIndices[i + 0] = offset + 0;
		mIndices[i + 1] = offset + 1;
		mIndices[i + 2] = offset + 2;

		mIndices[i + 3] = offset + 0;
		mIndices[i + 4] = offset + 2;
		mIndices[i + 5] = offset + 3;

		offset += 4;

	}

	mIndexBuffer->push(mIndices, BATCH_INDICES * sizeof(uint32_t));

}

void Batch::push(float* data, unsigned int count) {

	if (mCurrentPos + count > BATCH_CAPACITY * layoutSize) {
		flush();
		draw();
	}

	for (size_t i = 0; i < count; i += layoutSize) {

		for (size_t j = 0; j < layoutSize; j++)
			mData[mCurrentPos + j] = data[j + 0];

		mCurrentPos += layoutSize;

	}

}

void Batch::insert(const Polygon& p) {

	if (mCurrentPos + p.count > BATCH_CAPACITY * layoutSize)
		mCurrentPos = 0;

	mBuffer->insert(p.data, mCurrentPos * sizeof(float), p.count * sizeof(float));
	mCurrentPos += p.count;

}

void Batch::insert(float* data, uint32_t count) {

	if (mCurrentPos + count > BATCH_CAPACITY * layoutSize)
		mCurrentPos = 0;

	mBuffer->insert(data, mCurrentPos * sizeof(float), count * sizeof(float));
	mCurrentPos += count;

}

void Batch::flush() {
	mBuffer->push(mData, BATCH_DATA * sizeof(float));
	mCurrentPos = 0;
}

void Batch::end() {
	//flush();
	draw();
}

void Batch::draw() {

	mVertexArray->bind();
	mIndexBuffer->bind();

	glDrawElements(GL_TRIANGLES, mIndexBuffer->count(), GL_UNSIGNED_INT, 0);
	
}

