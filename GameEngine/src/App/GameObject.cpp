#include <gepch.h>
#include "GameObject.h"
#include "Game.h"
#include <App/WorldGeneration/Tile.h>

namespace App
{
	// gets the offsets for a texture given size changeratio
	glm::vec3 getOffset(glm::vec3 size, TexturePack pack)
	{
		float heightOffsetPostRatio = (size.y / (float)pack.textHeight) * pack.textOffset.y;
		glm::vec3 result = glm::vec3(0, (size.y / 2.F) - heightOffsetPostRatio, (size.y / -2.F) + heightOffsetPostRatio);
		return result;
	}

	CommonObjectData CommonObjectMap::get(CommonObjectsEnum objectID)
	{
		if (!initialized)
			init();
		return map.at(objectID);
	}

	CommonObjectData::CommonObjectData(glm::vec3 size, TextureNameEnums type, std::string name)
	{
		this->size = glm::vec3(size.x * Sprite::FLAT_WIDTH_RATIO, size.y * Sprite::FLAT_HEIGHT_RATIO, 0);
		texturePack = TexturePacks::get(type);
		offset = getOffset(this->size, texturePack);
		this->name = name;
	}

	void CommonObjectMap::init()
	{
		map[CHARACTER] = CommonObjectData
		(
			 glm::vec3(100, 100, 0),
			 TextureNameEnums::TEXT_CHARACTER,
			"Character"
		);

		map[MOUNTAIN] = CommonObjectData
		(
			glm::vec3(100, 100, 0),
			TextureNameEnums(TEXT_MOUNTAIN),
			"Mountain"
		);

		map[TREE1] = CommonObjectData
		(
			glm::vec3(250, 250, 0),
			TextureNameEnums(TEXT_TREE1),
			"Tree 1"
		);
		map[TREE2] = CommonObjectData
		(
			glm::vec3(250, 250, 0),
			TextureNameEnums(TEXT_TREE2),
			"Tree 2"
		);
		map[TREE3] = CommonObjectData
		(
			glm::vec3(250, 250, 0),
			TextureNameEnums(TEXT_TREE3),
			"Tree 3"
		);
		map[ROCKO] = CommonObjectData
		(
			glm::vec3(50, 50, 0),
			TextureNameEnums(TEXT_ROCK_O),
			"RockO"
		);
		map[GRASSO] = CommonObjectData
		(
			glm::vec3(100, 150, 0),
			TextureNameEnums(TEXT_GRASS_O),
			"GrassO"
		);
		map[BERRY_BUSH] = CommonObjectData
		(
			glm::vec3(100, 100, 0),
			TextureNameEnums(TEXT_BERRY_BUSH),
			"Berry Bush"
		);
		map[STICK_BUSH] = CommonObjectData
		(
			glm::vec3(150, 150, 0),
			TextureNameEnums(TEXT_STICK_BUSH),
			"Stick Bush"
		);
	}

	GameObject::GameObject(const glm::fvec3 position, const glm::vec3 size) :
		position(position),
		moved(true),
		size(size),
		velocity(0, 0),
		objectID(objectIDCount++)
	{

	}

	GameObject::~GameObject()
	{
	}

	void GameObject::setPosition(glm::fvec3 position)
	{
		if (this->position != position)
		{
			moved = true;
			this->position = position;
		}
	}

	void GameObject::onUpdate(const float& DT)
	{
		Vector2D new2DPosition(position.x, position.z);
		new2DPosition += velocity * DT;
		glm::fvec3 newPosition = glm::fvec3(new2DPosition.x, 0, new2DPosition.y);
		if (this->position != newPosition)
		{
			moved = true;
			this->position = newPosition;
		}
	}

	glm::fvec3& GameObject::getPosition()
	{
		return position;
	}
	CommonGameObject::CommonGameObject(glm::fvec3 position, CommonObjectsEnum e) :
		data(CommonObjectMap::get(e)),
		GameObject(position, data.size),
		sprite(this, data.texturePack)
	{
		sprite.setSize(data.size);
		size = data.size;
		sprite.setOffset(data.offset);
	}

	CommonGameObject::CommonGameObject(const CommonGameObject& other):
		GameObject(other),
		data(other.data),
		sprite(this, other.data.texturePack)
	{
		moved = true;
		sprite.setOffset(data.offset);
	}

	void CommonGameObject::draw(GE::Graphics::Renderer& rend)
	{
		sprite.draw(rend);
	}

	std::string CommonGameObject::toString() const
	{
		return "I am a " + data.name + ", my ID is " + std::to_string(objectID);
	}
	bool operator<(const GameObject& first, const GameObject& second)
	{
		return first.position.x + (int)first.position.z * Tile::TILE_HEIGHT <
			second.position.x + (int)second.position.z * Tile::TILE_HEIGHT;
	}
}