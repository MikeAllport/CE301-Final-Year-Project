#ifndef GAME_TILE
#define GAME_TILE

#include <GE/Graphics/TextureCache.h>
#include <App/Sprite.h>
#include <App/GameObject.h>

namespace App
{
	extern float convertRange0to1(float value, float min, float max);
	/**
	* Tile's purpose is to contain information related to a floor tiles spatial positioning
	* alongside qualities required to renderer the class.
	*
	* At the moment, it contains just enough information. As the possible tiles that can be drawn
	* increase, and a texture atlas will be used, this class will be more detailed.
	*/
	class Tile : public GameObject, public IDrawable
	{
	public:
		/**
		* Standard constructor used taking the tiles position as initialization argumenr
		*
		* args:
		*	glm::vec3f& - the vec3 of the tiles position spatially
		*/
		Tile(glm::fvec3& position = glm::fvec3(0.0f, 0.0f, 0.0f));
		Tile(const Tile& other);

		void setTextureType(float type);
		float getTextureType();
		int getWidth();
		int getHeight();
		Sprite& getSprite();

		static const int TILE_WIDTH = 128, TILE_HEIGHT = 128;
		static void useGreyscale(bool yn);
		static bool USE_GREYSCALE;

		void draw(GE::Graphics::Renderer& rend) override;
		static inline const float WATER = 0.15, SAND = 0.25, DIRT = 0.35, GRASS = 0.75, MOUNTAIN = 1;
	private:
		float textType;
		Sprite sprite;
	};
}
#endif