//(c) 2018 David S.Gerstl, all rights reserved

#include "adjacencyList.h"
#include <iostream>
#include <limits>

farmingdale::adjacencyList::adjacencyList(int numberOfNodes)
    : size(numberOfNodes) {
  list = new adjNode[numberOfNodes];
  for (int i = 0; i < size; ++i) {
	  list[i].edges = 0;
	  list[i].parent = -1;
  }
}

// we assume that the edge does not already exist
farmingdale::status farmingdale::adjacencyList::addEdge(int fromNode, int toNode, double weight) {
  adjLink* newLink;
  try {
    newLink = new adjLink;
  } catch (std::bad_alloc) {
    return FAILURE;
  }
  newLink->connectsToNode = toNode;
  newLink->weight = weight;
  newLink->next = list[fromNode].edges;
  list[fromNode].edges = newLink;
  return SUCCESS;
}

farmingdale::status farmingdale::adjacencyList::addEdge(int fromX, int fromY, int toX, int toY, double weight) {
	int fromNode = getIndex(fromX, fromY);
	int toNode = getIndex(toX, toY);
	if (0.0 > weight) {
		weight = slDistance(fromNode, toNode);
	}
	if (-1 == fromNode || -1 == toNode) {
		return farmingdale::FAILURE;
	}
	return addEdge(fromNode, toNode, weight);
}
	
farmingdale::status farmingdale::adjacencyList::setNode(int nodeNum, int x,
                                                        int y) {
  if (nodeNum >= size || 0 != list[nodeNum].edges) {
    return FAILURE;
  }
  list[nodeNum].xCoord = x;
  list[nodeNum].yCoord = y;
  return SUCCESS;
}

// faster than pow() for simple square
inline double square(int i) { return double(i * i); }

// Euclidean distance of two nodes in embedded graph
double farmingdale::adjacencyList::slDistance(int fromNode, int toNode) {
  if (fromNode >= size || toNode >= size) {
    return DBL_MAX;
  }
  int x1 = list[fromNode].xCoord;
  int x2 = list[toNode].xCoord;
  int y1 = list[fromNode].yCoord;
  int y2 = list[toNode].yCoord;
  double dist = sqrt(square(x2 - x1) + square(y2 - y1));
  return (dist);
}

// returns the single edge distance between the nodes, MAX_INT otherwise
double farmingdale::adjacencyList::distance(int fromNode, int toNode) {
	if (fromNode >= size || toNode >= size) {
		return INT_MAX;
	}
	adjLink *current = list[fromNode].edges;
	while (0 != current) {
		if (current->connectsToNode == toNode) {
			return current->weight;
		}
		current = current->next;
	}
	return INT_MAX;
}

farmingdale::status farmingdale::adjacencyList::getXY(int index, int &x, int &y) {
	if (index >= size) {
		return FAILURE;
	}
	x = list[index].xCoord;
	y = list[index].yCoord;
	return SUCCESS;
}

int farmingdale::adjacencyList::getIndex(int x, int y) {
	for (int i = 0; i < size; ++i) {
		if (list[i].xCoord == x && list[i].yCoord == y) {
			return i;
		}
	}
	return -1;
}


farmingdale::status farmingdale::adjacencyList::computeAStar(int fromX, int fromY, int toX, int toY, int &length, int *list) {
	int fromNode = getIndex(fromX, fromY);
	int toNode = getIndex(toX, toY);
	if (-1 == fromNode || -1 == toNode) {
		return farmingdale::FAILURE;
	}
	return computeAStar(fromNode, toNode, length, list);
}

farmingdale::status operator&&(farmingdale::status originalA, farmingdale::status originalB) {
	return ((farmingdale::SUCCESS == originalA && farmingdale::SUCCESS == originalB) ?
		farmingdale::SUCCESS : farmingdale::FAILURE);
}
