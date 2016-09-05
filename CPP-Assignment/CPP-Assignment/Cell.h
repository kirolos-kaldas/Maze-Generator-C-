/* ---------------------------------------------------------------------------
** <Cell>.h
** <Class which contains the structure of a cell used in the maze>
**
** Author: <Kirolos Kaldas (s3545643) & Josh Caratelli (s3492633)>
** Assignment 1, COSC1252/1254 Programming Using C++
** -------------------------------------------------------------------------*/

#ifndef CELL_H
#define CELL_H

//directions to move while generating
enum direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
	DIRECTION_COUNT
};

class Cell
{
public:
	Cell(int x, int y);
	Cell(const Cell& c);  
	~Cell();

	const int GetX();
	void SetX(int x);

	const int GetY();
	void SetY(int y);

	//Whether cells have been visited while generating or not
	const bool GetVisited();
	void SetVisited(bool val);
	
private:
	int m_x;
	int m_y;
	bool m_visited;
};

#endif
