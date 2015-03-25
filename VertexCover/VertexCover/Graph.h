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
		void Generate(int vertexCount, double falseFrequency);

	private:
		std::vector <std::vector <bool> > graph;
		int vertexCount, currentVertexSetNumber, vertexSetCount;
		int GetNeighbore(int vertexIndex, std::vector<int> vertexForCover);
		void DeleteIsolateVertex(std::vector<int>*);
		int GetNextVertexSet();
		std::vector<int> GetCoverForNumber(std::vector<int> vertexForCover, int coverNumber);
		void PrintCoverInfo(std::vector<int> cover);
		bool IsSetCovered(std::vector<int> CheckingCover, std::vector<int> vertexCover);
		void CoverArcs(std::vector<int> vertexCover, std::vector<int>* verteces, std::vector<std::vector<bool>>* graphCopy);
		bool HasGraphArcs(std::vector<std::vector<bool>> graphCopy);
};

