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

void Graph::ReadGraph(string inputFileName)
{
	cout << "Vertex Cover." << endl;
	ifstream infile("graph.txt");
	infile >> vertexCount;
	for (int i = 0; i < vertexCount; i++)
	{
		vector<bool> row;
		int edge;
		for (int j = 0; j < vertexCount; j++)
		{
			infile >> edge;
			if (edge == 0){
				row.push_back(false);
			}
			else
			{
				row.push_back(true);
			}
		}
		graph.push_back(row);
	}
}

void Graph::Generate(int vertexCount, int falseFrequency){
	cout << "Generate graph." << endl;
	for (int i = 0; i < vertexCount; i++)
	{
		vector<bool> row(vertexCount);
		for (int j = 0; j < vertexCount; j++)
		{
			if (rand() / RAND_MAX > falseFrequency){
				row.push_back(true);
			}
			else{
				row.push_back(false);
			}
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
	int minCoverSize = vertexForCover.size();
	int vertexSet;
	while ((vertexSet = GetNextVertexSet())>0){
		vector<int> currentCover = GetCoverForNumber(vertexForCover.size(), vertexSet);
		cout << "Current setNumber is " + to_string(vertexSet) << endl;
		PrintCoverInfo(currentCover);
		if (IsSetCovered(currentCover, arcsForCover, vertexForCover)){
			if (currentCover.size() < minCoverSize){
				minCoverSize = currentCover.size();
			}
		}
	}
	cout << "Min cover " + to_string(minCoverSize) << endl;
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

void Graph::PrintCoverInfo(vector<int> cover){
	string coverString = "Current cover is [ ";
	for each (int i in cover)
	{
		coverString += to_string(i) + " ";
	}
	cout << coverString + "]" << endl;
}

bool Graph::IsSetCovered(vector<int> checkingCover, vector<Graph::ARC> arcCover, vector<int> vertexCover){
	CoverArcs(checkingCover, &vertexCover);
	return !HasGraphArcs();
}

void Graph::CoverArcs(std::vector<int> checkingCover, std::vector<int>* vertexCover){
	for each (int vertexInCover in checkingCover)
	{
		for each (int vertex in *vertexCover)
		{
			if (graph[vertexInCover][vertex]){
				graph[vertexInCover][vertex] = false;
				graph[vertex][vertexInCover] = false;
			}
		}
	}
}

bool Graph::HasGraphArcs(){
	for each (vector<bool> verteces in graph)
	{
		if (std::find(verteces.begin(), verteces.end(), true) == verteces.end()){
			return true;
		}
	}
	return false;
}
