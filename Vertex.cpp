#include "Vertex.h"
Vertex::Vertex() {

	int caseId = -1;
	Sighting uninitialized;
	currSighting = uninitialized;


}

Vertex::Vertex(int caseID, Sighting& currSighting) {

	this->caseID = caseID;
	this->currSighting = currSighting;
}

int Vertex::getSightingID() {

	return caseID;
}

Sighting Vertex::getCurrSighting() {

	return currSighting;
}

vector<Edge> Vertex::getadjacentSightings() {

	return adjacentSightings;
}

void Vertex::addAdjacentNode(Edge newEdge) {
	this->adjacentSightings.push_back(newEdge);
}

void Vertex::printVertex(){

	cout << "Sighting ID: " <<  caseID << endl;
	cout << "Summary: " << currSighting.summary << endl;
	cout << "Location: " << currSighting.city  << ", " << currSighting.state << endl;
	cout << "Date/Time: " << currSighting.date_time << endl;
	cout << "Shape: " << currSighting.shape << endl;
	cout << "Duration: " << currSighting.duration << endl;
	cout << "Coordinates: " << currSighting.latitude << " Latitude, " << currSighting.longitude << " Longitude" << endl;
	cout << endl;
}