#include "Maze.h"
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

//************************************
// Method:    Maze
// FullName:  Maze::Maze
// Access:    public 
// Returns:   
// Qualifier:
// Parameter: int width
// Parameter: int height
// Parameter: unsigned long seed
//************************************
Maze::Maze(int width, int height, unsigned long seed)
{
	m_width = width;
	m_height = height;
	m_seed = seed;

	m_map.resize(m_width);

	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
		{
			Cell cell = Cell(i, j);
			m_map[i].push_back(cell);
		}
	}
}

//************************************
// Method:    ~Maze
// FullName:  Maze::~Maze
// Access:    public 
// Returns:   
// Qualifier:
//************************************
Maze::~Maze()
{

}

//************************************
// Method:    ExistsInMaze
// FullName:  Maze::ExistsInMaze
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: int x
// Parameter: int y
//************************************
bool Maze::ExistsInMaze(int x, int y)
{
	return (x >= 0 && x < m_width && y >= 0 && y < m_height);
}

//************************************
// Method:    AddEdge
// FullName:  Maze::AddEdge
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: const Edge edge
//************************************
void Maze::AddEdge(const Edge edge)
{
	m_edges.push_back(edge);
	m_numEdges++;
}

//************************************
// Method:    SaveSVG
// FullName:  Maze::SaveSVG
// Access:    public 
// Returns:   bool
// Qualifier: const
// Parameter: const char * fileName
//************************************
bool Maze::SaveSVG(const char *fileName) const
{
	cout << "Saving svg maze: " << fileName << endl;

	ofstream svgFile(fileName, ofstream::out);

	if (!svgFile)
	{
		cout << "Failed to save file!\n";
		return false;
	}

	const vector<Edge> edges = m_edges;
	const int width = m_width;
	const int height = m_height;
	const int svgWidth = 5 * width;
	const int svgHeight = 5 * width;

	const float strokeWidth = svgWidth * (1 / (float)edges.size()) * 0.062;

	svgFile << "<svg viewBox='0 0 1 1' width='" << VIEWBOX_WIDTH << "' height='" << VIEWBOX_HEIGHT << "' "
		"xmlns='http://www.w3.org/2000/svg'>\n"
		"<rect width='" << svgWidth << "' height='" << svgHeight << "' style='fill: black' />" << endl;

	for (auto edge : edges)
	{
		svgFile << "<line stroke='white' stroke-width='" << strokeWidth << "'"
			" x1='" << float(edge.GetFromX()) / width << "'"
			" y1='" << float(edge.GetFromY()) / height << "'"
			" x2='" << float(edge.GetToX()) / width << "'"
			" y2='" << float(edge.GetToY()) / height << "'/>\n";

		svgFile << "<!-- x1='" << edge.GetFromX() << "-->\n";
		svgFile << "<!-- y1='" << edge.GetFromY() << "-->\n";
		svgFile << "<!-- x2='" << edge.GetToX() << "-->\n";
		svgFile << "<!-- y2='" << edge.GetToY() << "-->\n";
	}

	svgFile << "</svg>" << flush;
	svgFile.close();

	return true;
}


//************************************
// Method:    SaveBinary
// FullName:  Maze::SaveBinary
// Access:    public 
// Returns:   bool
// Qualifier: const
// Parameter: const char * fileName
//************************************
bool Maze::SaveBinary(const char *fileName) const
{
	ofstream file(fileName, ios::binary);

	if (!file)
	{
		cout << "Failed to save file!\n";
		return false;
	}
	
	file.write((char*)&m_width, sizeof(int));
	file.write((char*)&m_height, sizeof(int));
	file.write((char*)&m_numEdges, sizeof(int));

	for (int i = 0; i < m_numEdges; i++)
	{
		int fromX = m_edges[i].GetFromX();
		int fromY = m_edges[i].GetFromY();
		int toX = m_edges[i].GetToX();
		int toY = m_edges[i].GetToY();

		file.write((char*)&fromX, sizeof(int));
		file.write((char*)&fromY, sizeof(int));
		file.write((char*)&toX, sizeof(int));
		file.write((char*)&toY, sizeof(int));
	}

	file.close();

	return true;
}

