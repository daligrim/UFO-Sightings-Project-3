#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include<bits/stdc++.h>
#include <utility>
#include "Hashtable.h"
using namespace std;
typedef pair<int, pair<string,string>> pairOfIntAndStringPair;

Hashtable::Hashtable() {
	arrayOfSightings = new Sighting *[200000];
    numSightings = 0;
	numBuckets = 200000;
}

Hashtable::~Hashtable() {
    delete[] arrayOfSightings;
}

void Hashtable::printSighting(Sighting* sighting) {
	cout << "Sighting ID: " << sighting->ID << endl;
	cout << "Summary: " << sighting->summary << endl;
	cout << "Location: " << sighting->city << ", " << sighting->state << endl;
	cout << "Date/Time: " << sighting->date_time << endl;
	cout << "Shape: " << sighting->shape << endl;
	cout << "Duration: " << sighting->duration << endl;
	cout << "Coordinates: " << sighting->latitude << " Latitude, " << sighting->longitude << " Longitude" << endl;
    cout << endl;
}

//Portions of this hash function are based on the hash function, djb2, developed by Dan Bernstein
int Hashtable::hashFunction(int hashID) {
    int hashValue = 5381;
	string stringID = to_string(hashID);
	char* stringChars = &stringID[0];
    int num = *stringChars++;
    while (num != 0) {
        hashValue = ((hashValue << 5) + hashValue) + num;
        num = *stringChars++;
    }
	if (hashValue - 177621 >= 0) {
		hashValue -= 177621;
	}
	while (hashValue >= numBuckets) {
        hashValue = hashValue - 177621;
    }
    return hashValue;
}

void Hashtable::insertSighting(Sighting* aSighting) {
	
    //Add to the count of number of sightings in the hash table
    numSightings++;
    //Determine the index for the sighting using the hash function
    int index = hashFunction(aSighting->ID);
	//Create a variable for tracking if the sighting has been inserted
	bool inserted = false;
    
	//Iterate through the table until an empty spot is found
	while (!inserted) {

		//Check if the spot is empty
		if (arrayOfSightings[index] == nullptr) {
			arrayOfSightings[index] = aSighting;
			inserted = true;
		}
		else if (index+1 >= numBuckets) {
			index = 0;
		}
		else {
			index++;
		}
	}
}

void Hashtable::searchByShape(string shapeName) {

	//Create a variable for tracking how many instances of the shape there are
	int numInstances = 0;

    //Iterate through the entire table to find sightings with the specified shape
    for (int i = 0; i < numBuckets; i++) {

        //If there is a sighting stored in the spot, print the sighting
        if (arrayOfSightings[i] != nullptr) {

            //If the sighting does contain the shape, print it
            if (shapeName.compare(arrayOfSightings[i]->shape) == 0) {
                printSighting(arrayOfSightings[i]);
                numInstances++;
            }
        }
    }

    if (numInstances == 0) {
        cout << "The shape, " << shapeName << ", was not reported in any sightings." << endl;
    }
	else {
		cout << "There are " << numInstances << " UFO sightings of " << numSightings << " that describe the UFO shape as a " << shapeName << endl;
		cout << "The sightings described as a " << shapeName << "account for " << fixed << setprecision(2) << (numInstances/(float)numSightings)*100 << '%' << " of the total number of reported sightings." << endl;
	}
  cout << endl;
}

void Hashtable::numSightingsInCity(string cityName, string stateName) {

	//Create a variable for tracking the number of sightings in the city
	int numCitySightings = 0;
    
    //Iterate through the hash table to find each instance
    for (int index = 0; index < numBuckets; index++) {

        //Ensure there are sightings stored in the current spot
        if (arrayOfSightings[index] != nullptr) {

            //If both the city and state match, add it to the count
            if (cityName.compare(arrayOfSightings[index]->city) == 0 && stateName.compare(arrayOfSightings[index]->state) == 0) {
                numCitySightings++;
				printSighting(arrayOfSightings[index]);
            }
        }
    }

	//Print the total number of sightings in the city
	if (numCitySightings == 0) {
		cout << "No sightings were reported in " << cityName << ", " << stateName << "." << endl;
	}
	else {
		cout << "A total of " << numCitySightings << " of " << numSightings << " UFO sightings were reported in " << cityName << ", " << stateName << "." << endl;
    	cout << "The number of sightings in this city accounts for " << fixed << setprecision(2) << (numCitySightings/(float)numSightings)*100 << '%' << " of the total number of reported sightings." << endl;
	}
  cout << endl;
}

