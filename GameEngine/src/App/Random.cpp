#include <gepch.h>
#include "Random.h"

Random::Random()
{
	std::random_device rand;
	seed = rand();
	generator = std::mt19937(seed);
}

Random::Random(const Random& other)
{
	seed = other.seed;
	generator = other.generator;
}

Random::Random(int seed):
	seed(seed)
{
	generator = std::mt19937(seed);
}

int Random::genInt()
{
	return generator();
}

float Random::genFloat()
{
	return generator();
}

int Random::genInt(int a, int b)
{
	std::uniform_int_distribution<int> dist(a, b);
	return dist(generator);
}

float Random::genFloat(float a, float b)
{
	std::uniform_real_distribution<float> dist(a, b);
	return dist(generator);
}

int Random::getSeed()
{
	return seed;
}

int hexToInt(std::string in)
{
	unsigned int x;
	std::stringstream ss;
	ss << std::hex << in;
	ss >> x;
	return x;
}
