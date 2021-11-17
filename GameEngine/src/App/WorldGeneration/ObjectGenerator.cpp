#include <gepch.h>
#include "ObjectGenerator.h"

namespace App::WorldGen
{
	ObjectGenerator::ObjectGenerator(World& world, WorldGen::ObjectPlacementSettings settings):
		world(world),
		random(world.getRNG()),
		objects(),
		settings(settings),
		poissonGen(world, settings.minDist, settings.maxDist, settings.attempts)
	{
		poissonGen.setBlueNoiseFreq(settings.blueNoise);
		generateObjects();
	}

	ObjectGenerator::~ObjectGenerator()
	{
		for (CommonGameObject* obj : objects)
			delete obj;
		objects.clear();
	}

	void ObjectGenerator::generateObjects()
	{
		Perlin& perlin = poissonGen.perlin;
		std::vector<Vector2D> points = poissonGen.getPoints();
		objects.reserve(poissonGen.grid->pointsGenerated);
		for (const Vector2D& position : points)
		{
			if (random.genFloat(0, 1) < 0.8)
			{
				float rand = random.genFloat(0, 1);
				float noisePos = perlin.noiseWithFreq(position.x, position.y, PoissonGenerator::BLUE_NOISE_FREQ);
				if (rand <= noisePos)
				{
					// generate tree
					objects.push_back(genTree(position));
				}
				else if (rand <= 1 - noisePos)
				{
					objects.push_back(genGrass(position));
				}
				else
				{
					objects.push_back(genMisc(position));
				}
				addConsumables(position);
			}

		}
	}

	void ObjectGenerator::addConsumables(Vector2D origin)
	{
		for (int i = 0; i < 2; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				float distance = poissonGen.minDist + random.genFloat(0, 1) * poissonGen.maxDist;
				Vector2D point = poissonGen.generatePointAround(origin, distance);
				if (poissonGen.grid->pointInGrid(point))
				{
					if (world.getTileFromXY(point.x, point.y).getTextureType() < .15)
						continue;
					if (poissonGen.noNeighbours(point, distance) && poissonGen.grid->addPoint(point))
					{
						objects.push_back(genConsumable(point));
						break;
					}
				}
			}
		}
	}

	CommonGameObject* ObjectGenerator::genTree(Vector2D position)
	{
		int rand = random.genInt(0, 2);
		//if (rand == 0)
			return new App::CommonGameObject(
				glm::vec3(position.x, 0, position.y),
				App::CommonObjectsEnum::TREE1);
		//if (rand == 1)
		//	return new App::CommonGameObject(
		//		glm::vec3(position.x, 0, position.y),
		//		App::CommonObjectsEnum::TREE2);
		//return new App::CommonGameObject(
		//	glm::vec3(position.x, 0, position.y),
		//	App::CommonObjectsEnum::TREE3);
	}

	CommonGameObject* ObjectGenerator::genGrass(Vector2D position)
	{
		return new App::CommonGameObject(
			glm::vec3(position.x, 0, position.y),
			App::CommonObjectsEnum::GRASSO);
	}

	CommonGameObject* ObjectGenerator::genMisc(Vector2D position)
	{
		int rand = random.genInt(0, 2);
		if (rand == 0)
			return new App::CommonGameObject(
				glm::vec3(position.x, 0, position.y),
				App::CommonObjectsEnum::STICK_BUSH);
		return new App::CommonGameObject(
			glm::vec3(position.x, 0, position.y),
			App::CommonObjectsEnum::BERRY_BUSH);
	}

	CommonGameObject* ObjectGenerator::genConsumable(Vector2D position)
	{
		int rand = random.genInt(0, 3);
		if (rand == 0)
			return new App::CommonGameObject(
				glm::vec3(position.x, 0, position.y),
				App::CommonObjectsEnum::ROCKO);
		//if (rand == 1)
			return new App::CommonGameObject(
				glm::vec3(position.x, 0, position.y),
				App::CommonObjectsEnum::GRASSO);
		//return new App::CommonGameObject(
		//	glm::vec3(position.x, 0, position.y),
		//	App::CommonObjectsEnum::BERRY_BUSH);
	}

	std::vector<CommonGameObject*>* ObjectGenerator::getObjects()
	{
		return &objects;
	}
}