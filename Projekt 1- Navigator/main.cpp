#include <iostream> 
#include <vector> 
#include <queue>
#include <stdio.h>
#include "head.h"
#include <math.h>



using namespace std; 

#define INF 999999 //TODO: Höherer Wert


struct CompareDist {
	bool operator ()(const Node* a, const Node* b) {
		return a->distance > b->distance; // Min-Heap
	}
};

void printPath(Node* target) {
	if (target->prevNode != nullptr) {
		printPath(target->prevNode);
	} 
	printf("%llu -> ", target->id);
	
}


void dijkstra(Node* SN, Node* TN, vector<Node*> graph) { //{Node, prevNode}
	
	priority_queue <Node*, vector<Node*>, CompareDist > pq; // Min-Heap
	//Node mit der kleinsten Distanz ist oben 


	SN->distance = 0;	// Startknoten Distanz auf 0 setzen
	pq.push(SN);        // Startknoten in die Queue einfügen


	while (!pq.empty()) {

		Node* tmpNode = pq.top();

		printf( "Visiting Node: %llu with current distance: %f\n", tmpNode->id, tmpNode->distance);

		pq.pop(); // Knoten mit der kleinsten Distanz auslesen und entfernen

		if (tmpNode->visited) {
			continue; // Bereits besuchter Knoten
		}
		
		
		printf("Checking neighbors of Node: %llu\n", tmpNode->id);
		for (auto& neighborPair : tmpNode->neighbors) {
			Node* neighbor = neighborPair.first;	//nachbarknoten
			int weight = neighborPair.second;		//dist. zu Nachbarknoten
			int newDist = tmpNode->distance + weight;
			printf("Neighbor: %d, Edge Weight: %d, New Distance: %d, Current Distance: %f\n", neighbor->id, weight, newDist, neighbor->distance);
			if (newDist < neighbor->distance) {
				neighbor->distance = newDist;
				neighbor->prevNode = tmpNode;
				pq.push(neighbor); // Aktualisierten Nachbarknoten in die Queue einfügen
			}
		}
		tmpNode->visited = true; // Knoten als besucht markieren
		printf("Node: %llu marked as visited.\n", tmpNode->id);
	}

	
	// Pfad rekonstruieren u. Ausgeben
	cout << "Pfad: ";
	Node* current = TN;	//Target Node
	vector<Node*> path;

	printPath(TN);

	cout << endl;


};

	
int main() {

	vector<Node*> graph;
	parser(1, 2); 

	Node A, B, C, D, E, F;


	A.id = 1;
	B.id = 2;
	C.id = 3;
	D.id = 4;
	E.id = 5;
	F.id = 6;



	A.neighbors = { { &B, A.getDistTo(&B)}, {&C, 4}};
	B.neighbors = { { &A, 4 }, { &C, 2 } };
	C.neighbors = { { &A, 2 }, { &B, 2 }, { &D, 3 }, { &E , 1 }, { &F , 6 } };
	D.neighbors = { { &C, 3 }, { &F, 2 } };
	E.neighbors = { { &C, 1 }, { &F, 3 } };
	F.neighbors = { { &D, 2 }, { &E, 3 } , { &C, 6 } };
	
	graph = { &A, &B, &C, &D , &E , & F};


	dijkstra(&A, &F, graph); 

	
	return 0;

}