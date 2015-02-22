#pragma once
#include <string>
#include <vector>
class Graph
{
public:
	Graph();
	~Graph();
	void ReadGraph(std::string);

private:
	std::vector <std::vector <int> > graph;
	int vertexCount;
};

