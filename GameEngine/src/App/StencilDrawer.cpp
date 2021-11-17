#include "gepch.h"
#include "StencilDrawer.h"

namespace App
{
	StencilRenderer::StencilRenderer(std::string vert, std::string frag) :
		GE::Graphics::RendererBatched(vert, frag)
	{
	}

	StencilDrawer::StencilDrawer(glm::vec3 color) :
		rend(),
		color(color)
	{
		rend.color = color;
	};

	void StencilDrawer::draw(CommonGameObject* obj, glm::mat4 projection, GE::Graphics::RendererBatched& originalRenderer)
	{
		originalRenderer.end();
		rend.begin();
		rend.setProjectionMatrix(projection);
		float* col = new float[] { color.r, color.g, color.b };
		rend.getShader().setUniform3fv("stencil_col", col);
		obj->draw(rend);
		delete[] col;
		rend.end();
		originalRenderer.begin();
		originalRenderer.staticDrawn = true;
		originalRenderer.setProjectionMatrix(projection);
	}
}