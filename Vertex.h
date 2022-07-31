
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Edge.h"

class Vertex {
	int caseID;
	Sighting currSighting;
	vector<Edge> adjacentSightings;

public:

	Vertex();
	Vertex(int sightingID, Sighting& currSighting);
	int getSightingID();
	Sighting getCurrSighting();
	vector<Edge> getadjacentSightings();
	void addAdjacentNode(Edge newEdge);
	void printVertex();
};