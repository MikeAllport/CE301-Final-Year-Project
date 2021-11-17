#pragma once

#include <App/Random.h>

//TODO: Reference diamondsquare and perlin - perlin from https://mrl.cs.nyu.edu/~perlin/noise/
namespace App
{
	extern float convertRange0to1(float value, float min, float max);
	class Noise
	{
	public:
		virtual ~Noise() = default;
		virtual float noise(int x, int y) = 0;
	};

	class DiamondSquare : public Noise
	{
	public:
		DiamondSquare(Random& rng, int size, float rough, float rough_div, bool use_more_water = true);
		float noise(int x, int y) override;
	private:
		const int size;
		float getAverage(const std::vector<float>& in, float random);
		const float roughness_div, rough;
		const bool USE_MORE_WATER;
		void runAlgo(float roughness);
		std::vector<std::vector<float>> noiseMap;
		Random& rng;
	};

	class Perlin : public Noise
	{
	public:
		Perlin(Random& rng, int size);
		Perlin(const Perlin& other);
		Perlin& operator=(const Perlin& other);
		float noise(int x, int y) override;
		float noiseWithFreq(int x, int y, int frequency);
	private:
		void init();
		float noise(float x, float y, float z = 0.f);
		float fade(float t);
		float lerp(float t, float a, float b);
		float grad(int hash, float x, float y, float z = 1);
		Random& rng;
		int size;
		int permutation[256], p[512];
	};
}