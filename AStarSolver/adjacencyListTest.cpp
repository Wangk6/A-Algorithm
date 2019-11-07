//(c) 2018 David S.Gerstl, all rights reserved

#include <iostream>
#include "adjacencyList.h"
int testOne();
int main() {
	int status = testOne();
	if (0 == status) {
		std::cout << "Your code passes" << std::endl;
	} else {
		std::cout << "Your code fails" << std::endl;
	}
	system("pause");
	return 0;
}

int testOne() {
	const int GRAPH_SIZE = 17;
	farmingdale::adjacencyList theGraph(GRAPH_SIZE); //Setup number of nodes
	// set this up--the graph is a resource in the directory
	// nodes are currently numbered from the source clockwise, then the zipzag
	theGraph.setNode(0, 20, 60);
	theGraph.setNode(1, 20, 70);
	theGraph.setNode(2, 50, 75);
	theGraph.setNode(3, 70, 60);
	theGraph.setNode(4, 60, 20);
	theGraph.setNode(5, 20, 10);
	theGraph.setNode(6, 10, 30);
	theGraph.setNode(7, 20, 50);
	theGraph.setNode(8, 40, 60);
	theGraph.setNode(9, 30, 50);
	theGraph.setNode(10, 45, 55);
	theGraph.setNode(11, 35, 40);
	theGraph.setNode(12, 50, 40);
	theGraph.setNode(13, 40, 30);
	theGraph.setNode(14, 55, 30);
	theGraph.setNode(15, 50, 20);

	//Add edges, starting node, ending node connection
	farmingdale::status theStatus = theGraph.addEdge(20, 60, 20, 70);
	theStatus = theStatus && theGraph.addEdge(20, 70, 50, 75);
	theStatus = theStatus && theGraph.addEdge(50, 75, 70, 60);
	theStatus = theStatus && theGraph.addEdge(70, 60, 60, 20);

	theStatus = theStatus && theGraph.addEdge(20, 60, 20, 50);
	theStatus = theStatus && theGraph.addEdge(20, 50, 10, 30);
	theStatus = theStatus && theGraph.addEdge(10, 30, 20, 10);
	theStatus = theStatus && theGraph.addEdge(20, 10, 60, 20);

	theStatus = theStatus && theGraph.addEdge(20, 70, 40, 60);
	theStatus = theStatus && theGraph.addEdge(40, 60, 30, 50);
	theStatus = theStatus && theGraph.addEdge(30, 50, 45, 55);
	theStatus = theStatus && theGraph.addEdge(45, 55, 35, 40);
	theStatus = theStatus && theGraph.addEdge(35, 40, 50, 40);
	theStatus = theStatus && theGraph.addEdge(50, 40, 40, 30);
	theStatus = theStatus && theGraph.addEdge(40, 30, 55, 30);
	theStatus = theStatus && theGraph.addEdge(55, 30, 50, 20);
	theStatus = theStatus && theGraph.addEdge(50, 20, 60, 20);

	// fail if anyone has failed
	if (farmingdale::FAILURE == theStatus) {
		std::cerr << "Error adding edges on line " << __LINE__ << std::endl;
		return 1;
	}

	int length;
	int list[GRAPH_SIZE]; // we don't know the path length, but it can never be > the number of edges

	//Starting node to goal node
	if (farmingdale::FAILURE == theGraph.computeAStar(20, 60, 60, 20, length, list)) {
		std::cerr << "Error computing A* on line " << __LINE__ << std::endl;
		return 1;
	}
	std::cout << "There are " << length << " links in the shortest path from (20,60) to (60,20). They are:" << std::endl;
	double distance = 0.0;
	for (int i = 1; i < length; ++i) {
		int fX, fY, tX, tY;
		theGraph.getXY(list[i - 1], fX, fY);
		theGraph.getXY(list[i], tX, tY);
		std::cout << "\tstep " << i << " from (" << fX << "," << fY << ") to (" << tX << "," << tY << ")" << std::endl;
		std::cout << "\t\t distance is " << theGraph.distance(list[i - 1], list[i]) << std::endl; 
		distance += theGraph.distance(list[i - 1], list[i]);
	}
	std::cout << "\ttotal distance is " << distance << std::endl;
	int soln[] = { 0,7,6,5,4 };
	for (int i = 0; i < length; ++i) {
		if (soln[i] != list[i]) {
			int fX, fY, tX, tY;
			theGraph.getXY(list[soln[i]], fX, fY);
			theGraph.getXY(list[list[i]], tX, tY);
			std::cout << "\tstep " << i << " is wrong. Should be (" << fX<<"," << fY<<
				") but you found (" << tX << "," << tY <<")" << std::endl;
			return 1;
		}
	}
	return 0;
}