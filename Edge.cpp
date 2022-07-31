#include "Edge.h"
Edge::Edge() {

	destID = -1;
	edgeWeight = -1;

}

Edge::Edge(int destID, int edgeWeight) {

	this->destID = destID;
	this->edgeWeight = edgeWeight;
}

int Edge::getDestID() {
	return destID;
}

int Edge::getEdgeWeight() {
	return edgeWeight;
}