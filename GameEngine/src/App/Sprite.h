#ifndef APP_SPRITE
#define APP_SPRITE
#include "Interfaces.h"
#include "TextureMap.h"

namespace App
{
	extern class GameObject;
	/**
	* Sprite's purpose is to hold information related to drawing a game entity comprising
	* of what texture to draw, the position to draw, and what size to draw it at.
	*
	* Given the renderer takes 0,0,0 to be the positions reference point, the position to
	* draw the sprite needs to be translated to make 0,0,0 the bottom-middle of the image
	* so that if drawing a person at 0,0,0 that point would be the middle of their feet.
	*/
	// All flattened image sizes need width and height adjusting to
	// ratio difference on height = 0.65
	// ratio difference on width =  1.1
	class Sprite : public IDrawable
	{
	public:
		/**
		* Default constructor initializing class members, with a reference to the position
		* so no update will be required for physics/movement aslong as the calling class
		* passes its position
		*
		* args:
		*	glm::vec3& position, the reference to the initiators position
		*	glm::vec2 size, the size of the image to draw
		*	TextureNameEnum, the enum related to the texture to draw
		*/
		Sprite( GameObject* owner,
			TexturePack e = TexturePacks::get(TEXT_ERROR));
		friend class StencilDrawer;
		virtual void draw(GE::Graphics::Renderer& rend);
		void setModelMatrix(GE::Graphics::Renderer& rend);
		glm::mat4 getModelMatrix();
		void setTexture(TextureNameEnums e);
		bool isRenderable(GE::Graphics::Renderer& rend);
		glm::fvec3 getOffset();
		void setOffset(glm::fvec3& newOffset);
		void setSize(glm::vec3 size);
		TexturePack textPack;
		inline const static float FLAT_HEIGHT_RATIO = 0.65, FLAT_WIDTH_RATIO = 1.1;
	protected:
		virtual void updateModelMatrix();
		friend class Tile;
		GE::Graphics::Renderer::TexturePosition textPos;
		glm::vec3 size;
		glm::mat4 modelMatrix;
		glm::fvec3 offset;
		GameObject* owner;
	};


	class FlatSprite : public Sprite
	{
	public:
		FlatSprite( GameObject* owner,
			TexturePack e );
	protected:
		void updateModelMatrix() override;
		static const glm::fmat4 flattenedMatrix;
	};
}

#endif