#include "pch.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(uint32_t width, uint32_t height): mWidth(width), mHeight(height) {
	init();

	unsigned int whiteColor = 0xffffffff;
	setData(&whiteColor);

}

Texture::Texture(const std::string& path) {
	init();
	load(path);
}

Texture::~Texture() {
	glDeleteTextures(1, &mTextureID);
}

void Texture::bind(unsigned int slot) const {
	glBindTextureUnit(slot, mTextureID);
}

void Texture::unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::setData(void* data) {
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

void Texture::load(const std::string& path) {

	mLocalBuffer = stbi_load(path.c_str(), &mWidth, &mHeight, &mBitsPerPixel, 4);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mLocalBuffer);

	if (mLocalBuffer)
		stbi_image_free(mLocalBuffer);

}

void Texture::init() {
	stbi_set_flip_vertically_on_load(1);

	glCreateTextures(GL_TEXTURE_2D, 1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	//glTextureStorage2D(mTextureID, 1, GL_RGBA8, mWidth, mHeight);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

}


bool operator==(const Texture& left, const Texture& right) { return left.mTextureID == right.mTextureID; }
bool operator!=(const Texture& left, const Texture& right) { return !(left == right); }





SubTexture::SubTexture(Texture* texture, float x, float y, float size): 
	pTexture(texture), mCoords{ x, y, size, size } {
}

SubTexture::SubTexture(Texture* texture, float x, float y, float width, float height):
	pTexture(texture), mCoords { x, y, width, height } {

}