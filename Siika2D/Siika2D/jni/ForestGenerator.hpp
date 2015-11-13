#ifndef FORESTGENERATOR_H
#define FORESTGENERATOR_H

#include "LevelGenerator.hpp"

class ForestGenerator : public LevelGenerator
{
public:
	ForestGenerator(core::Siika2D *siika, std::string name) :
		LevelGenerator(siika, name) {}

	// TODO(Jere): this
};

#endif // FORESTGENERATOR_H