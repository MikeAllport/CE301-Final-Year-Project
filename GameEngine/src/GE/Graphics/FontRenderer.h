#ifndef GE_FONT_RENDERER
#define GE_FONT_RENDERER

#include <gepch.h>
#include <iostream>
#include <fstream>
#include <GE/Graphics/FontLoader.h>
#include <GE/Graphics/Shader.h>

namespace GE::Graphics
{
	using namespace Fonts;

	/**
	* FontRenderer's purpose is as a singleton class, meaning inatantiation is done by the class
	* and only 1 instance can be created. This is a state machine which requires setting up of
	* the font and font's color externally before rendering by setFont and setColor methods.
	*
	* Once Font and Color has been set up, caller class must use begin() and end() methods 
	* in render cycle and subsequentially call renderText to render a string to the screen.
	* It renders by adding the vertices and indices to the local vector list when renderText
	* is called, and when end() is called it renders everything in these lists and empties
	*/
	class FontRenderer
	{
	public:
		/**
		* static method which takes a file path and filename and loads the glyph atlas using
		* the FontLoader class
		*
		* args:
		*	const char* fp - The file path to use
		*	const char* fn - the file name to use
		* returns:
		*	N/A
		*/
		static void setFont(const char* fp, const char* fn);

		/**
		* static method which sets the color of font to use for each render
		*
		* args:
		*	glm::vec3& color - the vector for color to use, no alpha channel
		* returns:
		*	N/A
		*/
		static void setColor(glm::vec3& color);

		/**
		* begin's purpose is to initialize gl required methods for a draw call
		*/
		void begin();

		/**
		* end's purpose is to flush and send the vertices and indexes to the gpu by
		* calling render and resetting the lists
		*/
		void end();

		/**
		* renderText's purpose is to take a cstring, position, and size, and add it to
		* the buffer of things to be rendered
		*/
		void renderText(const char* text, float x, float y, float scale);

		/**
		* singledton method to instantiate static instance
		*/
		static FontRenderer& getInstance();
		/**
		* send the vertice and indice data to the buffers and renders
		*/
		~FontRenderer();
	private:

		FontRenderer();
		void render();
		void createIndexBuffer(uint32& bufferID);
		void createVertexBuffer(uint32& bufferID);
		void assignVertexLayout(uint32& arrayID, uint32& bufferID);

		/**
		* Simple vertice to contain x/y position and texture position
		*/
		struct Vertex
		{
			float pos[2];
			float textPos[2];
		};

		/**
		* local variables
		* atlas - the font to be used
		* color - the color to be used
		* etc...
		*/
		GlyphAtlas* atlas = nullptr;
		glm::vec3* color = nullptr;
		Shader fontshader;
		uint32 
			vertexBuffer,
			vertexArray,
			indexBuffer;

		/**
		* The buffers of vertices and indices and count of characters drawn
		*/
		std::vector<Vertex> vertices;
		std::vector<uint32> indices;
		int quadsDrawn;

		static const int INDICES_PER_QUAD = 6, MAX_QUADS = 10000;
		inline static const std::string 
			VS = "FontVertex.shader",
			FS = "FontFragment.shader";
	};


}
#endif