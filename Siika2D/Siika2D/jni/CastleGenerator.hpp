#ifndef CASTLEGENERATOR_H
#define CASTLEGENERATOR_H

#include "LevelGenerator.hpp"

class CastleGenerator : public LevelGenerator
{
public:
	CastleGenerator(core::Siika2D *siika, std::string name) :
		LevelGenerator(siika, name) {}

	// TODO(Jere): this
};

#endif // CASTLEGENERATOR_H