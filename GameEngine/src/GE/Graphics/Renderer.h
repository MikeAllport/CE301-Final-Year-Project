#ifndef GE_RENDERER
#define GE_RENDERER

#include <gepch.h>
#include <GE/Graphics/Shader.h>
#include <GE/Graphics/Texture.h>
#include <GE/Graphics/TextureCache.h>

namespace GE::Graphics
{
	class Renderer
	{
	public:
		/**
		* TexturePosition's purpose is to contain the standard positions for a 1x1 size texture
		*/
		struct TexturePosition
		{
			glm::fvec2 arr[4] =
			{
				{ 0.0f, 0.0f },
				{ 1.0f, 0.0f },
				{ 1.0f, 1.0f },
				{ 0.0f, 1.0f }
			};
		};

		Renderer(std::string vertexShader, std::string fragShader);
		~Renderer();

		/**
		* Following methods are the basic methods a renderer should implement to render quads to screen
		*/
		virtual void drawQuadTextured(std::shared_ptr<Texture>, TexturePosition& pos = TexturePosition()) = 0; // creates a quad2d and calls render
		virtual void drawQuadColored(glm::vec4 color) = 0;
		virtual void drawStaticQuadTextured(std::shared_ptr<Texture>, TexturePosition& pos = TexturePosition()) = 0; // creates a quad2d and calls render
		virtual void drawStaticQuadColored(glm::vec4 color) = 0;
		virtual void clearStaticQuads() = 0;
		void setProjectionMatrix(glm::mat4& projection);
		void setModelMatrix(glm::mat4& model);

		bool isQuadInFrustrum(int x, int y, int z, int sizex, int sizey, int sizez);

		virtual void begin() = 0;
		virtual void end() = 0;
		Shader& getShader();
		void setShader(Shader& shader);
		bool staticDrawn = false;
		bool projectionSet = false, modelSet = false;
	protected:
		/**
		* initTeturArray's puprpose is to initialise an empty texture array in the shaders uniform
		* labelled 'textures'
		*/
		struct FrustrumMinMaxs
		{
			float minx, miny, minz,
				maxx, maxy, maxz;
		} frustMinMaxs;
		void setFrustrumValues();
		void initTextureArray();

		// buffer operations
		virtual void createIndexBuffer(uint32& bufferID, uint32 type) = 0;
		virtual void createVertexBuffer(uint32& bufferID, uint32 type) = 0;
		virtual void assignVertexLayout(uint32& arrayID, uint32& bufferID) = 0;
		virtual void sendBufferData(const void* data, uint32& bufferID, uint32 type, uint32 size) = 0;
		std::unique_ptr<Shader> shader = nullptr;
		static const uint32 maxQuads = 20000, maxTextures = 32, maxIndices = maxQuads * 6, maxVertices = maxQuads * 40;
		glm::mat4* projection, * model;
	};

	/**
	* RendererBatched's purpose is to control the drawing of quads by offering drawQuad methods to client and
	* storing a queue of multiple quads to be drawn. A base quad is used for the vertices and indices of a standard
	* quad, and each time drawQuad is called a new model tranformation matrix is calculated, the base vertice data's
	* positions are transformed, and the vertice/indice data is added to either the static quads or dynamic quads
	*
	* Once the amount of drawn quads is equal to maxQuads, render is called to send all of the vertice
	* data to the vbo and ibo's. Then glDrawElements is called.
	*
	* The shader is responsible for indexing the individual quads via gl_InstanceID
	*/
	class RendererBatched: public Renderer
	{
	public:
		RendererBatched(std::string vertexShader, std::string fragShader);
		~RendererBatched();

		void drawQuadTextured(std::shared_ptr<Texture>, TexturePosition& textPos = TexturePosition()) override; // creates a quad2d and calls render
		void drawQuadColored(glm::vec4 color) override;
		void drawStaticQuadColored(glm::vec4 color) override;
		void drawStaticQuadTextured(std::shared_ptr<Texture>, TexturePosition& textPos = TexturePosition()) override;
		void clearStaticQuads() override;

