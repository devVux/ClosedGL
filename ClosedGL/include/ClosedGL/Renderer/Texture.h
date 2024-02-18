#pragma once

class Texture {

	public:

		Texture(size_t index, uint32_t width = 1, uint32_t height = 1): 
			mIndex(index), mWidth(width), mHeight(height) { }
		~Texture();

		void init();

		void setData(void* data);
		void load(const std::string& path);
		
		friend bool operator==(const Texture& left, const Texture& right);
		friend bool operator!=(const Texture& left, const Texture& right);

		float index() const { return mIndex; }
		void setHandle(uint64_t handle) { mHandle = handle; }
		uint64_t handle() const { return mHandle; }
		uint32_t id() const { return mTextureID; }

		float width() const { return (float) mWidth; }
		float height() const { return (float) mHeight; }


	private:

		unsigned int mTextureID;
		uint64_t mHandle;
		float mIndex;

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