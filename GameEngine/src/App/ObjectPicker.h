#ifndef APP_OBJ_PICKER
#define APP_OBJ_PICKER
#include <GE/Graphics/Renderer.h>
#include <App/GameObject.h>
#include <App/MouseState.h>
#include <App/Game.h>

namespace App
{

	class RendererPicker : public GE::Graphics::RendererBatched
	{
	public:
		RendererPicker(std::string vert = "batchedRendererTest-vert.shader",
			std::string frag = "object_picker_frag.shader");
		glm::vec3 color;
		void drawQuadTextured(std::shared_ptr<GE::Graphics::Texture> text, TexturePosition& textPos) override;
	};

	// Code modified from 
	// http://www.opengl-tutorial.org/miscellaneous/clicking-on-objects/picking-with-an-opengl-hack/
	class ObjectPicker
	{
	public:
		ObjectPicker(Game& game);
		void pickObjects(std::vector<CommonGameObject*>* objects);
		RendererPicker* rend;
	private:
		void initWindow();
		void endWindow();
		void decodeObjectUnderMouse(std::unordered_map<int, CommonGameObject*>& lookupTable);
		glm::vec3 getEncodedColor(int objID);
		int getDecodedColor(glm::vec3 color);
		Game& game;
	};

}
#endif // !APP_OBJ_PICKER
