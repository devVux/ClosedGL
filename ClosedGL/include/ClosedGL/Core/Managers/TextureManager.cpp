#include "pch.h"
#include "TextureManager.h"

Texture& TextureManager::create(const std::optional<std::string>& path) {
	Ref<Texture> texture = makeRef<Texture>((uint32_t) mTextures.size());
	texture->init();

	if (path)
		texture->load(path.value());
	else {
		uint32_t white = 0xffffffff;
		texture->setData(&white);
	}

	uint64_t handle = glGetTextureHandleARB(texture->id());
	assert(handle != 0 && "Errore");

	texture->setHandle(handle);
	glMakeTextureHandleResidentARB(handle);

	mTextures.push_back(texture);
	return *texture;
}

void TextureManager::resident() {
	for (auto texture : mTextures)
		glMakeTextureHandleResidentARB(texture->handle());
}

void TextureManager::unresident() {
	for (auto& texture : mTextures)
		glMakeTextureHandleNonResidentARB(texture->handle());
}
