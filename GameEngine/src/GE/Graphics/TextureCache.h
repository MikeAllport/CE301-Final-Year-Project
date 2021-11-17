#ifndef GE_TEXTURECACHE
#define GE_TEXTURECACHE

#include "Texture.h"

namespace GE::Graphics
{
	/**
	*
	*/
	class TextureCache
	{
	public:
		/**
		* init's purpose is to pre-load all images from a given directory into its cache
		*/
		static void init(const std::string& path);
		static std::shared_ptr<Texture> getTexture(std::string name);
		static bool addTexture(std::string name, std::shared_ptr<Texture>);
		static inline std::string PATH;
	private:
		static inline boolean initialised = false;
		std::unordered_map<std::string, std::shared_ptr<Texture>> textures;
		TextureCache() : textures() {};
		~TextureCache();
		static TextureCache& getInstance();
		static inline const std::vector<std::string> FILE_TYPES = { ".png" };
	};

}
#endif // !GE_TEXTURECACHE
