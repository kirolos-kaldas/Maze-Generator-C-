#include "Cell.h"
#include <iostream>

using namespace std;

//************************************
// Method:    Cell
// FullName:  Cell::Cell
// Access:    public 
// Returns:   
// Qualifier: : m_visited(false)
// Parameter: int x
// Parameter: int y
//************************************
Cell::Cell(int x, int y)
	: m_visited(false)
{
	m_x = x;
	m_y = y;
}

//************************************
// Method:    Cell
// FullName:  Cell::Cell
// Access:    public 
// Returns:   
// Qualifier:
// Parameter: const Cell & c
//************************************
Cell::Cell(const Cell& c)
{
	m_x = c.m_x;
	m_y = c.m_y;
	m_visited = c.m_visited;
}


//************************************
// Method:    ~Cell
// FullName:  Cell::~Cell
// Access:    public 
// Returns:   
// Qualifier:
//************************************
Cell::~Cell()
{

}

//************************************
// Method:    GetX
// FullName:  Cell::GetX
// Access:    public 
// Returns:   const int
// Qualifier:
//************************************
const int Cell::GetX()
{
	return m_x;
}

//************************************
// Method:    SetX
// FullName:  Cell::SetX
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int x
//************************************
void Cell::SetX(int x)
{
	m_x = x;
}

//************************************
// Method:    GetY
// FullName:  Cell::GetY
// Access:    public 
// Returns:   const int
// Qualifier:
//************************************
const int Cell::GetY()
{
	return m_y;
}

//************************************
// Method:    SetY
// FullName:  Cell::SetY
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int y
//************************************
void Cell::SetY(int y)
{
	m_y = y;
}

//************************************
// Method:    SetVisited
// FullName:  Cell::SetVisited
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: bool val
//************************************
void Cell::SetVisited(bool val)
{
	m_visited = val;
}

//************************************
// Method:    GetVisited
// FullName:  Cell::GetVisited
// Access:    public 
// Returns:   const bool
// Qualifier:
//************************************
const bool Cell::GetVisited()
{
	return m_visited;
}