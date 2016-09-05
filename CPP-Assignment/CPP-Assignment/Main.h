/* ---------------------------------------------------------------------------
** <Main>.h
** <Entry point into the program, uses ArgsParser to assist with processing cmds>
**
** Author: <Kirolos Kaldas (s3545643) & Josh Caratelli (s3492633)>
** Assignment 1, COSC1252/1254 Programming Using C++
** -------------------------------------------------------------------------*/

#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <ctype.h>
#include "ArgsParser.h"
#include "Maze.h"
#include "Generator.h"
#include <limits.h>
#include <string.h>

//Requested by Paul, to check disk space before saving
// 150MB as 1000x1000 Mazes can get to this size
#define MIN_DISK_SPACE_MB 150

//Args in order if we were generating with seed, width and height specified 
enum CmdArgs
{
	ARG_GENERATE = 1,
	ARG_SEED,
	ARG_WIDTH,
	ARG_HEIGHT,
};

// Get the value assoicated with the argument e.g. width of 100
int GetArgVal(const char* arg);
//Check if we want to save a binary and then do so if we need to
bool CheckSaveBinary(const ArgsParser& cmdArgs, const Maze& maze);
//Check if we want to save a svg and then do so if we need to
bool CheckSaveSVG(const ArgsParser& cmdArgs, const Maze& maze);
//Is the cmd arg an unsigned int?
bool IsUInt(const string& s);

//On Linux/Server only, check if we have enough disk space
bool LINUX_GetAvailableSpace(const char* path);
// If we specify a command such as sb, do we have an even amount of 
// dashes in front?
bool EvenDashes(int argc, char ** argv, const ArgsParser& cmdArgs);
//The menu option to load binary, split off into seperate function
bool OptionLoadBinary(const ArgsParser& cmdArgs);
//Print an example list of commands since there's been an error
void PrintInvalidCmdError();
#endif
