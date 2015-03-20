#include "stdafx.h"
#include "Graph.h"
#include <tchar.h>

int _tmain(int argc, _TCHAR* argv[])
{
	Graph *graph = new Graph();
	graph->ReadGraph("graph.txt");
	graph->FindVertexCover();
	return 0;
}