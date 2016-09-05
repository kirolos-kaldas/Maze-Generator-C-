/* ---------------------------------------------------------------------------
** <Generator>.h
** <Class responsible for all generations in the maze, seed and algorithims>
**
** Author: <Kirolos Kaldas (s3545643) & Josh Caratelli (s3492633)>
** Assignment 1, COSC1252/1254 Programming Using C++
** -------------------------------------------------------------------------*/

#ifndef GENERATOR_H
#define GENERATOR_H
#include "Maze.h"

class Generator
{
public:
	Generator();
	~Generator();

	//Generate Seed
	int GenerateSeed(const int min, const int max) const;
	//Actually carve paths in maze using AldosBroder algorithim
	void AldousBroderMaze(Maze& maze);
};

#endif
