#include "pch.h"
#include "Renderer.h"

struct VerticesDisposition {
	static constexpr glm::vec4 a { glm::vec4(0.0f, 0.0f, 0.0f, 1.0f) };
	static constexpr glm::vec4 b { glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) };
	static constexpr glm::vec4 c { glm::vec4(1.0f, 1.0f, 0.0f, 1.0f) };
	static constexpr glm::vec4 d { glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) };
};

void Renderer::init() {
	
	mBatch.init();

	pWhiteTexture = new Texture;
	uint32_t white = 0xffffffff;
	pWhiteTexture->setData(&white);
	mTextureSlots[0] = pWhiteTexture;

	pShader = new Shader;
	pShader->fromFile("F:\\dev\\ClosedGL\\ClosedGL\\assets\\shaders\\simple.shader");
	pShader->bind();
	
	int samplers[32];
	for (size_t i = 0; i < 32; i++) {
		glActiveTexture(GL_TEXTURE0 + 0);
		samplers[i] = (int) i;
	}

	pShader->setUniformIntArray("uTextures", samplers, 32);

}

void Renderer::beginScene(const OrthographicCamera& camera) {
	mView = camera.view();
	mProjection = camera.projection();

	pShader->bind();
	pVertexArray->bind();

}

void Renderer::submit(const Shader& shader, const VertexArray& vertexArray) {

	shader.bind();
	shader.setUniformMatrix4("uProj", mProjection);
	shader.setUniformMatrix4("uView", mView);
	shader.setUniformMatrix4("uModel", glm::mat4(1.0f));

	draw(vertexArray);
	
}

void Renderer::endScene() {
	
}


void Renderer::beginBatch(const OrthographicCamera& camera) {
	mProjection = camera.projection();
	mView = camera.view();
	mBatch.begin();

	pShader->bind();
	pShader->setUniformMatrix4("uProj", camera.projection());
	pShader->setUniformMatrix4("uView", camera.view());

	mStats.drawCalls = 0;

}

void Renderer::drawQuad(glm::vec2 position, glm::vec2 size, glm::vec3 color) {

	const glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

	drawQuad(transform);

}

void Renderer::drawQuad(glm::vec2 position, glm::vec2 size, const Texture& texture) {

	size_t index = assignTextureSlot(texture);

	const glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 1.0f)) * 
				glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

	drawQuad(transform);

}

void Renderer::drawQuad(glm::vec2 position, glm::vec2 size, const SubTexture& subTexture) {

	size_t index = assignTextureSlot(subTexture.texture());

	// Subtexture coords
	auto [x, y, w, h] = subTexture.coords();

	// Original texture sizes
	float textWidth = subTexture.texture().width();
	float textHeight = subTexture.texture().height();

	// Normalized subtexture coords
	float subText_x = x / textWidth;
	float subText_y = y / textHeight;
	float subText_w = (x + w) / textWidth;
	float subText_h = (y + h) / textHeight;

	Batch::Polygon quad {
		{ position.x,			position.y,				1.0f, 1.0f, 1.0f,  subText_x, subText_y, (float) index },
		{ position.x + size.x,	position.y,				1.0f, 1.0f, 1.0f,  subText_w, subText_y, (float) index },
		{ position.x + size.x,	position.y + size.y,	1.0f, 1.0f, 1.0f,  subText_w, subText_h, (float) index },
		{ position.x,			position.y + size.y,	1.0f, 1.0f, 1.0f,  subText_x, subText_h, (float) index },
	};

	mBatch.insert(quad);

}

void Renderer::drawQuad(glm::mat4 transform, glm::vec3 color) {
	
	// TODO: export lambda
	const glm::vec3 a = transform * VerticesDisposition::a;
	const glm::vec3 b = transform * VerticesDisposition::b;
	const glm::vec3 c = transform * VerticesDisposition::c;
	const glm::vec3 d = transform * VerticesDisposition::d;

	Batch::Polygon quad {
		{ a[0],	a[1],	color.r, color.g, color.b,  1.0f, 0.0f, 0.0f },
		{ b[0],	b[1],	color.r, color.g, color.b,  0.0f, 0.0f, 0.0f },
		{ c[0],	c[1],	color.r, color.g, color.b,  1.0f, 1.0f, 0.0f },
		{ d[0],	d[1],	color.r, color.g, color.b,  0.0f, 1.0f, 0.0f },
	};

	mBatch.insert(quad);

}

void Renderer::endBatch() {
	
	uint32_t i = 0;
	while (i < 32 && mTextureSlots[i] != nullptr) {
		mTextureSlots[i]->bind(i);
		i++;
	}

	mBatch.end();
	mStats.drawCalls++;

}

void Renderer::draw(const VertexArray& vertexArray) {
	vertexArray.bind();
	glDrawElements(GL_TRIANGLES, vertexArray.indexBuffer().count(), GL_UNSIGNED_INT, 0);
}

size_t Renderer::assignTextureSlot(const Texture& texture) {
	
	size_t index = 1;

	while (index < mTextureSlots.size() && mTextureSlots[index] && *mTextureSlots[index] != texture)
		index++;

	if (index < mTextureSlots.size() && !mTextureSlots[index])
		mTextureSlots[index] = &texture;

	return index;

}

void Renderer::clear(float r, float g, float b) const {
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


