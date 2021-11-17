#include <gepch.h>
#include "FontLoader.h"

// code heavily adapted from learnopengl.com
// https://learnopengl.com/In-Practice/Text-Rendering

namespace GE::Graphics::Fonts
{
	GlyphAtlas FontLoader::createAtlas(const char* fp, const char* fn)
	{
		FontLoader fl(fp, fn);
		return fl.atlas;
	}

	FontLoader::FontLoader(const char* fp, const char* fn)
	{
		atlas.name = std::string(fn);
		absPath = std::string(fp) + std::string(fn);
		initFT();
		loadAtlasSizes();
		loadTexture();
	}

	void FontLoader::initFT()
	{
		if (FT_Init_FreeType(&ft)) {
			GE_ERROR("FontLoader -> Could not init freetype library");
			exit(1);
		}
		if (FT_New_Face(ft, absPath.c_str() , 0, &face)) {
			GE_ERROR("FontLoader -> Could not open font");
			exit(1);
		}
		FT_Set_Pixel_Sizes(face, 0, FONT_SIZE); // by leaving width size 0, freetype automatically sets width
	}
	
	void FontLoader::loadAtlasSizes()
	{
		FT_GlyphSlot g = face->glyph;
		for (int i = 32; i < 128; i++) {
			if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
				GE_ERROR("Loading character {} failed!", i);
				exit(1);
			}
			atlasWidth += g->bitmap.width;
			atlasHeight = std::max(atlasHeight, g->bitmap.rows);
		}
		atlas.width = atlasWidth;
		atlas.height = atlasHeight;
		atlas.fontSize = FONT_SIZE;
	}

	void FontLoader::loadTexture()
	{
		FT_GlyphSlot g = face->glyph;
		std::shared_ptr<Texture> text(new Texture(atlasWidth, atlasHeight, atlas.name));
		text->bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, (int)atlasWidth, (int)atlasHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
		float x = 0;
		// extracts all of the ascii characters glyph information & uploads data to buffer
		Glyph glyph;
		float xTexOffset = 1 / (float)(atlasWidth * 2), yTexOffset = 1 / (float)(atlasHeight * 2);
		for (int i = 32; i < 128; i++) {
			if (FT_Load_Char(face, i, FT_LOAD_RENDER))
				continue;

			uint32 rowStartPos = g->metrics.horiBearingY >> 6;
			uint32 colStartPos = g->metrics.horiBearingX >> 6;
			unsigned char** newBuff = new unsigned char* [g->bitmap.rows];
			glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, g->bitmap.width, g->bitmap.rows, GL_ALPHA, GL_UNSIGNED_BYTE, g->bitmap.buffer);
			
			glyph.xAdvance = g->advance.x >> 6;
			glyph.yAdvance = g->advance.y >> 6;
			glyph.sizeW = g->bitmap.width;
			glyph.sizeH = g->bitmap.rows;
			glyph.xOffset = g->bitmap_left;
			glyph.yOffset = g->bitmap_top;
			glyph.xText = (x / (float)atlasWidth) + xTexOffset;
			glyph.xTextMax = ((x + g->bitmap.width) / (float)atlasWidth) - xTexOffset;
			glyph.yText = 0 + yTexOffset;
			glyph.yTextMax = (g->bitmap.rows / (float)atlasHeight) - yTexOffset;
			atlas.characters[i] = glyph;
			x += g->bitmap.width;
		}
		atlas.text = text;
		GE::Graphics::TextureCache::addTexture(atlas.name, text);
	}

	GlyphAtlas* GlyphAtlasCache::getAtlas(const char* fp, const char* fn)
	{
		GlyphAtlasCache& cache = getInstance();
		std::string name = std::string(fn);
		if (!cache.cache[name])
		{
			GlyphAtlas* atlas = new GlyphAtlas(FontLoader::createAtlas(fp, fn));
			cache.cache[name] = atlas;
		}
		return cache.cache[name];
	}

	GlyphAtlasCache& GlyphAtlasCache::getInstance()
	{
		static GlyphAtlasCache cache;
		return cache;
	}

	GlyphAtlasCache::~GlyphAtlasCache()
	{
		for (auto i : cache)
		{
			delete i.second;
		}
	}
}