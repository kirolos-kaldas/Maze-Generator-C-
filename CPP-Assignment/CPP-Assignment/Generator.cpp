#include "Generator.h"
#include <vector>
#include <random>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <string>

//************************************
// Method:    Generator
// FullName:  Generator::Generator
// Access:    public 
// Returns:   
// Qualifier:
//************************************
Generator::Generator()
{
	
}

//************************************
// Method:    ~Generator
// FullName:  Generator::~Generator
// Access:    public 
// Returns:   
// Qualifier:
//************************************
Generator::~Generator()
{

}


//************************************
// Method:    GenerateSeed
// FullName:  Generator::GenerateSeed
// Access:    public 
// Returns:   int
// Qualifier: const
// Parameter: const int min
// Parameter: const int max
//************************************
// @Author Paul Miller
int Generator::GenerateSeed(const int min, const int max) const
{
	//get the duration since the unix epoch began
	auto duration = std::chrono::system_clock::now().time_since_epoch();

	//seed with number of milliseconds since the unix epoch began
	mt19937 seed(chrono::duration_cast<chrono::milliseconds>(
		duration).count());

	//set the range for the generator
	uniform_int_distribution<unsigned> dist(min, max);

	return dist(seed);
}


//************************************
// Method:    AldousBroderMaze
// FullName:  Generator::AldousBroderMaze
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: Maze & maze
//************************************
void Generator::AldousBroderMaze(Maze& maze)
{
	unsigned long seed = maze.GetSeed();
	mt19937 mt(seed);
	cout << "Seed for this generator is: " << (int)seed << endl;
	
	int maxWidth = maze.GetWidth();
	int maxHeight = maze.GetHeight();

	const int mazeSize = maxWidth * maxHeight;

	// North, East, South, West
	const int X_Axis_Movement[] = { 0, 1, 0, -1 };
	const int Y_Axis_Movement[] = { 1, 0, -1, 0 };

	//Lamda to generate random number using mersenne twister within range
	auto randNum = [](mt19937& mt, const int min, const int max) -> int { return min + (mt() % (max - min + 1)); };

	int x = randNum(mt, 0, maxWidth - 1);
	int y = randNum(mt, 0, maxHeight - 1);

	Cells& map = maze.GetMap();
	vector<Edge> edges;
	
	//Start at random point
	Cell& randomCell = map[x][y];
	randomCell.SetVisited(true);
	int numVisited = 1;

	while (numVisited < mazeSize)
	{
		direction randomDir = static_cast<direction>(randNum(mt, 0, DIRECTION_COUNT - 1));

		int checkX = randomCell.GetX() + X_Axis_Movement[randomDir];
		int checkY = randomCell.GetY() + Y_Axis_Movement[randomDir];

		//If the cell we could visit exists and isn't visited
		if (maze.ExistsInMaze(checkX, checkY))
		{
			Cell& checkCell = map[checkX][checkY];

			if (!checkCell.GetVisited())
			{
				checkCell.SetVisited(true);
				numVisited++;

				Edge edge(randomCell.GetX(), randomCell.GetY(), checkX, checkY);
				edges.push_back(edge);
			}
			
			//Set our new location to be where we've just moved to
			randomCell = checkCell;
		}
	}

	maze.SetEdges(edges);
	maze.SetNumEdges(edges.size());
}
