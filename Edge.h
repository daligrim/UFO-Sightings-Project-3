
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Sighting.h";

class Edge{

	int destID;
	int edgeWeight;
public:
	Edge();
	Edge(int destID, int edgeWeight);
	int getDestID();
	int getEdgeWeight();
};

