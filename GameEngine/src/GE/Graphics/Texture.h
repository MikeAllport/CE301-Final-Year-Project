#ifndef GE_TEXTURE
#define GE_TEXTURE
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include "glad/glad.h"

namespace GE::Graphics
{
	/**
	* Texture's purpose is to load a texture from a given filename via stb_image, and call
	* gl functions to load textures into GPU memory. These instances can then be bound before
	* a draw call to activate a sampler2D uniform of the given texture
	*/
	class Texture
	{
	public:
		Texture(std::string fp);
		Texture(int width, int height, std::string& fn);
		~Texture();

		void bind() const;
		void bind(const uint32 slot) const;
		void unbind() const;
		void enableBindlessTexture();
		bool hasLoaded();
		inline int getWidth() const { return width; };
		inline int getHeight() const { return height; };
		inline uint32 getID() const { return textID; };
		inline uint64 getHandle() { enableBindlessTexture(); return handle; };
		inline const char* getName() const { return (path + fn).c_str(); }

		int operator==(const Texture& other) const;
		friend std::ostream& operator<<(std::ostream& o, const Texture& text);
	private:
		bool isBindless = false;
		unsigned int textID;
		std::string fn;
		std::string path;
		bool loaded = true;
		unsigned char* locationBuf;
		int width, height, bitpp;
		uint64 handle;
	};
}
#endif // !GE_TEXTURE
