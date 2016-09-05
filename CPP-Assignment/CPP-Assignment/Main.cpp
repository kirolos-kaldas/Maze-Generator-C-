#include "Main.h"
using namespace std;

//Since we're coding on windows but want to use a linux command on the server
//Only include header file if we're on linux
#ifndef _WIN32
	#include <sys/statvfs.h>
#endif


int main(int argc, char ** argv)
{
	ArgsParser cmdArgs(argc, argv);

	//Check we always have two dashes if we're both generating and saving binary
	if (!EvenDashes(argc, argv, cmdArgs))
	{
		PrintInvalidCmdError();
		return EXIT_FAILURE;
	}

	if (argc <= 1 || (strcmp(argv[1], "--g") != 0 && strcmp(argv[1], "--lb") != 0))
	{
		PrintInvalidCmdError();
		return EXIT_FAILURE;
	}

	//If we specify to load a binary we can't generating
	if (cmdArgs.CmdOptionExists("--lb") && !(cmdArgs.CmdOptionExists("--g")))
	{
		if (!OptionLoadBinary(cmdArgs))
		{
			PrintInvalidCmdError();
			return EXIT_FAILURE;
		}
	}

	else if (cmdArgs.CmdOptionExists("--g") && !(cmdArgs.CmdOptionExists("--lb")))
	{
		Generator gen;

		int width, height, seed, i;

		for (i = 1; i < argc; i++)
		{
			if (strcmp(argv[i], "--sb") == 0 || strcmp(argv[i], "--sv") == 0)
			{
				break;
			}
		}

		//If we have seed, width and height specified
		if (i == 5)
		{
			seed = GetArgVal(argv[ARG_SEED]);
			width = GetArgVal((argv[ARG_WIDTH]));
			height = GetArgVal((argv[ARG_HEIGHT]));
		}
		
		// if no seed was specified but width and height was
		else if (i == 4)
		{
			seed = gen.GenerateSeed(0, INT_MAX);
			width = GetArgVal(argv[ARG_WIDTH - 1]);
			height = GetArgVal(argv[ARG_HEIGHT - 1]);
		}

		//if we're just generating use defaults and generate seed
		else if (i == 3)
		{
			seed = GetArgVal(argv[ARG_SEED]);
			width = DEFAULT_WIDTH;
			height = DEFAULT_HEIGHT;
		}

		//Invalid args, abort
		else
		{
			PrintInvalidCmdError();
			return EXIT_FAILURE;
		}

		// If specified width, height or seed was invalid in some way
		if (seed <= -1 || width <= -1 || height <= -1)
		{
			cout << "Specified seed, width or height was invalid!" << endl;
			PrintInvalidCmdError();
			return EXIT_FAILURE;
		}

		//If we're below the min size
		if (width < DEFAULT_WIDTH || height < DEFAULT_HEIGHT)
		{
			cout << "Width or Height are too small, width must be >= " << DEFAULT_WIDTH <<
				"and height must be >= " << DEFAULT_HEIGHT << endl;
			PrintInvalidCmdError();
			return EXIT_FAILURE;
		}

		//We always want square mazes
		if (width != height)
		{
			int mazeSize = (width < height) ? height : width;
			width = mazeSize;
			height = mazeSize;

			cout << "WARNING: Maze wasn't square, setting maze to max of width and height to be square"
				<< "Maze width and height is now: " << width << endl;
		}

		Maze maze(width, height, seed);

		gen.AldousBroderMaze(maze);

//Checking on Linux if we have enough disk space
// If def since we're using VS2015 on Windows to code
#ifndef _WIN32

		string path = argv[0];  /* Copy the first command-line argument,
								which is the execution line of the program */
		path = path.substr(0, path.find_last_of('/'));  // Remove app name from string

		if (!LINUX_GetAvailableSpace(path.c_str()))
		{
			cout << "There's less than " << (int)MIN_DISK_SPACE_MB << 
				"MB disk space! Please have more disk space available before running again" << endl;

			return EXIT_FAILURE;
		}
#endif

		//Saving
		if (cmdArgs.CmdOptionExists("--sb"))
		{
			bool validBinarySave = false;
			validBinarySave = CheckSaveBinary(cmdArgs, maze);

			if (!validBinarySave)
			{
				PrintInvalidCmdError();
				return EXIT_FAILURE;
			}
		}

		if (cmdArgs.CmdOptionExists("--sv"))
		{
			bool validSVGSave = false;
			validSVGSave = CheckSaveSVG(cmdArgs, maze);

			if(!validSVGSave)
			{
				PrintInvalidCmdError();
				return EXIT_FAILURE;
			}
		}

	}
	
	//Something has gone wrong abort
	else
	{
		PrintInvalidCmdError();
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

//************************************
// Method:    PrintInvalidCmdError
// FullName:  PrintInvalidCmdError
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void PrintInvalidCmdError()
{
	cout << "\n\n";
	cout << "INVALID COMMAND. Please match one of the following: " << endl;

	cout << "./mazer --lb filename.maze --sv filename.svg # load binary file and save svg file \n" 
		"./mazer --g seed --sb filename.maze # generate with seed value, save binary file\n" 
		"./mazer --g seed --sv filename.svg # generate with seed value, save svg file\n" 
		"./mazer --g seed --sb filename.maze --sv filename.svg # gen with seed, save binary, save svg" 
		"./mazer --g seed width height ... #save afterwards" << endl;
}

//************************************
// Method:    GetArgVal
// FullName:  GetArgVal
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: const char * arg
//************************************
int GetArgVal(const char* arg)
{
	if (IsUInt(arg))
		return atoi(arg);
	else
		return -1;
}

//************************************
// Method:    CheckSaveBinary
// FullName:  CheckSaveBinary
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: const ArgsParser & cmdArgs
// Parameter: const Maze & maze
//************************************
bool CheckSaveBinary(const ArgsParser& cmdArgs, const Maze& maze)
{
	string binaryName = cmdArgs.GetCmdOption("--sb");
	if (cmdArgs.CmdOptionExists("--sb") && strcmp(binaryName.c_str(), "") != 0)
	{
		cout << "Saving Binary " << binaryName.c_str() << endl;
		maze.SaveBinary(binaryName.c_str());

		return true;
	}

	return false;
}

//************************************
// Method:    CheckSaveSVG
// FullName:  CheckSaveSVG
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: const ArgsParser & cmdArgs
// Parameter: const Maze & maze
//************************************
bool CheckSaveSVG(const ArgsParser& cmdArgs, const Maze& maze)
{
	string svgName = cmdArgs.GetCmdOption("--sv");
	if (cmdArgs.CmdOptionExists("--sv") && strcmp(svgName.c_str(), "") != 0)
	{
		if (svgName.find(".svg") == std::string::npos)
		{
			cout << "Missing .svg extension on filename to be saved!\n";
			return false;
		}

		cout << "Saving SVG " << svgName.c_str() << endl;
		bool saveSuccessful = maze.SaveSVG(svgName.c_str());
		return saveSuccessful;
	}

	return false;
}


//************************************
// Method:    IsUInt
// FullName:  IsUInt
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: const string & s
//************************************
bool IsUInt(const string& s)
{
	string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

//************************************
// Method:    LINUX_GetAvailableSpace
// FullName:  LINUX_GetAvailableSpace
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: const char * path
//************************************
bool LINUX_GetAvailableSpace(const char* path)
{
	#ifndef _WIN32
		struct statvfs stat;

		if (statvfs(path, &stat) != 0) 
		{
			// error happens, just quits here
			return -1;
		}

		// the available size is f_bsize * f_bavail
		auto space = stat.f_bsize * stat.f_bavail;

		//We want to make sure we have more than 100mb free
		if (space > (1024 * MIN_DISK_SPACE_MB))
		{
			return true;
		}

		else
		{
			return false;
		}

	#endif

	//We're not on the server so don't bother checking
	return true;
}


//************************************
// Method:    EvenDashes
// FullName:  EvenDashes
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: int argc
// Parameter: char * * argv
// Parameter: const ArgsParser & cmdArgs
//************************************
bool EvenDashes(int argc, char ** argv, const ArgsParser& cmdArgs)
{
	for (int i = 1; i < argc; i++)
	{
		string arg = argv[i];
		string option = cmdArgs.GetCmdOption(arg);

		int count = 0;
		for (unsigned int i = 0; i < option.length(); ++i)
		{
			if (option.at(i) == '-')
			{
				count++;
			}
		}

		if (count % 2 != 0)
		{
			return false;
		}
	}

	return true;
}

//************************************
// Method:    OptionLoadBinary
// FullName:  OptionLoadBinary
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: const ArgsParser & cmdArgs
//************************************
bool OptionLoadBinary(const ArgsParser& cmdArgs)
{
	string binaryName = cmdArgs.GetCmdOption("--lb");
	cout << "Loading Binary " << binaryName.c_str() << endl;

	Maze maze(0, 0, 0);
	if (maze.LoadBinary(binaryName.c_str()) == false)
	{
		cout << "The error is in the binary file: " << binaryName.c_str() << endl;
		return false;
	}

	if (cmdArgs.CmdOptionExists("--sv"))
	{
		CheckSaveSVG(cmdArgs, maze);
	}

	return true;
}