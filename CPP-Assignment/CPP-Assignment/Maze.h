/* ---------------------------------------------------------------------------
** <Maze>.h
** <Class responsbile for encaspulating the generated maze, using cell and edge>
**
** Author: <Kirolos Kaldas (s3545643) & Josh Caratelli (s3492633)>
** Assignment 1, COSC1252/1254 Programming Using C++
** -------------------------------------------------------------------------*/

#ifndef MAZE_H
#define MAZE_H
#include "Edge.h"
#include "Cell.h"
#include <vector>
using std::vector;
using namespace std;

typedef vector<vector<Cell>> Cells;

#define  VIEWBOX_WIDTH 500
#define  VIEWBOX_HEIGHT 500
#define DEFAULT_WIDTH 4
#define DEFAULT_HEIGHT 4

class Maze
{
public:
	Maze(int width, int height, unsigned long seed);
	~Maze();
	
	//Is point in the maze?
	bool ExistsInMaze(int x, int y);

	int GetWidth() const;
	void SetWidth(int val);

	int GetHeight() const;
	void SetHeight(int val);
	
	int GetNumEdges() const;
	void SetNumEdges(int val);
	
	vector<Edge> GetEdges() const;
	vector<Edge>& GetEdges();
	void SetEdges(vector<Edge> val);

	//Helper function
	void AddEdge(const Edge edge);
	
	Cells& GetMap();
	void SetMap(Cells val);
	
	unsigned long GetSeed() const;
	void SetSeed(unsigned long val);

	//Specs do not require loading of SVG just saving
	bool SaveSVG(const char *fileName) const;

	bool SaveBinary(const char *fileName) const;
	bool LoadBinary(const char *fileName);

private:
	int m_width;
	int m_height;
	int m_numEdges;
	vector<Edge> m_edges;
	Cells m_map;
	unsigned long m_seed;
};

#endif
