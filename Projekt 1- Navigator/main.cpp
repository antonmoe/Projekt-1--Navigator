#include <iostream>
#include <vector> 
#include <queue>
#include <stdio.h>


using namespace std; 

#define INF 99999 //TODO: Höherer Wert


struct Node {
	//int id; 
	//int lon, lat; 
	string name;
	bool visited = false;

	Node* prevNode = nullptr; // Pointer auf den vorherigen Knoten im Pfad
	double distance = INF;

	vector<pair<Node*, int>> neighbors; 

	// Nachbarn + Kantengewicht
	// Liste {children Nodes, dist} 
	// {1,2}, {2,4}, ...
};

struct Graph {
	vector<Node*> adjList;
	int size = adjList.size();

};

struct CompareDist {
	bool operator ()(const Node* a, const Node* b) {
		return a->distance > b->distance; // Min-Heap
	}
};

void printPath(Node* target) {
	if (target->prevNode != nullptr) {
		printPath(target->prevNode);
	}
	cout << target->name << " ";
}


void dijkstra(Node* SN, Node* TN, Graph graph) { //{Node, prevNode}
	
	priority_queue <Node*, vector<Node*>, CompareDist > pq; // Min-Heap
	//Node mit der kleinsten Distanz ist oben 


	SN->distance = 0;	// Startknoten Distanz auf 0 setzen
	pq.push(SN); // Startknoten in die Queue einfügen


	while (!pq.empty()) {

		Node* tmpNode = pq.top();

		printf( "Visiting Node: %s with current distance: %f\n", tmpNode->name.c_str(), tmpNode->distance);

		pq.pop(); // Knoten mit der kleinsten Distanz auslesen und entfernen

		if (tmpNode->visited) {
			continue; // Bereits besuchter Knoten
		}
		
		
		printf("Checking neighbors of Node: %s\n", tmpNode->name.c_str());
		for (auto& neighborPair : tmpNode->neighbors) {
			Node* neighbor = neighborPair.first;	//nachbarknoten
			int weight = neighborPair.second;		//dist. zu Nachbarknoten
			int newDist = tmpNode->distance + weight;
			printf("Neighbor: %s, Edge Weight: %d, New Distance: %d, Current Distance: %f\n", neighbor->name.c_str(), weight, newDist, neighbor->distance);
			if (newDist < neighbor->distance) {
				neighbor->distance = newDist;
				neighbor->prevNode = tmpNode;
				pq.push(neighbor); // Aktualisierten Nachbarknoten in die Queue einfügen
			}
		}
		tmpNode->visited = true; // Knoten als besucht markieren
		printf("Node: %s marked as visited.\n", tmpNode->name.c_str());
	}

	// Ergebnis ausgeben
	cout << "\nDistanz "<< SN->name <<" -> "<< TN->name << ":  " << TN->distance << endl;

	// Pfad rekonstruieren u. Ausgeben
	cout << "Pfad: ";
	Node* current = TN;
	vector<Node*> path;

	printPath(TN);

	cout << endl;


};

	
int main() {

	Node A, B, C, D, E, F;
	Graph g;

	A.name = "A";
	B.name = "B";
	C.name = "C";
	D.name = "D";
	E.name = "E";
	F.name = "F";	


	A.neighbors = { { &B, 4 }, { &C, 4 } };
	B.neighbors = { { &A, 4 }, { &C, 2 } };
	C.neighbors = { { &A, 2 }, { &B, 2 }, { &D, 3 }, { &E , 1 }, { &F , 6 } };
	D.neighbors = { { &C, 3 }, { &F, 2 } };
	E.neighbors = { { &C, 1 }, { &F, 3 } };
	F.neighbors = { { &D, 2 }, { &E, 3 } , { &C, 6 } };
	
	g.adjList = { &A, &B, &C, &D , &E , & F};


	dijkstra(&A, &F, g); 

	
	return 0;

}