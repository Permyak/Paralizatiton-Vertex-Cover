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
#include <time.h>
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

void Graph::Generate(int userVertexCount, double falseFrequency){
	cout << "Generate graph." << endl;
	srand(time(NULL));
	vertexCount = userVertexCount;
	for (int i = 0; i < vertexCount; i++)
	{
		vector<bool> row;
		for (int j = 0; j < i; j++)
		{
			row.push_back(graph[j][i]);
		}
		row.push_back(false);
		for (int j = i+1; j < vertexCount; j++)
		{
			if ((double) rand() / RAND_MAX > falseFrequency){
				row.push_back(true);
			}
			else{
				row.push_back(false);
			}
		}
		graph.push_back(row);
	}

	for (int i = 0; i < vertexCount; i++)
	{
		string row;
		for (int j = 0; j < vertexCount; j++)
		{
			if (graph[i][j])
				row += "1 ";
			else
				row += "0 ";
		}
		cout << row << endl;
	}
}

void Graph::FindVertexCover(){
	vector<int> vertexForCover;
	DeleteIsolateVertex(&vertexForCover);
	if (vertexForCover.size() == 0) {
		cout << "Graph has not got arcs." << endl;
	}
	currentVertexSetNumber = 1;
	vertexSetCount = pow(2, vertexForCover.size());
	int minCoverSize = vertexForCover.size();
	int vertexSet;
	while ((vertexSet = GetNextVertexSet())>0){
		vector<int> currentCover = GetCoverForNumber(vertexForCover, vertexSet);
		//cout << "Current setNumber is " + to_string(vertexSet) << endl;
		PrintCoverInfo(currentCover);
		if (IsSetCovered(currentCover, vertexForCover)){
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
			if (std::find((*vertexForCover).begin(), (*vertexForCover).end(), i) == (*vertexForCover).end()){
				(*vertexForCover).push_back(i);
			}
			if (std::find((*vertexForCover).begin(), (*vertexForCover).end(), j) == (*vertexForCover).end()){
				(*vertexForCover).push_back(j);
			}
		}
	}
	sort((*vertexForCover).begin(), (*vertexForCover).end());
}

int Graph::GetNeighbore(int vertexIndex, vector<int> vertexForCover){
	for (int j = vertexIndex + 1; j < vertexCount; j++)
	{
		if (graph.at(vertexIndex).at(j) == 1)
			return j;
	}
	return -1;
}

int Graph::GetNextVertexSet(){
	return currentVertexSetNumber < vertexSetCount ? currentVertexSetNumber++ : -1;
}

vector<int> Graph::GetCoverForNumber(vector<int> vertexForCover, int coverNumber){
	vector<int> resultCover;
	for (int j = 0; j < vertexForCover.size(); j++)
	{
		//if  j  bit is set then add j vertex to cover
		if ((coverNumber & (1 << j)) != 0)
		{
			resultCover.push_back(vertexForCover.at(j));
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
	//cout << coverString + "]" << endl;
}

bool Graph::IsSetCovered(vector<int> checkingCover, vector<int> vertexCover){
	vector<vector<bool>> graphCopy = graph;
	CoverArcs(checkingCover, &vertexCover, &graphCopy);
	return !HasGraphArcs(graphCopy);
}

void Graph::CoverArcs(vector<int> checkingCover, vector<int>* vertexCover, vector<vector<bool>>* graphCopy){
	for each (int vertexInCover in checkingCover)
	{
		for each (int vertex in *vertexCover)
		{
			if ((*graphCopy)[vertexInCover][vertex]){
				(*graphCopy)[vertexInCover][vertex] = false;
				(*graphCopy)[vertex][vertexInCover] = false;
			}
		}
	}
}

bool Graph::HasGraphArcs(vector<vector<bool>> graphCopy){
	for each (vector<bool> verteces in graphCopy)
	{
		if (std::find(verteces.begin(), verteces.end(), true) != verteces.end()){
			return true;
		}
	}
	return false;
}
