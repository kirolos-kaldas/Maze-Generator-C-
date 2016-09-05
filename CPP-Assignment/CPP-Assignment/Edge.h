/* ---------------------------------------------------------------------------
** <Edge>.h
** <Class which contains the structure of a edge used in the maze>
**
** Author: <Kirolos Kaldas (s3545643) & Josh Caratelli (s3492633)>
** Assignment 1, COSC1252/1254 Programming Using C++
** -------------------------------------------------------------------------*/

#ifndef EDGE_H
#define EDGE_H

class Edge
{
public:
	Edge(int fromX, int fromY, int toX, int toY);
	//Copy constructor
	Edge(const Edge& e);
	~Edge();

	int GetFromX() const;
	void SetFromX(int val);

	int GetFromY() const;
	void SetFromY(int val);

	int GetToX() const;
	void SetToX(int val);

	int GetToY() const;
	void SetToY(int val);

	bool operator==(const Edge& other) const;

private:
	int m_fromX;
	int m_fromY;
	int m_toX;
	int m_toY;
};
#endif
