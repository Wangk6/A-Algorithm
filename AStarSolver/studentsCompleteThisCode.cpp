//(c) 2018 David S.Gerstl, all rights reserved

#include <iostream>
#include <limits>
#include "adjacencyList.h"
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

vector<int> discoveredNode; //list for discovered (store node index)
vector<double> nodeScore;

vector<int> processedNode; //list for processed


farmingdale::status farmingdale::adjacencyList::computeAStar(int fromNode, int toNode, int &length, int *returnList) {
	// note: the constant DBL_MAX is the max value double
	const double LARGE_DISTANCE = DBL_MAX / 2; // feel free to use as initial distance for all nodes
	length = 0;
	int xcord = 0;
	int ycord = 0;

	 discoveredNode.push_back(fromNode); //Place starting node in discoveredNode
	 nodeScore.push_back(0);
	 double lowestWeight = 0;
	 double lowestWeightNodeIndex = 0;

	 int currentNode;
	 
	while (!discoveredNode.empty()) //While there are still nodes to be processed
	{
		//Find lowest weight
		for (int i = 0; i < nodeScore.size(); i++) {
			if (nodeScore[i] <= lowestWeight) { //Track of lowest score
				lowestWeightNodeIndex = discoveredNode[i];
			}
		}
		currentNode = discoveredNode.front(); //Get the node in front 
		getXY(currentNode, xcord, ycord); //Get cords for current node
		
	    cout << "Checking Node: " << currentNode << " (" << xcord << ", " << ycord << ")" << endl; // You should print as you explore each node

		//See if there are any connecting nodes
		//Find nodes connected to discovered and add to discovered

		//Check that it exists (Not sure how to get total number of edges)
		if (int i = list[currentNode].edges != NULL) {
			if (std::find(discoveredNode.begin(), discoveredNode.end(), list[currentNode].edges->connectsToNode) == discoveredNode.end()
				&& std::find(processedNode.begin(), processedNode.end(), list[currentNode].edges->connectsToNode) == processedNode.end()) { //Not already discovered or processed
				discoveredNode.push_back(list[currentNode].edges->connectsToNode);
			}
		}

		if (list[currentNode].edges->next != NULL) {
			if (std::find(discoveredNode.begin(), discoveredNode.end(), list[currentNode].edges->next->connectsToNode) == discoveredNode.end()
				&& std::find(processedNode.begin(), processedNode.end(), list[currentNode].edges->next->connectsToNode) == processedNode.end()) { //Not already discovered or processed
				discoveredNode.push_back(list[currentNode].edges->next->connectsToNode);
			}
		}

		if (list[currentNode].edges->next->next != NULL) {
			if (std::find(discoveredNode.begin(), discoveredNode.end(), list[currentNode].edges->next->next->connectsToNode) == discoveredNode.end()
				&& std::find(processedNode.begin(), processedNode.end(), list[currentNode].edges->next->next->connectsToNode) == processedNode.end()) { //Not already discovered or processed
				discoveredNode.push_back(list[currentNode].edges->next->next->connectsToNode);
			}
		}

		//Find node with lowest weight
		for (int i = 0; i < discoveredNode.size(); i++) {
			//Straight Line distance from current node to end
			//processedNodeScore.push_back(slDistance(i, toNode) + distance(i, i+1));
		}
		//GetIndex, GetXY
	}
	
	// When you complete, returnList[] should contain the list of nodes in order to get from fromNode to toNode
	// length should contain the full path length
	// and you should return SUCCESS
	return FAILURE;
}