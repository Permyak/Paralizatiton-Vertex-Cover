#include "stdafx.h"
#include "Graph.h"
#include <algorithm>
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

void Graph::FindVertexCover(){
	vector<int> vertexForCover;
	vector<int> arcsForCover;
	for (int i = 0; i < vertexCount; i++)
	{
		int j = GetNeighbore(i, vertexForCover);
		if (j != -1){
			vertexForCover.push_back(i);
			if (std::find(vertexForCover.begin(), vertexForCover.end(), j) == vertexForCover.end()){
				vertexForCover.push_back(j);
			}
		}
	}
	sort(vertexForCover.begin, vertexForCover.end);
}

int Graph::GetNeighbore(int vertexIndex, vector<int> vertexForCover){
	if (std::find(vertexForCover.begin(), vertexForCover.end(), vertexIndex) == vertexForCover.end()){
		for (int j = vertexIndex + 1; j < vertexCount; j++)
		{
			if (graph.at(vertexIndex).at(j) == 1)
				return j;
		}
	}
	return -1;
}
