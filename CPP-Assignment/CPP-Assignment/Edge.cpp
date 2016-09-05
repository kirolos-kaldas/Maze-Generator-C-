#include "Edge.h"

//************************************
// Method:    Edge
// FullName:  Edge::Edge
// Access:    public 
// Returns:   
// Qualifier:
// Parameter: int fromX
// Parameter: int fromY
// Parameter: int toX
// Parameter: int toY
//************************************
Edge::Edge(int fromX, int fromY, int toX, int toY)
{
	m_fromX = fromX;
	m_fromY = fromY;
	m_toX = toX;
	m_toY = toY;
}

//************************************
// Method:    ~Edge
// FullName:  Edge::~Edge
// Access:    public 
// Returns:   
// Qualifier:
//************************************
Edge::~Edge()
{

}

//************************************
// Method:    Edge
// FullName:  Edge::Edge
// Access:    public 
// Returns:   
// Qualifier:
// Parameter: const Edge & e
//************************************
Edge::Edge(const Edge& e)
{
	m_fromX = e.m_fromX;
	m_fromY = e.m_fromY;
	m_toX = e.m_toX;
	m_toY = e.m_toY;
}

//************************************
// Method:    operator==
// FullName:  Edge::operator==
// Access:    public 
// Returns:   bool
// Qualifier: const
// Parameter: const Edge & other
//************************************
bool Edge::operator==(const Edge& other) const
{
	return m_fromX == other.GetFromX() &&
		m_fromY == other.GetFromY() &&
		m_toX == other.GetToX() &&
		m_toY == other.GetToY();
}


//************************************
// Method:    GetFromX
// FullName:  Edge::GetFromX
// Access:    public 
// Returns:   int
// Qualifier: const
//************************************
int Edge::GetFromX() const
{ 
	return m_fromX; 
}

//************************************
// Method:    SetFromX
// FullName:  Edge::SetFromX
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int val
//************************************
void Edge::SetFromX(int val)
{ 
	m_fromX = val; 
}

//************************************
// Method:    GetFromY
// FullName:  Edge::GetFromY
// Access:    public 
// Returns:   int
// Qualifier: const
//************************************
int Edge::GetFromY() const
{ 
	return m_fromY; 

}
//************************************
// Method:    SetFromY
// FullName:  Edge::SetFromY
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int val
//************************************
void Edge::SetFromY(int val)
{ 
	m_fromY = val; 
}

//************************************
// Method:    GetToX
// FullName:  Edge::GetToX
// Access:    public 
// Returns:   int
// Qualifier: const
//************************************
int Edge::GetToX() const
{ 
	return m_toX; 
}

//************************************
// Method:    SetToX
// FullName:  Edge::SetToX
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int val
//************************************
void Edge::SetToX(int val)
{
	m_toX = val; 
}

//************************************
// Method:    GetToY
// FullName:  Edge::GetToY
// Access:    public 
// Returns:   int
// Qualifier: const
//************************************
int Edge::GetToY() const
{ 
	return m_toY; 
}

//************************************
// Method:    SetToY
// FullName:  Edge::SetToY
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int val
//************************************
void Edge::SetToY(int val)
{ 
	m_toY = val; 
}




