//(c) 2018 David S.Gerstl, all rights reserved

#include <iostream>
#include <limits>
#include "adjacencyList.h"
#include <vector>
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

	 int lowestWeightNodeVectorIndex = 0; //Index of lowest node in vector

	 double lowestWeight = 0;		
	 int lowestWeightNodeIndex = 0; //Name of node or index in adjlist

	 int currentNode;
	 double connectedWeight = 0;
	 int connectedNode = 0;

	while (!discoveredNode.empty()) //While there are still nodes to be processed
	{
		lowestWeight = nodeScore[0];
		//Find lowest weight
		for (int i = 0; i < nodeScore.size(); i++) {
			getXY(discoveredNode[i], xcord, ycord);
			cout << "lowestweight: " << nodeScore[i] << " Node: (" << xcord << ", " << ycord << ")" << endl;
			if (nodeScore[i] <= lowestWeight) { //Track of lowest score
				lowestWeightNodeIndex = discoveredNode[i];
				lowestWeightNodeVectorIndex = i;
				lowestWeight = nodeScore[i];
			}
		}
		currentNode = lowestWeightNodeIndex; //Get current lowest node
		getXY(currentNode, xcord, ycord); //Get cords for current node
		discoveredNode.erase(discoveredNode.begin() + lowestWeightNodeVectorIndex); //Remove lowest node from discovered as we will begin processing
		nodeScore.erase(nodeScore.begin() + lowestWeightNodeVectorIndex);
		
	    cout <<endl<< "Checking Node: " << currentNode << " (" << xcord << ", " << ycord << ")" << endl; // You should print as you explore each node

		//See if there are any connecting nodes
		//Find nodes connected to discovered and add to discovered

		//Check that it exists (Not sure how to get total number of edge iteration)
		//When added, set currentNode as parent
		int nextConnectedNode;
		int nextNodeWeight;
		connectedNode = list[currentNode].edges->connectsToNode; //7
		connectedWeight = list[currentNode].edges->weight; //7
		while (list[connectedNode].edges != NULL) {
			if (std::find(discoveredNode.begin(), discoveredNode.end(), connectedNode) == discoveredNode.end()
				&& std::find(processedNode.begin(), processedNode.end(), connectedNode) == processedNode.end()) { //Not already discovered or processed

				discoveredNode.push_back(connectedNode); //Add node to discovered
				nodeScore.push_back(connectedWeight);	//Calculate weight

				nextConnectedNode = list[connectedNode].edges->connectsToNode;
				nextNodeWeight = list[connectedNode].edges->weight;
			}
			connectedNode = list[nextConnectedNode].edges->connectsToNode;
			connectedWeight = list[nextNodeWeight].edges->weight;
		}
		//if (list[currentNode].edges != NULL) {
		//	connectedNode = list[currentNode].edges->connectsToNode;
		//	connectedWeight = list[currentNode].edges->weight;
		//	if (std::find(discoveredNode.begin(), discoveredNode.end(), connectedNode) == discoveredNode.end()
		//		&& std::find(processedNode.begin(), processedNode.end(), connectedNode) == processedNode.end()) { //Not already discovered or processed
		//		discoveredNode.push_back(connectedNode); //Add node to discovered
		//		nodeScore.push_back(connectedWeight);	//Calculate weight
		//		if (list[currentNode].edges->next != NULL) {
		//			connectedNode = list[currentNode].edges->next->connectsToNode;
		//			connectedWeight = list[currentNode].edges->next->weight;
		//			if (std::find(discoveredNode.begin(), discoveredNode.end(), connectedNode) == discoveredNode.end()
		//				&& std::find(processedNode.begin(), processedNode.end(), connectedNode) == processedNode.end()) { //Not already discovered or processed
		//				discoveredNode.push_back(connectedNode);
		//				nodeScore.push_back(connectedWeight);
		//				if (list[currentNode].edges->next->next != NULL) {
		//					connectedNode = list[currentNode].edges->next->next->connectsToNode;
		//					connectedWeight = list[currentNode].edges->next->next->weight;
		//					if (std::find(discoveredNode.begin(), discoveredNode.end(), connectedNode) == discoveredNode.end()
		//						&& std::find(processedNode.begin(), processedNode.end(), connectedNode) == processedNode.end()) { //Not already discovered or processed
		//						discoveredNode.push_back(connectedNode);
		//						nodeScore.push_back(connectedWeight);
		//					}
		//				}
		//			}
		//		}
		//	}
		//}

		//Loop through discovered and for each one add the total edge distance
		for (int i = 0; i < discoveredNode.size(); i++) {
			int parentNode = list[discoveredNode[i]].parent;
			int indexNode = discoveredNode[i];
			if (parentNode >= 0 && slDistance(discoveredNode[i], toNode) != 0) {
				//Straight Line distance from current node to end
				//cout << "parentNode: " << parentNode << " discoveredNode: " << discoveredNode[i] << " slDistance: " << slDistance(discoveredNode[i], toNode) << " distance: " << distance(parentNode, indexNode) << endl;
				//cout << "i: " << i << " total: " << slDistance(discoveredNode[i], toNode) + distance(parentNode, indexNode) << endl;
				nodeScore[i] = slDistance(discoveredNode[i], toNode) + distance(parentNode, indexNode);
				//If they have 1 parent and is not the last node

				indexNode = parentNode;
				parentNode = list[parentNode].parent;
				while (indexNode > 0 && parentNode >= 0) {
					//Get the previous link
					nodeScore[i] += distance(parentNode, indexNode);
					//cout << "i1: " << i << " total: " << slDistance(discoveredNode[i], toNode) + distance(parentNode, indexNode) << endl;
					indexNode = parentNode;
					parentNode = list[parentNode].parent;
				}
			}
		}

		if (int i = 0 > 2) {

		}
		//Find node with lowest weight
		//GetIndex, GetXY
	}
	
	// When you complete, returnList[] should contain the list of nodes in order to get from fromNode to toNode
	// length should contain the full path length
	// and you should return SUCCESS
	return FAILURE;
}