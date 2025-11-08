#include <iostream>
#include <vector> 
#include <queue>


using namespace std; 


#define INF 999; //TODO: Höchserer Wert




struct Node {
	//int id; 
	//int lon, lat; 
	bool visited = false;
	Node* PrevNode = nullptr; // Pointer auf den vorherigen Knoten im Pfad
	int distance = INF;
	vector<pair<Node*, int>> neighbors; // Nachbarn + Kantengewicht
	// Liste {children Nodes, dist} 
	// {1,2}, {2,4}, ...
};

struct Graph {
	vector<Node*> adjList;

	// Liste an {Startnodes und Listen von {Nodes,Dist}}
	// 0 --> {1,4}, {2,4}  
	// 1--> {0,4}, {2,2}	
	// usw.

	int size = adjMatrix.size();

};


struct CompareDist {
	bool operator ()(const Node* a, const Node* b) {
		return a->distance > b->distance; // Min-Heap
	}
};


struct Path {
	vector<Node> nodesInPath;
	int totalDistance;
};





vector<Node> dijkstra(Node* SN, Node* TN, Graph& graph, vector<Node>& dist, vector<Node, Node> prevNode ) { //{Node, prevNode}
	
	priority_queue <Node*, vector<Node*>, CompareDist > pq; // Min-Heap
	//Node mit der kleinsten Distanz hat höchste Priorität 
	
	SN->distance = 0;	// Startknoten Distanz auf 0 setzen
	pq.push(SN); // Startknoten in die Queue einfügen


	while (!pq.empty()) {

		Node* tmpNode = pq.top(); 
		
		cout << tmpNode->distance << "  " << tmpNode->PrevNode << endl;

		pq.pop(); // Knoten mit der kleinsten Distanz auslesen und entfernen


	}
	

}

	
int main() {

	Node A, B, C, D;
	Graph g;

	A.neighbors = {{ &B, 1 }, { &C, 2 }};
	B.neighbors = { { &A, 1 }, { &D, 3 } };
	C.neighbors = { { &A, 2 }, { &D, 1 } };
	D.neighbors = { { &B, 3 } };
	





return 0;

}