		void renderStaticContent();

		uint32 getQuadsRendered() { return QuadsRendered; }
		uint32 quadsDrawn = 0;

		void begin() override;
		void end() override;

	protected:
		// data structs
		struct BaseQuadVertice
		{
			float vertices[40] =
			{
				//position            // col                      //text pos    // text slot
				-0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  -1.0f  , // top left
				 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  -1.0f  , // top right
				 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,  -1.0f  , // bottom left
				-0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  -1.0f	 // bottom right
			};
			uint32 indices[6] =
			{
				0, 1, 2, // triangle 1
				2, 3, 0 // triangle 2
			};
		};

		struct QuadVerticeData
		{
			std::vector<float> vertices;
			std::vector<uint32> indices;
			//float vertices[maxQuads * (sizeof(BaseQuadVertice::vertices) / sizeof(float))];
			//uint32 indices[maxQuads * (sizeof(BaseQuadVertice::indices) / sizeof(uint32))];
			QuadVerticeData() : 
				vertices(maxQuads* (sizeof(BaseQuadVertice::vertices) / sizeof(float))),
				indices(maxQuads* (sizeof(BaseQuadVertice::indices) / sizeof(uint32)))
			{
			}
			QuadVerticeData(const QuadVerticeData& other) :
				vertices(other.vertices),
				indices(other.indices) {
				int x = 0;
			}
		};

		struct BufferObjects
		{
			uint32 vbo, vao, ibo;
		};

		BufferObjects staticBufferObjs, dynamicBufferObjs;

		bool drawQuad(QuadVerticeData& data, int textSlot, glm::vec4 color, uint32 quadsDrawn, TexturePosition& textPos = TexturePosition());
		BaseQuadVertice getTransformedBaseQuad(glm::mat4 model, int textSlot, glm::vec4 color, TexturePosition& textPos);
		void renderDynamicContent();
		int findTexture(std::shared_ptr<Texture>, std::unordered_map<uint32, std::shared_ptr<Texture>> map);
		void bindTextureSlots(std::unordered_map<uint32, std::shared_ptr<Texture>> map);
		void pushNewStaticData();

		// buffer operations
		void createBuffers(BufferObjects& objs, uint32 type);
		void bindBuffers(BufferObjects& objs);
		void unbindBuffers();
		virtual void createIndexBuffer(uint32& bufferID, uint32 type) override;
		virtual void createVertexBuffer(uint32& bufferID, uint32 type) override;
		virtual void assignVertexLayout(uint32& arrayID, uint32& bufferID) override;
		void sendBufferData(BufferObjects& buffers, QuadVerticeData& data, uint32 howMany);
		void sendBufferData(const void* data, uint32& bufferID, uint32 type, uint32 size) override;

		// dynamic variables
		// control variables to keep track of drawn dynamic quads and ssbo id's
		int  texturesDrawn = 0;
		// texture cache dynamic storage
		std::unordered_map<uint32, std::shared_ptr<Texture>> dynamicTextureMap;
		// arrays of individual dynamic quad data
		QuadVerticeData dynamicQuad;

		// static quad arrays
		// when staticQuadsDrawn hits maxQuads, a new data object will be made and pushed to back
		// of staticQuads. If staticQuads holds more than 1 member, the last member will be dynamically
		// sized and use of staticQuadsDrawn will be used to index its data, else datacount will be 
		// maxQuads in length
		std::vector<std::pair<BufferObjects, QuadVerticeData>> staticBufferDataVector;
		std::vector<QuadVerticeData> staticQuads;
		QuadVerticeData currentStaticQuad;
		uint32 staticQuadsDrawn = 0, staticTexturesDrawn = 0;
		bool staticContentAdded = false;
		//texture cache static storage
		std::unordered_map<uint32, std::shared_ptr<Texture>> staticTextureMap;

		// stats
		uint32 QuadsRendered = 0;
	};
}
#endif
