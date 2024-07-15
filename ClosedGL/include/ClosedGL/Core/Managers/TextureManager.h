#pragma once

#include "ClosedGL/Renderer/Texture.h"

class TextureManager {

	public:
		
		Texture& create(const std::optional<std::string>& path);

		/*
		SubTexture& crop(Texture& texture, const Coords& coords) {
			SubTexture* subTexture = new SubTexture(&texture, coords);

			mSubTextures.push_back(subTexture);
			return *subTexture;
		}

		std::vector<SubTexture> crop(Texture& texture, std::initializer_list<Coords> coords) {
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
		*/

		size_t size() {
			return mTextures.size();
		}
		
		const auto& textures() {
			return mTextures;
		}

		std::vector<uint64_t> handles() {
			std::vector<uint64_t> h(mTextures.size());

			for (size_t i = 0; i < mTextures.size(); i++) 
				h[i] = mTextures[i]->handle();
			
			return h;
		}

		void resident();

		void unresident();

			

	private:

		std::vector<Ref<Texture>> mTextures;

};