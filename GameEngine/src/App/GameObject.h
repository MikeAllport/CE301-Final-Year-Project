#ifndef APP_GAMEOBJECT
#define APP_GAMEOBJECT
#include "Interfaces.h"
#include "TextureMap.h"
#include "Vector2D.h"
#include "Sprite.h"
#include <Object.h>
namespace App
{
	enum CommonObjectsEnum
	{
		CHARACTER,
		MOUNTAIN,
		TREE1,
		TREE2,
		TREE3,
		ROCKO,
		STICK_BUSH,
		BERRY_BUSH,
		GRASSO
	};

	class CommonObjectData
	{
	public:
		CommonObjectData() {};
		CommonObjectData(glm::vec3 size, TextureNameEnums type, std::string name);
		glm::vec3 size;
		TexturePack texturePack;
		glm::vec3 offset;
		std::string name;
	};

	class CommonObjectMap
	{
	public:
		static CommonObjectData get(CommonObjectsEnum objectID);
	private:
		static inline bool initialized = false;
		static void init();
		static inline std::unordered_map<CommonObjectsEnum, CommonObjectData> map = {};
	};

	/**
	* Sprite's purpose is to hold information related to drawing a game entity comprising
	* of what texture to draw, the position to draw, and what size to draw it at.
	*
	* Given the renderer takes 0,0,0 to be the positions reference point, the position to
	* draw the sprite needs to be translated to make 0,0,0 the bottom-middle of the image
	* so that if drawing a person at 0,0,0 that point would be the middle of their feet.
	*/
	class GameObject : public IUpdateableDT
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
		GameObject(const glm::fvec3 position, const glm::vec3 size);
		~GameObject();
		virtual void onUpdate(const float& DT) override;
		void setPosition(glm::fvec3 position);
		glm::fvec3 position;
		glm::fvec3& getPosition();
		glm::vec3 size;
		friend bool operator<(const GameObject& first, const GameObject& second);
		static inline int objectIDCount = 0;
		const int objectID;
	protected:
		friend class Game;
		friend class CameraEventHandler;
		friend class Sprite;
		bool moved = false;
		Vector2D velocity;
	};

	class CommonGameObject : public GameObject, public IDrawable, public GE::Object
	{
	public:
		CommonGameObject(glm::fvec3 position, CommonObjectsEnum e);
		CommonGameObject(const CommonGameObject& other);
		void draw(GE::Graphics::Renderer& rend) override;
		std::string toString() const override;
		FlatSprite& getSprite() { return sprite; }
	protected:
		CommonObjectData data;
		FlatSprite sprite;
	};
}

#endif