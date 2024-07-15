#pragma once


class Texture {

	public:

		Texture(uint32_t index, int width = 1, int height = 1): 
			mIndex(static_cast<float>(index)), mCoords {0, 0, width, height} { }
		~Texture();

		void init();

		void setData(void* data);
		void load(const std::string& path);

		//Texture cutOut(Coords coords);
		//std::vector<SubTexture> cutOut(const std::initializer_list<Coords>& coords);
		
		float index() const { return mIndex; }
		void setHandle(uint64_t handle) { mHandle = handle; }
		uint64_t handle() const { return mHandle; }
		uint32_t id() const { return mTextureID; }

		int width() const { return mCoords.width; }
		int height() const { return mCoords.height; }

		bool operator<=>(const Texture& other) const { return mTextureID == other.mTextureID && mIndex == other.mIndex; }


	private:

		uint32_t mTextureID { 0 };
		uint64_t mHandle { 0 };
		float mIndex;

		Coords<int> mCoords;
		int mBitsPerPixel { 3 };

		unsigned char* mLocalBuffer { nullptr };

};

