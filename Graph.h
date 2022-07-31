#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <random>
#include <unordered_map>
#include <queue>
#include <stack>
#include <cstring>
#include <climits>
#include<bits/stdc++.h>
#include "Vertex.h"


class Graph {

	 map<int, Vertex> adjacencyList;
	 int numVertices;

public:
	Graph();
	void insertVertex(int sightingID, Sighting& currSighting);
	bool insertEdge(int fromID, int toID);
	void setEdges();
	float calculateWeight(int fromID, int toID);
	void printGraph();
	pair<int, int> dijkstra(int fromID, int toID);
	void searchLocationBFS(int sourceID, string city, string state);
	void searchLocationDFS(int sourceID, string city, string state);
  void searchShapeBFS(int sourceID, string shape);
  void searchKeyWordBFS(int sourceID, string keyword);
  void searchID(int sightingID);
  void mostPopularCities(int n);
};

