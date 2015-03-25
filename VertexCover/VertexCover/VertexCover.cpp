#include "stdafx.h"
#include "Graph.h"
#include <tchar.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
int _tmain(int argc, _TCHAR* argv[])
{
	Graph *graph = new Graph();
	//graph->ReadGraph("graph.txt");
	graph->Generate(10, 0.9);
	graph->FindVertexCover();
	return 0;
}