#include <gepch.h>
#include "Sprite.h"
#include "GameObject.h"

#define _CRTDBG_MAP_ALLOC

namespace App
{
	glm::fmat4 getFlatMatrix()
	{
		glm::mat4 fact = glm::mat4(1);
		fact = setMat4Row(fact, getMat4Row(fact, 2) * -1.f, 2);
		fact = setMat4Column(fact, 1e-13f * getMat4Column(fact, 2) - glm::vec4(0, 1, 0, 0), 2);
		return fact;
	}

	glm::fmat4 const FlatSprite::flattenedMatrix = getFlatMatrix();

	Sprite::Sprite(	GameObject* owner,
		TexturePack e) :
		textPack(e), 
		size(owner->size),
		modelMatrix(glm::mat4(1)),
		textPos(),
		owner(owner),
		offset(0)
	{
	}

	void Sprite::setSize(glm::vec3 size)
	{
		this->size = size;
	}

	glm::mat4 Sprite::getModelMatrix()
	{
		return modelMatrix;
	}
	void Sprite::setTexture(TextureNameEnums e)
	{
		textPack = TexturePacks::get(e);
	}

	void Sprite::draw(GE::Graphics::Renderer& rend)
	{
		if (isRenderable(rend))
		{
			setModelMatrix(rend);
			rend.drawQuadTextured(textPack.text, textPos);
		}
	}

	bool Sprite::isRenderable(GE::Graphics::Renderer& rend)
	{
		return rend.isQuadInFrustrum(
			owner->position.x,
			owner->position.y,
			owner->position.z,
			owner->size.x,
			owner->size.y,
			owner->size.z);
	}

	void Sprite::updateModelMatrix()
	{
		modelMatrix = glm::translate( glm::mat4(1.0F), glm::fvec3( 
			owner->position.x + offset.x, 
			owner->position.y + offset.y, 
			owner->position.z + offset.z) ) *
			glm::scale( glm::mat4(1.0f), size );
	}

	void Sprite::setModelMatrix(GE::Graphics::Renderer& rend)
	{
		if (owner->moved)
		{
			updateModelMatrix();
			owner->moved = false;
		}
		rend.setModelMatrix(modelMatrix);
	}

	glm::fvec3 Sprite::getOffset()
	{
		return offset;
	}

	void Sprite::setOffset(glm::fvec3& newOffset)
	{
		offset = newOffset;
	}


	FlatSprite::FlatSprite( GameObject* owner,
		TexturePack e ) :
		Sprite( owner, e )
	{
	}

	void FlatSprite::updateModelMatrix()
	{
		getFlatMatrix();
		modelMatrix = glm::translate(glm::mat4(1.0f), glm::fvec3( 
			owner->position.x + offset.x, 
			owner->position.y + offset.y, 
			owner->position.z + offset.z)) *
			flattenedMatrix *
			glm::scale(glm::mat4(1.0f), size);
	}

}