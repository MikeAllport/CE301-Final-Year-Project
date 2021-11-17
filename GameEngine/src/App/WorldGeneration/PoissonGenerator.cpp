#include <gepch.h>
#include "PoissonGenerator.h"

namespace App::WorldGen
{
	PoissonGenerator::PoissonGenerator(World& world, float minDist, float maxDist, int attempts) :
		world(world),
		random(world.getRNG()),
		perlin(random, world.sizex),
		minDist(minDist),
		maxDist(maxDist),
		maxGridSize(world.sizex),
		attempts(attempts),
		grid(nullptr)
	{
		generateGrid();
	}

	PoissonGenerator::~PoissonGenerator()
	{
		delete grid;
	}

	void PoissonGenerator::generateGrid()
	{
		// init lists
		float cellSize = maxDist / std::sqrt(2);
		int maxRowsCols = (int)std::ceil(maxGridSize / cellSize);
		// approximate maximum circles per cell so as to minimize memory copying
		float areaRect = cellSize * cellSize;
		float areaOneCircleToRect = minDist * minDist;
		int maxPointsInCell = std::ceil(areaRect / areaOneCircleToRect);
		grid = new Grid(maxRowsCols, maxRowsCols, maxPointsInCell, cellSize);
	}

	std::vector<Vector2D> PoissonGenerator::getPoints()
	{
		generatePoints();
		std::vector<Vector2D> points;
		points.reserve(grid->pointsGenerated);
		for(int i = 0; i < grid->cellsHeigh; ++i)
			for (int j = 0; j < grid->cellsWide; ++j)
			{
				for (std::vector<Vector2D>::iterator it = grid->grid[i][j].begin();
					it != grid->grid[i][j].end();
					++it)
					points.push_back(*it);
			}
		return points;
	}

	void PoissonGenerator::generatePoints()
	{
		std::vector<Vector2D> frontier;

		//generate starting point and update lists
		Vector2D randomPoint;
		do {
			randomPoint = Vector2D(random.genInt(0, maxGridSize - 1), random.genInt(0, maxGridSize - 1));
		} while (world.getTileFromXY(randomPoint.x, randomPoint.y).getTextureType() < .15);
		grid->addPoint(randomPoint);
		frontier.push_back(randomPoint);

		//generate all points
		while (!frontier.empty())
		{
			int randomPointIndex = random.genInt(0, frontier.size() - 1);
			Vector2D pointReference = frontier[randomPointIndex];
			float densityValue1 = perlin.noiseWithFreq(pointReference.x, pointReference.y, BLUE_NOISE_FREQ);
			float densityValue = 1 - perlin.noiseWithFreq(pointReference.x, pointReference.y, BLUE_NOISE_FREQ);
			//densityValue = convertRange0to1(densityValue, 0, 1.75);
			// change this to 
			// minDist + density * (maxDist-minDist) for alternative
			// or 
			//float distance = (0.15 / std::exp(1.0)) * minDist + (densityValue / std::exp(1.0)) * maxDist;
			float distance = minDist + (std::max(densityValue * maxDist, minDist));
			//distance = std::sqrt(distance);
			bool inserted = false;
			for (int i = 0; i < attempts; ++i)
			{
				Vector2D possiblePoint = generatePointAround(pointReference, distance);
				if (grid->pointInGrid(possiblePoint))
				{
					if (world.getTileFromXY(possiblePoint.x, possiblePoint.y).getTextureType() < .15)
						continue;
					if (noNeighbours(possiblePoint, distance))
					{
						frontier.push_back(possiblePoint);
						grid->addPoint(possiblePoint);
						inserted = true;
					}
				}
			}
			if (!inserted)
				frontier.erase(frontier.begin() + randomPointIndex);
		}
	}

	void PoissonGenerator::setBlueNoiseFreq(int value)
	{
		BLUE_NOISE_FREQ = value;
	}

	bool PoissonGenerator::noNeighbours(const Vector2D& point, float distance)
	{
		Vector2D pointGridXY = grid->getGridXY(point);
		std::vector<Vector2D*> neighbours;
		int ySearchMin = (int)pointGridXY.y - 4;
		int ySearchMax = (int)pointGridXY.y + 4;
		int xSearchMin = (int)pointGridXY.x - 4;
		int xSearchMax = (int)pointGridXY.x + 4;
		for(int y = ySearchMin; y <= ySearchMax; ++y)
			for (int x = xSearchMin; x <= xSearchMax; ++x)
			{
				if (findNeighbourInCell(Vector2D(x, y), point, distance))
					return false;
			}
		return true;
	}

	bool PoissonGenerator::findNeighbourInCell(const Vector2D& cellXY, const Vector2D& origin, float distance)
	{
		std::vector<Vector2D>* pointsInCell = grid->getPointsInCell(cellXY);
		if (pointsInCell != nullptr)
		{
			for (std::vector<Vector2D>::iterator it = pointsInCell->begin(); it != pointsInCell->end(); ++it)
			{
				if (it->Distance(origin) < distance)
					return true;
			}
		}
		return false;
	}

	Vector2D PoissonGenerator::generatePointAround(const Vector2D& point, float distance)
	{
		float angle = random.genFloat(0, 1) * M_PI * 2;
		float randomDist = distance * (random.genFloat(0,1) + 1);
		return Vector2D(point) + Vector2D::Cartesian(angle, randomDist);
	}

	PoissonGenerator::Grid::Grid(int width, int height, int maxElements, float cellSize) :
		cellsWide(width),
		cellsHeigh(height),
		cellSize(cellSize),
		pointsGenerated(0)
	{
		grid = std::vector<std::vector<std::vector<Vector2D>>>(width, std::vector<std::vector<Vector2D>>(height, std::vector<Vector2D>()));
		for (auto outervec : grid)
			for (auto innervec : outervec)
				innervec.reserve(maxElements);
	}

	bool PoissonGenerator::Grid::pointInGrid(const Vector2D& point)
	{
		return point.x >= 0 && point.x < ((float)cellsWide-1) * cellSize && point.y >= 0 && point.y < ((float)cellsHeigh -1) * cellSize;
	}
	Vector2D PoissonGenerator::Grid::getGridXY(const Vector2D& point)
	{
		int gridX = (int)(point.x / cellSize);
		int gridY = (int)(point.y / cellSize);
		return Vector2D(gridX, gridY);
	}
	bool PoissonGenerator::Grid::addPoint(const Vector2D& point)
	{
		Vector2D pointGridXY = getGridXY(point);
		if (pointGridXY.x < 0 || pointGridXY.x >= cellsWide ||
			pointGridXY.y < 0 || pointGridXY.y >= cellsHeigh)
			return false;
		grid[pointGridXY.y][pointGridXY.x].push_back(point);
		pointsGenerated++;
		return true;
	}

	std::vector<Vector2D>* PoissonGenerator::Grid::getPointsInCell(const Vector2D& cell)
	{
		if (cell.x < 0 || cell.x >= cellsWide || cell.y < 0 || cell.y >= cellsHeigh)
			return nullptr;
		return &grid[cell.y][cell.x];
	}

}