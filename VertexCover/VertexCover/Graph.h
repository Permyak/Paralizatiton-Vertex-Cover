#pragma once
#include <string>
#include <vector>

class Graph
{
	struct ARC {
		bool isCovered;
		int fromVertex, toVertex;
	};

	public:
		Graph();
		~Graph();
		void ReadGraph(std::string);
		void FindVertexCover();
		void Generate(int vertexCount, int frequency);

	private:
		std::vector <std::vector <bool> > graph;
		int vertexCount, currentVertexSetNumber, vertexSetCount;
		int GetNeighbore(int vertexIndex, std::vector<int> vertexForCover);
		void DeleteIsolateVertex(std::vector<int>*);
		int GetNextVertexSet();
		std::vector<int> GetCoverForNumber(int coverSize, int coverNumber);
		void PrintCoverInfo(std::vector<int> cover);
		bool IsSetCovered(std::vector<int> CheckingCover, std::vector<ARC> arcCover, std::vector<int> vertexCover);
		void CoverArcs(std::vector<int> vertexCover, std::vector<int>* verteces);
		bool HasGraphArcs();
};

