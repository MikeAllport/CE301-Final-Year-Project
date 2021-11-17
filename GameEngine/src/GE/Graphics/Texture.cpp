#include "gepch.h"
#include "Texture.h"

#include "stb_image.h"
#include "TextureCache.h"

namespace GE::Graphics
{

	Texture::Texture(std::string fn) :
		fn(fn), textID(0), locationBuf(nullptr), width(0), height(0), bitpp(0),
		handle(0)
	{
		path = TextureCache::PATH;
		std::string load(path + fn);
		stbi_set_flip_vertically_on_load(0);
		locationBuf = stbi_load(load.c_str(), &width, &height, &bitpp, 4);

		if (locationBuf == nullptr)
		{
			GE_WARN("Error loading image: {0}", path + fn);
			loaded = false;
			return;
		}
		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &textID);
		glBindTexture(GL_TEXTURE_2D, textID);

		GE_INFO("Texture loaded {0} to textId {1}", path + fn, textID);

		// set texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, locationBuf);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(locationBuf);
	}

	Texture::Texture(int width, int height, std::string& fn):
		fn(fn), textID(0), locationBuf(nullptr), width(width), height(height), bitpp(0),
		handle(0)
	{
		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &textID);
		glBindTexture(GL_TEXTURE_2D, textID);
	}

	bool Texture::hasLoaded()
	{
		return loaded;
	}

	Texture::~Texture()
	{
	}

	void Texture::enableBindlessTexture()
	{
		if (!isBindless)
		{
			handle = glGetTextureHandleARB(textID);
			glMakeTextureHandleResidentARB(handle);
			isBindless = true;
		}
	}
	void Texture::bind() const
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textID);
	}

	void Texture::bind(const uint32 slot) const
	{
		glBindTextureUnit(slot, textID);
	}

	void Texture::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	int Texture::operator==(const Texture& other) const
	{
		return textID == other.textID;
	}

	std::ostream& operator<<(std::ostream& o, const Texture& text)
	{
		o << "I am a texture of " << text.path << text.fn << std::endl;
		return o;
	}

}