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
			Texture* texture = new Texture(mTextures.size());
			texture->init();

			uint32_t white = 0xffffffff;
			texture->setData(&white);

			uint64_t handle = glGetTextureHandleARB(texture->id());
			assert(handle != 0 && "Errore");

			texture->setHandle(handle);

			mTextures.push_back(texture);
			return *texture;
		}
		
		static Texture& create(const std::string& path) {
			Texture* texture = new Texture(mTextures.size());
			texture->init();
			texture->load(path);

			uint64_t handle = glGetTextureHandleARB(texture->id());
			assert(handle != 0 && "Errore");

			texture->setHandle(handle);


			mTextures.push_back(texture);
			return *texture;
		}

		static size_t size() {
			return mTextures.size();
		}
		
		static const auto& textures() {
			return mTextures;
		}

		static std::vector<uint64_t> handles() {
			std::vector<uint64_t> h(mTextures.size());

			for (size_t i = 0; i < mTextures.size(); i++) 
				h[i] = mTextures[i]->handle();
			
			return h;
		}

		static void resident() {
			for (auto texture : mTextures)
				glMakeTextureHandleResidentARB(texture->handle());
		}

		static void unresident() {
			for (auto& texture : mTextures)
				glMakeTextureHandleNonResidentARB(texture->handle());
		}

			

	private:

		static std::vector<const Texture*> mTextures;

};