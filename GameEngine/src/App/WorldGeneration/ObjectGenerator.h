#pragma once
#include <App/WorldGeneration/World.h>
#include <App/WorldGeneration/PoissonGenerator.h>
#include <App/WorldGeneration/GeneratorSettings.h>

namespace App::WorldGen
{
	class ObjectGenerator
	{
	public:
		ObjectGenerator(World& world, WorldGen::ObjectPlacementSettings settings = WorldGen::ObjectPlacementSettings());
		std::vector<CommonGameObject*>* getObjects();
		~ObjectGenerator();
		PoissonGenerator poissonGen;
	private:
		void generateObjects();
		CommonGameObject* genTree(Vector2D position);
		CommonGameObject* genGrass(Vector2D position);
		CommonGameObject* genMisc(Vector2D position);
		CommonGameObject* genConsumable(Vector2D position);
		void addConsumables(Vector2D origin);
		std::vector<CommonGameObject*> objects;
		World& world;
		Random& random;
		WorldGen::ObjectPlacementSettings settings;
	};
}