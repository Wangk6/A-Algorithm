#pragma once
//(c) 2018 David S.Gerstl, all rights reserved

namespace farmingdale {
	enum status {FAILURE, SUCCESS};
	struct adjNode;
	struct adjLink;
	class adjacencyList;
};

// define an && operation on status (see the test file for use)
farmingdale::status operator&&(farmingdale::status originalA, farmingdale::status originalB);


struct farmingdale::adjLink {
	int connectsToNode;
	double weight;
    adjLink *next;
};



struct farmingdale::adjNode {
	int xCoord;
	int yCoord;
	// unused, except in traversal or A*
	int parent;
	adjLink *edges;
};

// directed graph adj list structure for GPS routing (A*) code
class farmingdale::adjacencyList{
private:
	adjNode * list;
	int size; // number of nodes
public:
	adjacencyList(int numberOfNodes);
	status setNode(int nodeNum, int x, int y);
	status addEdge(int fromNode, int toNode, double weight);
	// returns STRAIGHT LINE distance from fromNode to toNode (assumes embedded graph)
	double slDistance(int fromNode, int toNode); 
	// returns the single edge distance between the nodes, MAX_INT otherwise
	double distance(int fromNode, int toNode);
	// computes the fastest route from fromNode to toNode using the A* algorithm. You will write this. Note that the stub
	// contains some variables that you must fill in
	status computeAStar(int fromNode, int toNode, int &length, int *list); 
	status getXY(int index, int &x, int &y);
	// helper methods
	// returns the index if (x,y) is a point. -1 otherwise
	int getIndex(int x, int y);
	// syntactic sugar: Note if called without weight, it uses euclidean distance
	status addEdge(int fromX, int fromY, int toX, int toY, double weight = -1);
	status computeAStar(int fromX, int fromY, int toX, int toY,int &length, int *list);

};

