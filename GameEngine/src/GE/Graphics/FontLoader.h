#ifndef GE_FONT_FL
#define GE_FONTS_FL

#include <ft2build.h>
#include FT_FREETYPE_H
#include <GE/Graphics/Texture.h>
#include <GE/Graphics/TextureCache.h>

namespace GE::Graphics::Fonts
{
	/**
	* Glyph's purpose is to hold typical information about a character glyph from a given
	* texture atlas
	*/
	struct Glyph
	{
		uint32 id;
		double xText, xTextMax, yText, yTextMax, xOffset, yOffset,
			sizeW, sizeH, xAdvance, yAdvance;
	};

	/**
	* GlphAtlas is a struct containing a map of glyphs, associated to ascii char int value
	* and stores to atlas's toal width and height information
	*/
	struct GlyphAtlas
	{
		std::unordered_map<int, Glyph> characters;
		std::string name;
		std::shared_ptr<Texture> text;
		uint32 width, height, fontSize;
	};

	/**
	* FontAtlasCache is as it says, a simple cached maps of loaded GlyphAtlas's. If a requested
	* fn&fp does not exist, FontLoader is called to open the file and extract all glyph/glyph atlas
	* data
	*/
	class GlyphAtlasCache
	{
	public:
		static GlyphAtlas* getAtlas(const char* fp, const char* fn);
	private:
		~GlyphAtlasCache();
		static GlyphAtlasCache& getInstance();
		std::unordered_map<std::string, GlyphAtlas*> cache;
	};

	/**
	* FontLoader's purpose is to take a filename and filepath, load the file into a buffer and 
	* use FreeType to extract individual glyph information into a Glyph atlas. This is a static
	* class meaning initialization is done in the createAtlas method and destroyed when extraction
	* is complete. No external classes can instantiate this class
	*/
	class FontLoader
	{
	public:
		/**
		* The only public method which instantiates itself to extract information returning the
		* Glyph atlas or causing the application to exit if there are file issues
		*
		* TODO: Return a default font if any error occurs
		*/
		static GlyphAtlas createAtlas(const char* fp, const char* fn);
	private:
		FontLoader(const char* fp, const char* fn);
		void initFT();
		void loadAtlasSizes();
		void loadTexture();
		GlyphAtlas atlas;
		uint32 atlasWidth = 0, atlasHeight = 0;
		std::string absPath;
		FT_Library ft;
		FT_Face face;
		const uint32 FONT_SIZE = 70;
	};
}

#endif