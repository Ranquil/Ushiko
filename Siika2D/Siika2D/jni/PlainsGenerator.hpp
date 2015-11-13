#ifndef PLAINSGENERATOR_H
#define PLAINSGENERATOR_H

#include "LevelGenerator.hpp"

class PlainsGenerator : public LevelGenerator
{
public:
	PlainsGenerator(core::Siika2D *siika, std::string name) :
		LevelGenerator(siika, name) {}

	// TODO(Jere): this
};

#endif // PLAINSGENERATOR_H