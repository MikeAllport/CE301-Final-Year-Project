#include <gepch.h>
#include "FontRenderer.h"

// code heavily adapted from learnopengl.com
// https://learnopengl.com/In-Practice/Text-Rendering

namespace GE::Graphics
{
	FontRenderer::FontRenderer():
		fontshader(VS, FS),
		vertexBuffer(0),
		indexBuffer(0),
		vertexArray(0),
		quadsDrawn(0)
	{
		// sets up buffers
		createVertexBuffer(vertexBuffer);
		createIndexBuffer(indexBuffer);
		assignVertexLayout(vertexArray, vertexBuffer);
	}


	void FontRenderer::createVertexBuffer(uint32& bufferID)
	{
		glGenBuffers(1, &bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, bufferID);
		glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex) * MAX_QUADS, nullptr, GL_DYNAMIC_COPY);
	}	
	void FontRenderer::createIndexBuffer(uint32& bufferID)
	{
		glGenBuffers(1, &bufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, INDICES_PER_QUAD * MAX_QUADS * sizeof(uint32), nullptr, GL_DYNAMIC_COPY);
	}
	void FontRenderer::assignVertexLayout(uint32& arrayID, uint32& bufferID)
	{
		glGenVertexArrays(1, &arrayID);
		glBindVertexArray(arrayID);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), BUFFER_OFFSET(0));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), BUFFER_OFFSET(2 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glBindVertexArray(0);
	}

	FontRenderer::~FontRenderer()
	{
		delete color;
	}

	FontRenderer& FontRenderer::getInstance()
	{
		static FontRenderer renderer;
		return renderer;
	}

	void FontRenderer::setFont(const char* fp, const char* fn)
	{
		FontRenderer& fr = getInstance();
		fr.atlas = GlyphAtlasCache::getAtlas(fp, fn);
	}

	void FontRenderer::setColor(glm::vec3& color)
	{
		FontRenderer& fr = getInstance();
		if (fr.color != nullptr)
			delete fr.color;
		fr.color = new glm::vec3(color);
	}

	void FontRenderer::begin()
	{
		fontshader.bind();
	}

	void FontRenderer::end()
	{
		this->FontRenderer::render();
		vertices.clear();
		indices.clear();
		quadsDrawn = 0;
		fontshader.unbind();
	}

	void FontRenderer::render()
	{
		fontshader.bind();
		fontshader.setUniform3fv("u_col", &color->r);
		atlas->text->bind();

		// bind buffers
		glBindVertexArray(vertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

		// sends vertex buffer data
		glInvalidateBufferData(vertexBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * 4 * quadsDrawn, &vertices[0].pos[0]);

		// sends index buffer data
		glInvalidateBufferData(indexBuffer);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, quadsDrawn * INDICES_PER_QUAD * sizeof(uint32), &indices[0]);

		// draw call
		glDrawElements(GL_TRIANGLES, quadsDrawn * INDICES_PER_QUAD, GL_UNSIGNED_INT, 0);

		// unbinds
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void FontRenderer::renderText(const char* text, float x, float y, float scale)
	{
		if (atlas == nullptr || color == nullptr || atlas == NULL)
		{
			GE_ERROR("{} -> font atlas and font color has not been initialized");
			__debugbreak();
			return;
		}
		float scale2 = scale / (float)atlas->height;

		for (const char* ch = text; *ch; ch++)
		{
			Glyph& g = atlas->characters[*ch];
			// gets positional attributes including the offsets
			float xPos = x + g.xOffset * scale2;
			float yPos = y - (g.sizeH - g.yOffset) * scale2;
			float width = g.sizeW * scale2;
			float height = g.sizeH * scale2;

			x += g.xAdvance * scale2;
			y += g.yAdvance * scale2;

			if (!g.sizeW || !g.sizeH)
				continue;

			// sets up vertices and indices
			Vertex vertex[4] = {
				{  xPos			, yPos + height	,  g.xText		, g.yText	 },
				{  xPos + width	, yPos + height	,  g.xTextMax	, g.yText	 },
				{  xPos 		, yPos			,  g.xText		, g.yTextMax },
				{  xPos + width	, yPos			,  g.xTextMax	, g.yTextMax }
			};		  

			int i;

			for (i = 0; i < 4; i++)
				vertices.push_back(vertex[i]);

			int offset = quadsDrawn * 4;
			uint32 arr[6] =
			{
				0 + offset,	1 + offset,	2 + offset,
				2 + offset,	3 + offset,	1 + offset
			};

			for (i = 0; i < 6; i++)
				indices.push_back(arr[i]);

			++quadsDrawn;
		}
	}

}