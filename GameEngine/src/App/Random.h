#pragma once
#include <iostream>
#include <random>


class Random {
public:
	Random();
	Random(const Random& other);
	Random(int seed);
	int genInt();
	float genFloat();
	int genInt(int a, int b);
	float genFloat(float a, float b);
	int getSeed();

	// quick operator to return a completely random item
	auto operator()(int a, int b) {
		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_int_distribution<int> dist(a, b);
		return dist(gen);
	}
private:
	int seed;
	std::mt19937 generator;
};

int hexToInt(std::string in);