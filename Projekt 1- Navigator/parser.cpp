#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <math.h>

using namespace std;

string filePath = "C:/Users/anton/maposm.sec";


//  ich definiere dies Dinge hier global damit von überall darauf zugreifen können 
struct node {
	unsigned long long id = 0;
	double lat, lon = 0.0;
	double distance = -1.0;
	node* vorgaenger = nullptr;
	bool visited = false;
	vector <node> neigbours;
};
vector <node> nodelist; // List mit allen Nodes (wird vom Parser belegt)
node* ptrstart; // pointer auf den Startnode (wird vom Parser belegt)
node* ptrziel; // pointer auf den Zielnode (wird vom Parser belegt)

unsigned long long powerof(unsigned long long base, unsigned long long pot) { // pow aber für unsigned long long
	if (pot == 0) {
		return 1;
	}
	unsigned long long sum = base;
	for (unsigned long long i = 1; i < pot; i++) {
		sum = sum * base;
	}
	return sum;
}

void add_intersection_to_nodelist(string data, unsigned long long pstartID, unsigned long long pzielID) {
	unsigned long long tempid = 0;
	double templat = 0.0;
	double templon = 0.0;
	//cout << data << endl;
	basic_string <char>::size_type nodeindexstart, nodeindexend;
	const char* cstrB1 = "id=";
	const char* cstrB2 = "vis";
	string burner = "9";
	basic_string <char>::reference refStr1 = burner[0];
	unsigned long long powwertID = 0;
	double powwert = 0.0;
	// ID rausschreiben -> tempid
	nodeindexstart = data.find(cstrB1);
	nodeindexend = data.find(cstrB2);
	string ID = data.substr(nodeindexstart + 4, (nodeindexend - 6) - nodeindexstart);
	for (int i = ID.length() - 1; i != -1; i--) {
		refStr1 = ID[i];
		powwertID = (ID.length() - 1) - i;
		tempid = tempid + (((unsigned long long)refStr1 - 48) * powerof(10, powwertID));
	}
	// lat rausschreiben -> templat
	cstrB1 = "lat";
	cstrB2 = "lon";
	nodeindexstart = data.find(cstrB1);
	nodeindexend = data.find(cstrB2);
	string lat = data.substr(nodeindexstart + 8, 7);
	for (int i = lat.length() - 1; i != -1; i--) {
		refStr1 = lat[i];
		powwert = (i + 1) * (-1);
		templat = templat + (((double)refStr1 - 48) * powl(10.0, powwert));
	}
	templat = templat + 49.0;
	// lon rausschreiben -> templon
	nodeindexstart = data.find(cstrB2);
	string lon = data.substr(nodeindexstart + 7, 7);
	for (int i = lon.length() - 1; i != -1; i--) {
		refStr1 = lon[i];
		powwert = (i + 1) * (-1);
		templon = templon + (((double)refStr1 - 48) * powl(10.0, powwert));
	}
	templon = templon + 8.0;
	node* crossing = new node{ tempid,templat,templon,-1.0,nullptr };
	if (tempid == pstartID) {
		ptrstart = crossing;
	}
	else if (tempid == pzielID) {
		ptrziel = crossing;
	}
	nodelist.push_back(*crossing);
}

void addneigbour(string nodeA, string nodeB) {
	unsigned long long nodeAid = 0;
	unsigned long long nodeBid = 0;
	basic_string <char>::size_type nodeindexstart, nodeindexend;
	const char* cstrC1 = "ref";
	const char* cstrC2 = "/>";
	string burner = "9";
	basic_string <char>::reference refStr1 = burner[0];
	unsigned long long powwertID = 0;
	// ID rausschreiben für nodeA
	nodeindexstart = nodeA.find(cstrC1);
	nodeindexend = nodeA.find(cstrC2);
	string ID = nodeA.substr(nodeindexstart + 5, (nodeindexend - 6) - nodeindexstart);
	for (int i = ID.length() - 1; i != -1; i--) {
		refStr1 = ID[i];
		powwertID = (ID.length() - 1) - i;
		nodeAid = nodeAid + (((int)refStr1 - 48) * powerof(10, powwertID));
	}
	// ID rausschreiben für nodeB
	nodeindexstart = nodeB.find(cstrC1);
	nodeindexend = nodeB.find(cstrC2);
	ID = nodeB.substr(nodeindexstart + 5, (nodeindexend - 6) - nodeindexstart);
	for (int i = ID.length() - 1; i != -1; i--) {
		refStr1 = ID[i];
		powwertID = (ID.length() - 1) - i;
		nodeBid = nodeBid + (((int)refStr1 - 48) * powerof(10, powwertID));
	}
	// Nachbarlisten belegen
	bool foundA = false;
	bool foundB = false;
	int posA = 0;
	int posB = 0;
	for (int i = 0; !nodelist.empty() && i < nodelist.size(); i++) {
		if (nodelist.at(i).id == nodeAid) {
			posA = i;
			foundA = true;
		}
		if (nodelist.at(i).id == nodeBid) { // Hier kein else if falls start = ziel ist
			posB = i;
			foundB = true;
		}
	}
	if (foundA && foundB) {
		nodelist.at(posA).neigbours.push_back(nodelist.at(posB));
		nodelist.at(posB).neigbours.push_back(nodelist.at(posA));
	}
}

