#pragma once
void parser(unsigned long long pstartID, unsigned long long pzielID);

#define INF 99999 //TODO: Höherer Wert
#include <string>

#include <vector> 
using namespace std;


struct Node {
	unsigned long long id = 0;
	double lon, lat = 0.0;
	
	bool visited = false;
	double distance = INF;

	Node* prevNode = nullptr; // Pointer auf den vorherigen Knoten im Pfad
	//nach dijkstra durchgang

	float getDistTo(Node* other) {
		return 4;

	}

	vector<pair<Node*, float>> neighbors;
	//<Nachbar node und dist zu diesem knoten vor djikstra>
	//int zu double und mit getDIst verbinden

};

Node* ptrStart; 
Node* ptrZiel;

vector<Node*> adjList;
	