//Michael Viscione	
//12/6/2017
//Project 6

#include "Header.h"
#include <iostream>
#include <ctype.h>
using namespace std;

int main() {
	char node1 = '0', node2 = '0', weight = 0; bool error = true, skip = false;
	Graph graph;

	cout << "Enter a node, followed by the weight of one of its paths, and the node on \n";
	cout << "the other end of the path. For column 1, only use nodes have been used \n";
	cout << "previously. The first node is pre-set to node A.\n";
	cout << "Press X after all input is entered.\n";
	cout << "1 W 2\n";
	do {
		cout << "A ";

		cin >> weight;
		if (weight == 'X') {
			skip = true;
			break;
		}
		cin >> node2;
		if (node2 == 'X') {
			skip = true;
			break;
		}

		if (node2 == 'A')
			cout << "Cannot create a path from one node to itself.\n";
		else if (!isdigit(weight)) {
			cout << "Please enter a digit for the weight.\n";
			if (weight == 0)
				cout << "Please enter a weight above 0.\n";
		}	
		else if (isdigit(node2))
			cout << "Please enter a character for node A and B.\n";
		else
			error = false;
	} while (error == true);

	error = true;
	if (skip == false) {
		weight = weight - 48;				//convert weight char to int
		graph.createNodes(1, node2, weight);

		do {
			cin >> node1;
			if (node1 == 'X')
				break;
			cin >> weight;
			if (weight == 'X')
				break;
			cin >> node2;
			if (node2 == 'X')
				break;
			if (graph.checkList(node1) == 0)
				cout << "Please use previous nodes for column 1.\n";
			else if (node2 == node1)
				cout << "Cannot create a path from one node to itself.\n";
			else if (!isdigit(weight)) {
				cout << "Please enter a digit for the weight.\n";
				if (weight == 0)
					cout << "Please enter a weight above 0.\n";
			}
			else if (isdigit(node1) || isdigit(node2))
				cout << "Please enter a character for node A and B.\n";
			else if (graph.checkDup(node1, node2))
				cout << "Please avoid entering duplicate paths.\n";
			else {
				weight = weight - 48;
				graph.createNodes(node1, node2, weight);
			}
		} while (node1 != 'X' || node2 != 'X' || weight != 'X');
	}

	cout << endl << "------------------------------------------------------" << endl;
	cout << "All Paths\n---------\n";
	graph.printGraph();
	cout <<"------------------------------------------------------" << endl;

	graph.SetUpDijkstra();
	
	system("pause");
	return 0;
}