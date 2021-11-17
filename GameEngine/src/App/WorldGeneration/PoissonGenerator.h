#ifndef APP_POISSON
#define APP_POISSON

#include "Noise.h"
#include <App/Vector2D.h>
#include <App/WorldGeneration/World.h>

namespace App::WorldGen
{
	class PoissonGenerator
	{
	public:
		PoissonGenerator(World& world, float minDist, float maxDist, int attempts);
		~PoissonGenerator();
		std::vector<Vector2D> getPoints();
		void setBlueNoiseFreq(int value);
		Random& random;
		Perlin perlin;
	private:
		friend class ObjectGenerator;
		PoissonGenerator(const PoissonGenerator& other);
		void generateGrid();
		void generatePoints();
		class Grid
		{
		public:
			Grid(int width, int height, int maxElements, float cellSize);
			bool pointInGrid(const Vector2D& point);
			Vector2D getGridXY(const Vector2D& point);
			bool addPoint(const Vector2D& point);
			std::vector<Vector2D>* getPointsInCell(const Vector2D& cell);
			int cellsWide, cellsHeigh;
			int pointsGenerated;
			float cellSize;
			std::vector<std::vector<std::vector<Vector2D>>> grid;
		};

		Grid* grid;
		World& world;
		float minDist, maxDist;
		int maxGridSize, attempts;

		static inline int BLUE_NOISE_FREQ = 10;
		//using Grid = std::vector<std::vector<std::vector<Vector2D>>>;
		//static bool inGrid(Vector2D point, int maxGridSize);
		bool noNeighbours(const Vector2D& point, float distance);
		bool findNeighbourInCell(const Vector2D& cellXY, const Vector2D& origin, float distance);
		//static Vector2D getGridXY(Vector2D point, float cellSize);
		Vector2D generatePointAround(const Vector2D& point, float distance);
	};
}

#endif