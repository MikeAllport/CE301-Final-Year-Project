#include <gepch.h>
#include "ObjectPicker.h"

namespace App
{
	RendererPicker::RendererPicker(std::string vert, std::string frag):
		GE::Graphics::RendererBatched(vert, frag)
	{
	}

	void RendererPicker::drawQuadTextured(std::shared_ptr<GE::Graphics::Texture> text, TexturePosition& textPos)
	{
		if (quadsDrawn == maxQuads || texturesDrawn == maxTextures)
			renderDynamicContent();
		int textSlot = findTexture(text, dynamicTextureMap);
		if (textSlot == -1)
		{
			textSlot = texturesDrawn;
			dynamicTextureMap[texturesDrawn++] = text;
		}
		drawQuad(dynamicQuad, textSlot, glm::vec4(color, 1), quadsDrawn, textPos);
		++quadsDrawn;
	}

	ObjectPicker::ObjectPicker(Game& game):
		game(game)
	{
		game.getWindow().useHiddenWindow();
		rend = new RendererPicker();
		game.getWindow().useMainWindow();
	}

	void ObjectPicker::initWindow()
	{
		game.getWindow().useHiddenWindow();
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		int wMain, wHidden, hMain, hHidden;
		glfwGetWindowSize(GE::Window::window, &wMain, &hMain);
		glfwGetWindowSize(GE::Window::hiddenWindow, &wHidden, &hHidden);
		if (wMain != wHidden || hMain != hHidden)
			glfwSetWindowSize(GE::Window::hiddenWindow, wMain, hMain);
		glViewport(0, 0, wMain, hMain);
	}

	void ObjectPicker::pickObjects(std::vector<CommonGameObject*>* objects)
	{
		initWindow();
		rend->begin();
		rend->setProjectionMatrix(game.getWindow().getCamera()->getViewProjection());
		std::unordered_map<int, CommonGameObject*> lookupTable;
		for (std::vector<CommonGameObject*>::iterator it = objects->begin();
			it != objects->end();
			++it)
		{
			rend->color = getEncodedColor((*it)->objectID);
			(*it)->draw(*rend);
			lookupTable[(*it)->objectID] = (*it);
		}
		rend->end();
		decodeObjectUnderMouse(lookupTable);
	}

	void ObjectPicker::decodeObjectUnderMouse(std::unordered_map<int, CommonGameObject*>& lookupTable)
	{
		Vector2D mousePos = MouseState::getPosition();
		unsigned char data[4];
		glFinish();
		glReadBuffer(GL_FRONT);
		glReadPixels(mousePos.x, 
			game.getWindow().getHeight() - mousePos.y, 1, 1,
			GL_RGBA, 
			GL_UNSIGNED_BYTE, 
			&data);
		if (game.getWindow().isPointInWindow(mousePos.x, mousePos.y))
		{
			if (data[0] != GE::Window::WINDOW_COLOR.r && 
				data[1] != GE::Window::WINDOW_COLOR.g && 
				data[2] != GE::Window::WINDOW_COLOR.b)
			{
				int objectID = getDecodedColor(glm::vec3(data[0], data[1], data[2]));
				MouseState::setObjectUnderMouse(lookupTable[objectID]);
			}
			else
			{
				MouseState::setObjectUnderMouse(nullptr);
			}
		}
	}

	void ObjectPicker::endWindow()
	{

	}

	glm::vec3 ObjectPicker::getEncodedColor(int objID)
	{
		int r = (objID & 0x000000FF) >> 0;
		int g = (objID & 0x0000FF00) >> 8;
		int b = (objID & 0x00FF0000) >> 16;
		return glm::vec3(r, g, b);
	}
	int ObjectPicker::getDecodedColor(glm::vec3 color)
	{
		return 	color.r + color.g * 256 + color.b * 256 * 256;
	}
}
