#pragma once
#include <string>
#include <vector>
class Graph
{
public:
	Graph();
	~Graph();
	void ReadGraph(std::string);
	void FindVertexCover();

private:
	std::vector <std::vector <int> > graph;
	int vertexCount;
	int GetNeighbore(int vertexIndex, std::vector<int> vertexForCover);
	void DeleteIsolateVertex(std::vector<int>);
};

