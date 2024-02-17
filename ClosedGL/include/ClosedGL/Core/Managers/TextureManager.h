#pragma once

#include "ClosedGL/Renderer/Texture.h"

#include <array>

class TextureManager {

	public:
		
		~TextureManager() {
			for (const auto& texture : mTextures)
				delete texture;
		}

		static Texture& create() {
			Texture* texture = new Texture;
			texture->init();
			
			//texture->handle = glGetTextureHandleARB(texture->id());
			assert(texture->handle != 0 && "Errore");


			mTextures.push_back(texture);
			return *texture;
		}
		
		static Texture& create(const std::string& path) {
			Texture* texture = new Texture;
			texture->init();
			texture->load(path);

			glBindTexture(GL_TEXTURE_2D, texture->id());
			texture->handle = glGetTextureHandleARB(texture->id());
			//assert(texture->handle != 0 && "Errore");


			mTextures.push_back(texture);
			return *texture;
		}

		static size_t size() {
			return mTextures.size();
		}
		
		static const auto& textures() {
			return mTextures;
		}


		static void resident() {
			for (auto texture : mTextures)
				glMakeTextureHandleResidentARB(texture->handle);
		}

		static void unresident() {
			for (auto& texture : mTextures)
				glMakeTextureHandleNonResidentARB(texture->handle);
		}

		static void bindAll() {
			size_t i = 0;
			while (i < mTextures.size() && mTextures[i] != nullptr)
				mTextures[i++]->bind();
		}

		//static uint32_t assignSlotTo(const Texture& texture) {

		//	uint32_t index = 0;

		//	while (index < mTextures.size() && mTextures[index] != nullptr)
		//		index++;

		//	// TODO: handle case when there are no texture units available
		//	if (index < mTextures.size()) {
		//		mTextures[index] = &texture;
		//		return index;
		//	} 
		//	else
		//		return -1;

		//}
			
		//static uint32_t slotOf(const Texture& texture) {

		//	// index 0 is the white texture
		//	uint32_t index = 0;

		//	const auto& are_the_same = [](const Texture* a, const Texture& b) {
		//		return a != nullptr && *a == b;
		//	};

		//	while (index < mTextures.size() && !are_the_same(mTextures[index], texture))
		//		index++;

		//	// TODO: handle case when there are no texture units available
		//	return index < mTextures.size() ? index : -1;

		//}


	private:

		static std::vector<const Texture*> mTextures;

};