#pragma once
#include <string>
class Graph
{
public:
	Graph();
	~Graph();
	void ReadGraph(std::string);
private:
	vector< vector <int> > graph;
	int vertexCount;
};