//************************************
// Method:    LoadBinary
// FullName:  Maze::LoadBinary
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: const char * fileName
//************************************
bool Maze::LoadBinary(const char *fileName)
{
	ifstream file(fileName, ios::binary);

	int fromX, fromY, toX, toY, height, width, numEdges;

	if (file.is_open())
	{
		file.read((char*)&width, sizeof(int));
		file.read((char*)&height, sizeof(int));
		file.read((char*)&numEdges, sizeof(int));

		if (width < DEFAULT_WIDTH && height < DEFAULT_HEIGHT)
		{
			cout << "Error in loading binary file: Invalid dimensions specified for the maze." << endl;
			return false;
		}

		if (width != height)
		{
			cout << "Error in loading binary file: The width and height are not equal." << endl;
			return false;
		}

		int maxSize = width * height;

		if (numEdges != maxSize - 1)
		{
			cout << "Error in loading binary file: Invalid number of edges." << endl;
			return false;
		}

		m_width = width;
		m_height = height;
		m_numEdges = numEdges;

		for (int i = 0; i < numEdges; i++)
		{
			file.read((char*)&fromX, sizeof(int));
			file.read((char*)&fromY, sizeof(int));
			file.read((char*)&toX, sizeof(int));
			file.read((char*)&toY, sizeof(int));

			Edge edge(fromX, fromY, toX, toY);
			m_edges.push_back(edge);
		}
	}

	else
	{
		return false;
	}

	file.close();

	return true;
}

//************************************
// Method:    GetWidth
// FullName:  Maze::GetWidth
// Access:    public 
// Returns:   int
// Qualifier: const
//************************************
int Maze::GetWidth() const
{ 
	return m_width; 
}

//************************************
// Method:    SetWidth
// FullName:  Maze::SetWidth
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int val
//************************************
void Maze::SetWidth(int val)
{ 
	m_width = val; 
}

//************************************
// Method:    GetHeight
// FullName:  Maze::GetHeight
// Access:    public 
// Returns:   int
// Qualifier: const
//************************************
int Maze::GetHeight() const
{ 
	return m_height; 
}

//************************************
// Method:    SetHeight
// FullName:  Maze::SetHeight
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int val
//************************************
void Maze::SetHeight(int val)
{ 
	m_height = val; 
}

//************************************
// Method:    GetNumEdges
// FullName:  Maze::GetNumEdges
// Access:    public 
// Returns:   int
// Qualifier: const
//************************************
int Maze::GetNumEdges() const
{ 
	return m_numEdges; 
}

//************************************
// Method:    SetNumEdges
// FullName:  Maze::SetNumEdges
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int val
//************************************
void Maze::SetNumEdges(int val)
{ 
	m_numEdges = val; 
}

//************************************
// Method:    GetEdges
// FullName:  Maze::GetEdges
// Access:    public 
// Returns:   vector<Edge>
// Qualifier: const
//************************************
vector<Edge> Maze::GetEdges() const
{ 
	return m_edges; 
}

//************************************
// Method:    GetEdges
// FullName:  Maze::GetEdges
// Access:    public 
// Returns:   vector<Edge>&
// Qualifier:
//************************************
vector<Edge>& Maze::GetEdges()
{ 
	return m_edges; 
}

//************************************
// Method:    SetEdges
// FullName:  Maze::SetEdges
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: vector<Edge> val
//************************************
void Maze::SetEdges(vector<Edge> val)
{ 
	m_edges = val; 
}


//************************************
// Method:    GetMap
// FullName:  Maze::GetMap
// Access:    public 
// Returns:   Cells&
// Qualifier:
//************************************
Cells& Maze::GetMap()
{ 
	return m_map; 
}

//************************************
// Method:    SetMap
// FullName:  Maze::SetMap
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: Cells val
//************************************
void Maze::SetMap(Cells val)
{ 
	m_map = val; 
}

//************************************
// Method:    GetSeed
// FullName:  Maze::GetSeed
// Access:    public 
// Returns:   unsigned long
// Qualifier: const
//************************************
unsigned long Maze::GetSeed() const
{ 
	return m_seed; 
}

//************************************
// Method:    SetSeed
// FullName:  Maze::SetSeed
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: unsigned long val
//************************************
void Maze::SetSeed(unsigned long val)
{ 
	m_seed = val; 
}