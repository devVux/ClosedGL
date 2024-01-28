#pragma once

#include <string>

class Texture {

	public:

		Texture(uint32_t width = 1, uint32_t height = 1);
		Texture(const std::string& path);
		~Texture();

		void bind(unsigned int slot = 0) const;
		void unbind() const;

		void setData(void* data);
		void load(const std::string& path);
		
		friend bool operator==(const Texture& left, const Texture& right);
		friend bool operator!=(const Texture& left, const Texture& right);

		uint32_t id() const { return mTextureID; }
		float width() const { return (float) mWidth; }
		float height() const { return (float) mHeight; }

	private:
		
		void init();

	private:

		unsigned int mTextureID;
		int mWidth { 1 };
		int mHeight { 1 };
		int mBitsPerPixel;

		unsigned char* mLocalBuffer;

};

class SubTexture {
 
	public:
		
		SubTexture(Texture* texture, float x, float y, float size);
		SubTexture(Texture* texture, float x, float y, float width, float height);

		const Texture& texture() const { return *pTexture; }

		Coords coords() const { return mCoords; }

	private:

		Texture* pTexture;
		Coords mCoords;

};