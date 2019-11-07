//(c) 2018 David S.Gerstl, all rights reserved

#include <iostream>
#include <limits>
#include "adjacencyList.h"
#include <vector>
using namespace std;

farmingdale::status farmingdale::adjacencyList::computeAStar(int fromNode, int toNode, int &length, int *returnList) {
	// note: the constant DBL_MAX is the max value double
	const double LARGE_DISTANCE = DBL_MAX / 2; // feel free to use as initial distance for all nodes
	length = 0;
	
	 vector<int> discoveredNode; //vector for discovered (store node index)
	 vector<int> processed;	//vector for processed
	
	 discoveredNode.push_back(getIndex(fromNode, toNode)); //Place starting node in discoveredNode
	 int lowestWeight = 0;
	 int lowestWeightNodeIndex = 0;

	while (!discoveredNode.empty) //While there are still nodes to be processed
	{
		//Find nodes connected to discovered and add to discovered


		//Find node with lowest weight
		for (int i = 0; i < discoveredNode.size(); i++) {

		}
		//GetIndex, GetXY
	}
	
	std::cout << "Checking Node: " << fromNode << std::endl; // You should print as you explore each node

	// When you complete, returnList[] should contain the list of nodes in order to get from fromNode to toNode
	// length should contain the full path length
	// and you should return SUCCESS
	return FAILURE;
}