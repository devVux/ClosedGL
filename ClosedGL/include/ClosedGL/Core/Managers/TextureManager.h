#pragma once

#include "ClosedGL/Renderer/Texture.h"

#include <array>

class TextureManager {

	public:
		
		~TextureManager() {
			while (!mTextures.empty()) {
				delete mTextures.back();
				mTextures.pop_back();
			}
			while (!mSubTextures.empty()) {
				delete mSubTextures.back();
				mSubTextures.pop_back();
			}
		}
		
		static Texture& create(std::optional<std::string> path) {
			Texture* texture = new Texture(mTextures.size());
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

		static SubTexture& crop(Texture& texture, const Coords& coords) {
			SubTexture* subTexture = new SubTexture(&texture, coords);

			mSubTextures.push_back(subTexture);
			return *subTexture;
		}

		static std::vector<SubTexture> crop(Texture& texture, std::initializer_list<Coords> coords) {
			std::vector<SubTexture> subs(coords.size());
			mSubTextures.reserve(coords.size());

			size_t i = 0;

			for (const Coords& c : coords) {

				SubTexture* text = new SubTexture(&texture, c);
				mSubTextures.push_back(text);
				subs[i] = *text;
				
				i++;
			}

			return subs;
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
		static std::vector<const SubTexture*> mSubTextures;

};