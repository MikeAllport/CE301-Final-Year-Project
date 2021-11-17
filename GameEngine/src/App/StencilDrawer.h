#ifndef APP_STENCIL_DR
#define APP_STENCIL_DR

#include <GE/Graphics/Renderer.h>
#include <App/GameObject.h>

namespace App
{

	class StencilRenderer : public GE::Graphics::RendererBatched
	{
	public:
		friend class StencilDrawer;
		StencilRenderer(std::string vert = "batchedRendererTest-vert.shader",
			std::string frag = "stencil-frag.shader");
	private:
		glm::vec3 color;
	};

	class StencilDrawer
	{
	public:
		StencilDrawer(glm::vec3 color = glm::vec3(1.5, 1.5, 1.8));
		void draw(CommonGameObject* obj, glm::mat4 projection, GE::Graphics::RendererBatched& originalRenderer);
	private:
		glm::vec3 color;
		StencilRenderer rend;
	};
}
#endif