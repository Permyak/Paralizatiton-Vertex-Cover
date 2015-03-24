#include "stdafx.h"
#include "Graph.h"
#include <algorithm>
#include <stdlib.h>  
#include <iostream>
#include <fstream> 
#include <string> 
#include <vector> 
#include <tchar.h>
#include <functional>
using namespace std;


Graph::Graph()
{
}


Graph::~Graph()
{
}

struct ARC {
	bool isCovered;
	int fromVertex, toVertex;
};

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
	vector<ARC> arcsForCover;
	DeleteIsolateVertex(&vertexForCover);
	if (vertexForCover.size() == 0) {
		cout << "Graph has not got arcs." << endl;
	}
	currentVertexSetNumber = 1;
	vertexSetCount = pow(2, vertexForCover.size());
	int vertexSet;
	while ((vertexSet = GetNextVertexSet())>0){
		vector<int> currentCover = GetCoverForNumber(vertexForCover.size(), vertexSet);
		cout << "Current setNumber is " + to_string(vertexSet) << endl;
		string coverString = "Current cover is [ ";
		for each (int i in currentCover)
		{
			coverString += to_string(i) + " ";
		}
		cout << coverString + "]" << endl;
	}
	cin.get();
}

void Graph::DeleteIsolateVertex(vector<int>* vertexForCover){
	for (int i = 0; i < vertexCount; i++)
	{
		int j = GetNeighbore(i, *vertexForCover);
		if (j != -1){
			(*vertexForCover).push_back(i);
			if (std::find((*vertexForCover).begin(), (*vertexForCover).end(), j) == (*vertexForCover).end()){
				(*vertexForCover).push_back(j);
			}
		}
	}
	sort((*vertexForCover).begin(), (*vertexForCover).end());
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

int Graph::GetNextVertexSet(){
	return currentVertexSetNumber < vertexSetCount ? currentVertexSetNumber++ : -1;
}

vector<int> Graph::GetCoverForNumber(int coverSize, int coverNumber){
	vector<int> resultCover;
	for (int j = 0; j < coverSize; j++)
	{
		//if  j  bit is set then add j vertex to cover
		if ((coverNumber & (1 << j)) != 0)
		{
			resultCover.push_back(j);
		}
	}
	return resultCover;
}
