#include "gepch.h"
#include "TextureCache.h"
#include <filesystem>

namespace GE::Graphics
{
	TextureCache::~TextureCache()
	{
	}

	void TextureCache::init(const std::string& path)
	{
		TextureCache::PATH = path;
		initialised = true;
		for (auto& it: std::filesystem::recursive_directory_iterator(PATH))
		{
			auto& extension = it.path().extension();
			boolean typeCorrect = false;
			for (auto fileType : FILE_TYPES)
			{
				if (extension == fileType)
					typeCorrect = true;
				if (typeCorrect)
				{
					getTexture(it.path().filename().string());
				}
			}
		}
	}

	std::shared_ptr<Texture> TextureCache::getTexture(std::string name)
	{
		TextureCache& tc = getInstance();
		if (!initialised)
		{
			GE_ERROR("{} getTexture called on an uninitatialized texture cache", typeid(tc).name());
			exit(1);
		}
		if (!tc.textures[name])
		{
			std::shared_ptr<Texture> text(new Texture(name));
			if (text->hasLoaded())
				tc.textures[name] = text;
		}
		return tc.textures[name];
	}

	TextureCache& TextureCache::getInstance()
	{
		static TextureCache instance;
		return instance;
	}

	bool TextureCache::addTexture(std::string name, std::shared_ptr<Texture> text)
	{
		TextureCache& tc = TextureCache::getInstance();
		if (!tc.textures[name])
		{
			tc.textures[name] = text;
			return true;
		}
		return false;
	}
}