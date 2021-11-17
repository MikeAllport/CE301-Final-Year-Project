#include "gepch.h"
#include "Renderer.h"

namespace GE::Graphics
{
	//--------- Renderer interface ------------//
	Renderer::Renderer(std::string vertexShader, std::string fragShader) :
		shader(new Shader(vertexShader, fragShader)),
		projection(nullptr),
		model(nullptr),
		projectionSet(false),
		frustMinMaxs()
	{
		initTextureArray();
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::initTextureArray()
	{
		int arr[maxTextures];
		for (int i = 0; i < maxTextures; i++)
		{
			arr[i] = i;
		}
		shader->bind();
		shader->setIntArray("textures", arr, maxTextures);
	}

	void Renderer::setProjectionMatrix(glm::mat4& projection)
	{
		shader->bind();
		shader->setUniformMat4F("projection", projection);
		this->projection = &projection;
		projectionSet = true;
		setFrustrumValues();
	}

	void Renderer::setFrustrumValues()
	{
		glm::mat4 inverseProjection = glm::inverse(*projection);
		glm::vec4 frustrumMinMaxs[8] = {
			{ -1, -1,  0 , 1 },
			{  1, -1,  0 , 1 },
			{  1,  1,  0 , 1 },
			{ -1,  1,  0 , 1 },
			{ -1, -1,  1 , 1 },
			{  1, -1,  1 , 1 },
			{  1,  1,  1 , 1 },
			{ -1,  1,  1 , 1 } };
		int minx, miny, minz, maxx, maxy, maxz;
		minx = miny = minz = std::numeric_limits<int>::max();
		maxx = maxy = maxz = std::numeric_limits<int>::min();

		for (int i = 0; i < 8; i++)
		{
			glm::vec4 position = frustrumMinMaxs[i];
			position = inverseProjection * position;
			position.x /= position.w;
			position.y /= position.w;
			position.z /= position.w;
			minx = (minx < position.x) ? minx : position.x;
			miny = (miny < position.y) ? miny : position.y;
			minz = (minz < position.z) ? minz : position.z;
			maxx = (maxx > position.x) ? maxx : position.x;
			maxy = (maxy > position.y) ? maxy : position.y;
			maxz = (maxz > position.z) ? maxz : position.z;
		}
		frustMinMaxs.maxx = maxx;
		frustMinMaxs.maxy = maxy;
		frustMinMaxs.maxz = maxz;
		frustMinMaxs.minx = minx;
		frustMinMaxs.miny = miny;
		frustMinMaxs.minz = minz;
	}


	bool Renderer::isQuadInFrustrum(
		int x, int y, int z, int sizex, int sizey, int sizez)
	{
		if (!projectionSet)
			return false;
		return
			x <= frustMinMaxs.maxx && x + sizex >= frustMinMaxs.minx &&
			y <= frustMinMaxs.maxy && y + sizey >= frustMinMaxs.miny &&
			z <= frustMinMaxs.maxz && z + sizez >= frustMinMaxs.minz;
	}

	void Renderer::setModelMatrix(glm::mat4& model)
	{
		this->model = &model;
		modelSet = true;
	}

	Shader& Renderer::getShader()
	{
		return *shader;
	}

	void Renderer::setShader(Shader& shader)
	{
		this->shader = std::unique_ptr<Shader>(new Shader(shader));
		initTextureArray();
	}


	RendererBatched::RendererBatched(std::string vertexShader, std::string fragShader) :
		Renderer(vertexShader, fragShader),
		currentStaticQuad(),
		staticBufferObjs(),
		dynamicBufferObjs()
	{
		// inits buffers
		createBuffers(staticBufferObjs, GL_DYNAMIC_DRAW);
		createBuffers(dynamicBufferObjs, GL_DYNAMIC_DRAW);
		// sets up static data
		staticTextureMap[0] = GE::Graphics::TextureCache::getTexture("textureError.png");
		++staticTexturesDrawn;
	}

	void RendererBatched::createBuffers(BufferObjects& obj, uint32 type)
	{
		createVertexBuffer(obj.vbo, type);
		assignVertexLayout(obj.vao, staticBufferObjs.vbo);
		createIndexBuffer(obj.ibo, type);
	}

	void RendererBatched::createIndexBuffer(uint32& bufferID, uint32 type)
	{
		glGenBuffers(1, &bufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(BaseQuadVertice::indices) * maxQuads, nullptr, type);
	}
	void RendererBatched::createVertexBuffer(uint32& bufferID, uint32 type)
	{
		glGenBuffers(1, &bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, bufferID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(BaseQuadVertice::vertices) * maxQuads, nullptr, type);
	}
	void RendererBatched::assignVertexLayout(uint32& arrayID, uint32& bufferID)
	{
		glGenVertexArrays(1, &arrayID);
		glBindVertexArray(arrayID);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), BUFFER_OFFSET(0));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), BUFFER_OFFSET(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), BUFFER_OFFSET(7 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 10 * sizeof(float), BUFFER_OFFSET(9 * sizeof(float)));
		glEnableVertexAttribArray(3);
		glBindVertexArray(0);
	}

	RendererBatched::~RendererBatched()
	{
		staticQuads.clear();
		dynamicTextureMap.clear();
		quadsDrawn = 0;
		texturesDrawn = 0;
	}

	void RendererBatched::drawQuadTextured(std::shared_ptr<Texture> text, TexturePosition& textPos)
	{
		if (quadsDrawn == maxQuads || texturesDrawn == maxTextures)
			renderDynamicContent();
		int textSlot = findTexture(text, dynamicTextureMap);
		if (textSlot == -1)
		{
			textSlot = texturesDrawn;
			dynamicTextureMap[texturesDrawn++] = text;
		}
		if (!drawQuad(dynamicQuad, textSlot, glm::vec4(1, 1, 1, 1), quadsDrawn, textPos))
			return;
		++quadsDrawn;
	}

	void RendererBatched::drawStaticQuadTextured(std::shared_ptr<Texture> text, TexturePosition& textPos)
	{
		if (staticQuadsDrawn == maxQuads || staticTexturesDrawn == maxTextures)
			pushNewStaticData();
		int textSlot = findTexture(text, staticTextureMap);
		if (textSlot == -1)
		{
			textSlot = texturesDrawn;
			staticTextureMap[texturesDrawn++] = text;
		}
		if (!drawQuad(currentStaticQuad, textSlot, glm::vec4(1, 1, 1, 1), staticQuadsDrawn, textPos))
			return;
		++staticQuadsDrawn;
		staticContentAdded = true;
	}

	void RendererBatched::drawStaticQuadColored(glm::vec4 color)
	{
		if (staticQuadsDrawn == maxQuads)
			pushNewStaticData();
		if (!drawQuad(currentStaticQuad, -1, color, staticQuadsDrawn))
			return;
		++staticQuadsDrawn;
		staticContentAdded = true;
	}

	void RendererBatched::drawQuadColored(glm::vec4 color)
	{
		if (quadsDrawn == maxQuads)
			renderDynamicContent();
		if (!drawQuad(dynamicQuad, -1, color, quadsDrawn))
			return;
		++quadsDrawn;
	}

	void RendererBatched::pushNewStaticData()
	{
		staticBufferDataVector.push_back(std::pair<BufferObjects, QuadVerticeData>(staticBufferObjs, currentStaticQuad));
		sendBufferData(staticBufferObjs, currentStaticQuad, maxQuads);
		currentStaticQuad = QuadVerticeData();
		staticBufferObjs = BufferObjects();
		createBuffers(staticBufferObjs, GL_DYNAMIC_DRAW);
		staticQuadsDrawn = 0;
		staticContentAdded = false;
	}

	int RendererBatched::findTexture(std::shared_ptr<Texture> text, std::unordered_map<uint32, std::shared_ptr<Texture>> map)
	{
		int found = -1;
		for (auto pair : map)
		{
			if (pair.second == text)
			{
				found = pair.first;
			}
		}
		return found;
	}

	bool RendererBatched::drawQuad(QuadVerticeData& data, int textSlot, glm::vec4 color, uint32 quadsDrawn, TexturePosition& textPos)
	{
		if (!modelSet)
		{
			GE_WARN("{} Render cycle initiated without having set model transformation", typeid(this).name());
			return false;
		}
		BaseQuadVertice transformedBase = getTransformedBaseQuad(*model, textSlot, color, textPos);
		for (int i = 0; i < 40; i += 10)
		{
			data.vertices[i + (quadsDrawn * 40) + 0] = transformedBase.vertices[i + 0];
			data.vertices[i + (quadsDrawn * 40) + 1] = transformedBase.vertices[i + 1];
			data.vertices[i + (quadsDrawn * 40) + 2] = transformedBase.vertices[i + 2];
			data.vertices[i + (quadsDrawn * 40) + 3] = transformedBase.vertices[i + 3];
			data.vertices[i + (quadsDrawn * 40) + 4] = transformedBase.vertices[i + 4];
			data.vertices[i + (quadsDrawn * 40) + 5] = transformedBase.vertices[i + 5];
			data.vertices[i + (quadsDrawn * 40) + 6] = transformedBase.vertices[i + 6];
			data.vertices[i + (quadsDrawn * 40) + 7] = transformedBase.vertices[i + 7];
			data.vertices[i + (quadsDrawn * 40) + 8] = transformedBase.vertices[i + 8];
			data.vertices[i + (quadsDrawn * 40) + 9] = transformedBase.vertices[i + 9];
		}
		int indiceOffset = quadsDrawn * 4;
		int quadOffset = quadsDrawn * 6;
		data.indices[quadOffset + 0] = indiceOffset + 0;
		data.indices[quadOffset + 1] = indiceOffset + 1;
		data.indices[quadOffset + 2] = indiceOffset + 2;
		data.indices[quadOffset + 3] = indiceOffset + 2;
		data.indices[quadOffset + 4] = indiceOffset + 3;
		data.indices[quadOffset + 5] = indiceOffset + 0;
		modelSet = false;
		return true;
	}

	RendererBatched::BaseQuadVertice RendererBatched::getTransformedBaseQuad(
		glm::mat4 model,
		int textSlot, 
		glm::vec4 color, 
		TexturePosition& textPos)
	{
		BaseQuadVertice base;
		for (int i = 0; i < 40; i += 10)
		{
			glm::vec4 pos = glm::vec4(base.vertices[i + 0], base.vertices[i + 1], base.vertices[i + 2], 1.0f);
			pos = model * pos;
			base.vertices[i + 0] = pos.x;
			base.vertices[i + 1] = pos.y;
			base.vertices[i + 2] = pos.z;
			base.vertices[i + 3] = color.r / 255.f;
			base.vertices[i + 4] = color.g / 255.f;
			base.vertices[i + 5] = color.b / 255.f;
			base.vertices[i + 6] = color.a;
			base.vertices[i + 7] = textPos.arr[i / 10].x;
			base.vertices[i + 8] = textPos.arr[i / 10].y;
			base.vertices[i + 9] = textSlot;
		}
		return base;
	}

	void RendererBatched::clearStaticQuads()
	{
		for (auto data : staticBufferDataVector)
		{
			glDeleteBuffers(1, &data.first.vbo);
			glDeleteBuffers(1, &data.first.ibo);
			glDeleteVertexArrays(1, &data.first.vao);
		}
		staticBufferDataVector.clear();
		staticTextureMap.clear();
		staticTexturesDrawn = staticQuadsDrawn = 0;
		staticContentAdded = false;
		currentStaticQuad = QuadVerticeData();
		staticBufferObjs = BufferObjects();
		createBuffers(staticBufferObjs, GL_DYNAMIC_DRAW);
	}

	void RendererBatched::begin()
	{
		shader->bind();
		QuadsRendered = 0;
		staticDrawn = false;
		modelSet = false;
		projectionSet = false;
	}

	void RendererBatched::end()
	{
		renderDynamicContent();
		shader->unbind();
	}

	void RendererBatched::renderDynamicContent()
	{
		if (!projectionSet)
		{
			GE_WARN("{} Render cycle initiated without having set projection transformation", typeid(this).name());
			return;
		}
		if (!staticDrawn)
			renderStaticContent();
		if (quadsDrawn == 0)
			return;
		sendBufferData(dynamicBufferObjs, dynamicQuad, quadsDrawn);

		bindBuffers(dynamicBufferObjs);
		bindTextureSlots(dynamicTextureMap);
		// draw call
		glDrawElements(GL_TRIANGLES, 6 * quadsDrawn, GL_UNSIGNED_INT, 0);
		quadsDrawn = 0;
		QuadsRendered += quadsDrawn;	
		unbindBuffers();
	}

	void RendererBatched::renderStaticContent()
	{
		bindTextureSlots(staticTextureMap);
		for (std::vector<std::pair<BufferObjects, QuadVerticeData>>::iterator it = staticBufferDataVector.begin(); 
			it != staticBufferDataVector.end(); ++it)
		{
			bindBuffers(it->first);
			glDrawElements(GL_TRIANGLES, 6 * maxQuads, GL_UNSIGNED_INT, 0);
		}
		if (staticQuadsDrawn > 0)
		{
			if (staticContentAdded)
			{
				sendBufferData(staticBufferObjs, currentStaticQuad, staticQuadsDrawn);
				staticContentAdded = false;
			}
			bindBuffers(staticBufferObjs);
			glDrawElements(GL_TRIANGLES, 6 * staticQuadsDrawn, GL_UNSIGNED_INT, 0);
		}
		unbindBuffers();
		staticDrawn = true;
	}
	
	void RendererBatched::sendBufferData(BufferObjects& buffers, QuadVerticeData& data, uint32 howMany)
	{
		bindBuffers(buffers);
		sendBufferData(&data.vertices[0],
			buffers.vbo,
			GL_ARRAY_BUFFER,
			sizeof(BaseQuadVertice::vertices) * howMany);

		sendBufferData(&data.indices[0],
			buffers.vao,
			GL_ELEMENT_ARRAY_BUFFER,
			sizeof(BaseQuadVertice::indices) * howMany);
		unbindBuffers();
	}

	void RendererBatched::bindBuffers(BufferObjects& buffers)
	{
		glBindVertexArray(buffers.vao);
		glBindBuffer(GL_ARRAY_BUFFER, buffers.vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers.ibo);
	}

	void RendererBatched::unbindBuffers()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void RendererBatched::sendBufferData(const void* data, uint32& bufferID, uint32 type, uint32 size)
	{
		glInvalidateBufferData(bufferID);
		glBufferSubData(type, 0, size, data);
	}

	void RendererBatched::bindTextureSlots(std::unordered_map<uint32, std::shared_ptr<Texture>> map)
	{
		for (auto pair : map)
		{
			pair.second->bind(pair.first);
		}
	}
}