void Hashtable::mostPopularCities(int N) {

	//Create a map to gather the number of sightings in each city
	map<pair<string,string>, int> citySightingCounts;

	//Iterate through the hash table to tally amounts of sightings for each city
	for (int index = 0; index < numBuckets; index++) {
		if (arrayOfSightings[index] != nullptr) {
			citySightingCounts[make_pair(arrayOfSightings[index]->city, arrayOfSightings[index]->state)] = citySightingCounts[make_pair(arrayOfSightings[index]->city, arrayOfSightings[index]->state)] + 1;
		}
	}

	//Create a minimum priority queue to determine the N most popular cities
	priority_queue<pairOfIntAndStringPair, vector<pairOfIntAndStringPair>, greater<pairOfIntAndStringPair> > minQueue;

	//Iterate through the map and add the most popular cities to the queue
	for (map<pair<string,string>, int>::iterator it = citySightingCounts.begin(); it != citySightingCounts.end(); ++it) {
		if (minQueue.size() < N) {
			minQueue.push(make_pair(it->second, it->first));
		}
		else if (it->second > minQueue.top().first) {
			minQueue.pop();
			minQueue.push(make_pair(it->second, it->first));
		}
	}

	//Add the most popular cities to a vector for printing purposes
	vector<pairOfIntAndStringPair> popularCities;
	while (!minQueue.empty()) {
		popularCities.push_back(minQueue.top());
		minQueue.pop();
	}

	cout << "The " << N << " cities with the most sightings are: " << endl;
	for (int i = popularCities.size()-1; i >= 0; i--) {
		cout << N-i << ". " << popularCities[i].second.first << ", " << popularCities[i].second.second << " with " << popularCities[i].first << " sightings, which accounts for " << fixed << setprecision(2) << (popularCities[i].first/(float)numSightings)*100 << '%' << " of the total number of reported sightings." << endl;
	}
  cout << endl;
}

void Hashtable::searchByKeyword(string keyword) {

	//Create a variable for tracking if the keyword was found
	bool wasFound = false;
	//Create a variable for tracking the number of instances found
	int numInstances = 0;

	//Iterate through the hash table and search every summary for the keyword
	for (int index = 0; index < numBuckets; index++) {
		if (arrayOfSightings[index] != nullptr) {
			if (arrayOfSightings[index]->summary.find(keyword) != std::string::npos) {
				numInstances++;
				wasFound = true;
				printSighting(arrayOfSightings[index]);
			}
		}
	}

	if (wasFound) {
		cout << "The keyword, " << keyword << ", was found in " << numInstances << " of " << numSightings << " UFO sighting summaries, which accounts for " << fixed << setprecision(2) << (numInstances/(float)numSightings)*100 << '%' << " of the total number of reported sightings." << endl;
	}
	else {
		cout << "The keyword, " << keyword << ", was not found in any sighting summaries." << endl;
	}
  cout << endl;
}

void Hashtable::printHashtable() {
	//Iterate through the hash table and print each sighting
	for (int index = 0; index < numBuckets; index++) {
    if (arrayOfSightings[index] != nullptr) {
      printSighting(arrayOfSightings[index]);
    }
	}
}

void Hashtable::findID(int _ID) {
	
	//Determine the hash value for the ID
	int IDHash = hashFunction(_ID);
	//Create a variable for tracking if the ID was found
	bool wasFound = false;
	//Create a variable for tracking if the end of the array was reached
	bool endReached = false;

	//Iterate through the table starting at the hash value
	while (IDHash < numBuckets) {
		
		if (arrayOfSightings[IDHash] == nullptr) {
			break;
		}
		else if (arrayOfSightings[IDHash]->ID == _ID) {
			
			printSighting(arrayOfSightings[IDHash]);
			wasFound = true;
			break;
		}
		else if (IDHash+1 == numBuckets && !endReached) {
			endReached = true;
			IDHash = 0;
		}
		else {
			IDHash++;
		}
	}

	if (!wasFound) {
		cout << "Case ID " << _ID << " does not exist." << endl;
	}
  cout << endl;
}

int Hashtable::getLoadFactor() {
	return numSightings/numBuckets;
}

void Hashtable::reHash() {

	//Determine the new hash table size
	int newNumBuckets = numSightings/0.75;

	//Create the expanded hash table
	Sighting **tempArrayOfSightings = new Sighting *[newNumBuckets];
	for (int i = 0; i < numBuckets; i++) {
		tempArrayOfSightings[i] = arrayOfSightings[i];
	}

	//Reassign variables
	arrayOfSightings = tempArrayOfSightings;
	numBuckets = newNumBuckets;
}

int Hashtable::getNumSightings() {
	return numSightings;
}