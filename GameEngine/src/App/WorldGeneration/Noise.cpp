#include <gepch.h>
#include "Noise.h"


namespace App
{

	DiamondSquare::DiamondSquare(Random& rng, int size, float roughness, float rough_div, bool use_more_water) :
		rng(rng), size(size), rough(roughness), USE_MORE_WATER(use_more_water), roughness_div(rough_div)
	{
		runAlgo(roughness);
	}

	void DiamondSquare::runAlgo(float roughness)
	{
		//base case
		std::vector<std::vector<float>> map(size, std::vector<float>(size));
		float low = 0;
		std::unique_ptr<float> lowFact(nullptr);
		if (USE_MORE_WATER)
			lowFact = std::unique_ptr<float>(&roughness);
		else
			lowFact = std::unique_ptr<float>(&low);
		map[0][0] = rng.genFloat(-*lowFact, roughness);
		map[0][size - 1] = rng.genFloat(-*lowFact, roughness);
		map[size - 1][0] = rng.genFloat(-*lowFact, roughness);
		map[size - 1][size - 1] = rng.genFloat(-*lowFact, roughness);
		float max = INT_MIN, min = INT_MAX;
		for (int step = size / 2; step > 0; step /= 2, roughness *= roughness_div)
		{
			//squareStep(map, size, i, roughness, random);
			//diamondStep(map, size, i, roughness, random);
			for (int row = step; row < size; row += 2 * step)
			{
				for (int col = step; col < size; col += 2 * step)
				{
					// diamond step, get each corner, set center to average + random roughness
					float topLeft = map[row - step][col - step];
					float topRight = map[row - step][col + step];
					float bottomLeft = map[row + step][col - step];
					float bottomRight = map[row + step][col - step];
					float centre = map[row][col] = map[row][col] = 
						getAverage(std::vector<float>{ topLeft, topRight, bottomLeft, bottomRight }, rng.genFloat(-*lowFact, roughness));
					

					//square step
					float midTop = map[row - step][col] = 
						getAverage({ topLeft, topRight, centre }, rng.genFloat(-*lowFact, roughness));
					float midRight = map[row][col + step] =
						getAverage({ topRight, bottomRight, centre}, rng.genFloat(-*lowFact, roughness));;
					float midBot = map[row + step][col] = 
						getAverage({ bottomLeft, bottomRight, centre}, rng.genFloat(-*lowFact, roughness));
					float midLeft = map[row][col - step] = 
						getAverage({ bottomLeft, topLeft, centre }, rng.genFloat(-*lowFact, roughness));;

					// get max
					max = std::max({ max, centre, midTop, midRight, midBot, midLeft, topLeft, topRight, bottomLeft, bottomRight });
					min = std::min({ min, centre, midTop, midRight, midBot, midLeft, topLeft, topRight, bottomLeft, bottomRight });
				}
			}
		}
		lowFact.release();
		// sets all values between 0-1
		for (int i = 0; i < size; ++i)
			for (int j = 0; j < size; ++j)
				map[i][j] = convertRange0to1(map[i][j], min, max);
		noiseMap = map;
	}

	float DiamondSquare::noise(int y, int x)
	{
		int newX = x % (2 * size), newY = y % (2 * size);
		if (newX > size)
		{
			int tempx = newX;
			newX = 1 * size;
			newX -= tempx % size;
		}
		if (newY > size)
		{
			int tempy = newY;
			newY = 1 * size;
			newY -= tempy % size;
		}
		return noiseMap[newY][newX];
	}

	float DiamondSquare::getAverage(const std::vector<float>& in, float random)
	{
		float result = std::accumulate(in.begin(), in.end(), 0);
		result /= in.size();
		result += random;
		return result;
	}

	Perlin::Perlin(Random& rng, int size) : 
		rng(rng), size(size)
	{
		init();
	}

	Perlin::Perlin(const Perlin& other) :
		rng(other.rng)
	{
		init();
	}

	Perlin& Perlin::operator=(const Perlin& other)
	{
		rng = other.rng;
		init();
		return *this;
	}

	void Perlin::init()
	{
		for (int i = 0; i < 256; i++)
			permutation[i] = rng.genInt(0, 255);
		for (int i = 0; i < 256; i++)
			p[256 + i] = p[i] = permutation[i];
	}

	float Perlin::noise(int x, int y)
	{
		float newx = x / (float)size;
		float newy = y / (float)size;
		return noise(newx, newy);
	}

	float Perlin::noiseWithFreq(int x, int y, int frequency)
	{
		float noiseVal = noise(x * frequency, y * frequency);
		noiseVal = convertRange0to1(noiseVal, -1, 1);
		return noiseVal;
	}

	float Perlin::noise(float x, float y, float z)
	{
		int X = (int)std::floor(x) & 255,                  // FIND UNIT CUBE THAT
			Y = (int)std::floor(y) & 255,                  // CONTAINS POINT.
			Z = (int)std::floor(z) & 255;
		x -= std::floor(x);                                // FIND RELATIVE X,Y,Z
		y -= std::floor(y);                                // OF POINT IN CUBE.
		z -= std::floor(z);
		float u = fade(x),                                // COMPUTE FADE CURVES
			v = fade(y),                                // FOR EACH OF X,Y,Z.
			w = fade(z);
		int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z,      // HASH COORDINATES OF
			B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;      // THE 8 CUBE CORNERS,

		return lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z),  // AND ADD
			grad(p[BA], x - 1, y, z)), // BLENDED
			lerp(u, grad(p[AB], x, y - 1, z),  // RESULTS
				grad(p[BB], x - 1, y - 1, z))),// FROM  8
			lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1),  // CORNERS
				grad(p[BA + 1], x - 1, y, z - 1)), // OF CUBE
				lerp(u, grad(p[AB + 1], x, y - 1, z - 1),
					grad(p[BB + 1], x - 1, y - 1, z - 1))));
	}
	float Perlin::fade(float t)
	{
		return t * t * t * (t * (t * 6 - 15) + 10);
	}
	float Perlin::lerp(float t, float a, float b)
	{
		return a + t * (b - a);
	}
	float Perlin::grad(int hash, float x, float y, float z)
	{
		int h = hash & 15;                      // CONVERT LO 4 BITS OF HASH CODE
		double u = h < 8 ? x : y,                 // INTO 12 GRADIENT DIRECTIONS.
			v = h < 4 ? y : h == 12 || h == 14 ? x : z;
		return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
	}
}