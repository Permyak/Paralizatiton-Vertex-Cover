#include "stdafx.h"
#include "Graph.h"
#include <stdlib.h>  
#include <iostream>
#include <fstream> 
#include <string> 
#include <vector> 
#include <tchar.h>
using namespace std;


Graph::Graph()
{
}


Graph::~Graph()
{
}

void Graph::ReadGraph(string inputFileName)
{
	cout << "Vertex Cover." << endl;
	ifstream infile("graph.txt");
	infile >> vertexCount;
	for (int i = 0; i<vertexCount; i++)
	{
		vector<int> row;
		int edge;
		for (int j = 0; j<vertexCount; j++)
		{
			infile >> edge;
			row.push_back(edge);
		}
		graph.push_back(row);
	}
}