void TEST_display_nodelist() {
	for (int i = 0; !nodelist.empty() && i < nodelist.size(); i++) {
		cout << "Element " << i << ": " << nodelist.at(i).id << " | lat: " << nodelist.at(i).lat << " | lon: " << nodelist.at(i).lon << endl;
	}
	cout << "TEST_display_nodelist - finished" << endl;
}
void TEST_show_neighbours_for_nodelist_at(int index) {
	for (int i = 0; !nodelist.at(index).neigbours.empty() && i < nodelist.at(index).neigbours.size(); i++) {
		cout << nodelist.at(index).neigbours.at(i).id << endl;
	}
	cout << "TEST_show_neighbours_for_nodelist_at - finished" << endl;
}



// parser als mit rückgabe der Node list bzw als graph struct
void parser(unsigned long long pstartID, unsigned long long pzielID) { // Trägt alle Nodes mit den richtigen Werten in die nodelist ein und belegt ptrstart und ptrziel
	string currentline;
	string data;
	//string checkline;
	bool nodeidentifier = false;
	bool nodeidentifiertwo = false;
	bool nodeidentifierthree = false;

	const char* cstr1 = "<node";
	const char* cstr2 = "crossing";

	const char* cstr3 = "button_operated";
	const char* cstr4 = "bicycle";

	const char* cstr5 = "railway";
	const char* cstr6 = "note";

	bool wayidentifier = false;
	bool wayidentifiertwo = false;

	const char* cstr7 = "<way";
	const char* cstr8 = "<nd";


	

	fstream Eingabedatei;
	Eingabedatei.open(filePath);
	if (Eingabedatei.good()) {
		while (!Eingabedatei.eof()) { // läuft die Datei von oben bis unten durch
			getline(Eingabedatei, currentline);
			if ((currentline.find(cstr1) != -1 && nodeidentifier) || (currentline.find(cstr7) != -1 && wayidentifier)) { // Abbruch falls "<node" auf "<node" folgt bzw "<way" auf "<way"
				nodeidentifier = false;
				nodeidentifiertwo = false;
				nodeidentifierthree = false;
				wayidentifier = false;
				wayidentifiertwo = false;
			}
			if (currentline.find(cstr7) != -1) {
				wayidentifier = true;
				wayidentifiertwo = false;
			}
			else if (wayidentifier && currentline.find(cstr8) != -1) {
				if (!wayidentifiertwo) {
					data = currentline;
				}
				else if (wayidentifiertwo) {
					addneigbour(currentline, data);
				}
				wayidentifiertwo = true;
			}
			else {
				if (!nodeidentifier && currentline.find(cstr1) != -1) {
					data = currentline;
					nodeidentifier = true;
				}
				else if (nodeidentifier && !nodeidentifiertwo && !nodeidentifierthree) { // Testet Zeile 1
					if (currentline.find(cstr2) != -1 && currentline.find(":") == -1 && currentline.find(cstr5) == -1 && currentline.find(cstr6) == -1) {
						// Valid
						add_intersection_to_nodelist(data, pstartID, pzielID);
						nodeidentifier = false;
						nodeidentifiertwo = false;
						nodeidentifierthree = false;
					}
					else if (currentline.find(cstr3) != -1 || currentline.find(cstr4) != -1) {
						nodeidentifiertwo = true;
					}
					else {
						// Invalid
						nodeidentifier = false;
					}
				}
				else if (nodeidentifier && nodeidentifiertwo && !nodeidentifierthree) { // Testet Zeile 2
					if (currentline.find(cstr2) != -1 && currentline.find(":") == -1 && currentline.find(cstr5) == -1 && currentline.find(cstr6) == -1) {
						// Valid
						add_intersection_to_nodelist(data, pstartID, pzielID);
						nodeidentifier = false;
						nodeidentifiertwo = false;
						nodeidentifierthree = false;
					}
					else if (currentline.find(cstr3) != -1 || currentline.find(cstr4) != -1) {
						nodeidentifierthree = true;
					}
					else {
						// Invalid
						nodeidentifier = false;
						nodeidentifiertwo = false;
					}
				}
				else if (nodeidentifier && nodeidentifiertwo && nodeidentifierthree) { // Testet Zeile 3
					if (currentline.find(cstr2) != -1 && currentline.find(":") == -1 && currentline.find(cstr5) == -1 && currentline.find(cstr6) == -1) {
						// Valid
						add_intersection_to_nodelist(data, pstartID, pzielID);
						nodeidentifier = false;
						nodeidentifiertwo = false;
						nodeidentifierthree = false;
					}
					nodeidentifier = false;
					nodeidentifiertwo = false;
					nodeidentifierthree = false;
				}
			}
		}
	}
	else {
		cout << "Error - file bad" << endl;
	}
	Eingabedatei.close();

	TEST_display_nodelist(); 
	TEST_show_neighbours_for_nodelist_at(0);
}



/*int main() {
	// Temporär
	unsigned long long startID;
	unsigned long long zielID;
	cout << "Start ID angeben:" << endl;
	cin >> startID;
	cout << "Ziel ID angeben:" << endl;
	cin >> zielID;
	cout << "----------" << endl;
	// Parser
	parser(startID, zielID);
	// Djkstra



	// Visualisierung

	return 0;
}*/