#include <iostream>
#include "Header.h"
using namespace std;

Graph::node *head = new Graph::node;
Graph::list *listHead = new Graph::list;
Graph::node *graphPtr = head;

Graph::Graph(void) {
	head->data = 'A';				//label node A 
	listHead->data = 'A';			//add node A to the list 
	listHead->nodePtr = head;
}

void Graph::createNodes(char node1, char node2, int pathWeight) {
	if (nodeCount == 1) {			//if there are no nodes
		nodeCount = 2;

		node *tempP = new node;
		node *temp2 = new node;
		addToList(temp2, node2);

		head->nextPath = tempP;				//create path from node 1 and create node 2
		tempP->nextNode = temp2;			//connect node 1's path to node 2
		tempP->weight = pathWeight;			//set node 1's path weight
		temp2->data = node2;				//label node 2

		tempP = new node;					//create another path to represent 2->1
		tempP->weight = pathWeight;
		temp2->nextPath = tempP;
		tempP->nextNode = head;
	}
	else {										//else if there are nodes in the list
		nodeCount++;
		bool nodeFound = checkList(node2);
		node *temp1;  //= new node;
		setNode(temp1, node1);			//temp1 is node 1

		node *tempP = new node;			//tempP is the path between node 1 and node 2 
		tempP->weight = pathWeight;	//set pathweight

									//logically, Node 1 will always be in the list so,
		while (temp1->nextPath != 0)	//if node 1 already has a path, move temp1 down the path list
			temp1 = temp1->nextPath;	//keep moving down the path list until there are no more paths


		temp1->nextPath = tempP;	//create a new path for node 1 using tempP

		node *temp2;

		if (nodeFound == 0) {					//if node2 is new
			temp2 = new node;			//create a new node for node 2	
			temp2->data = node2;		//label node 2

			addToList(temp2, node2);
		}
		else {				//else if node 2 already exists in the list
			setNode(temp2, node2);	//temp2 becomes known node
		}

		tempP->nextNode = temp2;	//link path from node 1 to node 2

		setNode(temp1, node1);				//set temp1 back to node 1
		tempP = new node;					//create another path to represent 2->1
		tempP->weight = pathWeight;

		while (temp2->nextPath != 0) {
			temp2 = temp2->nextPath;
		}

		temp2->nextPath = tempP;
		tempP->nextNode = temp1;
	}
}

void Graph::addToList(node *nodeX, char nodeName) {
	list *temp1 = listHead;
	list *temp2 = new list;
	do {							//A is already initialized into the list
		if (temp1->next != 0)		//find end of list
			temp1 = temp1->next;
	} while (temp1->next != 0);

	temp1->next = temp2;		//add to end of list
	temp2->data = nodeName;
	temp2->nodePtr = nodeX;
	//cout << "added " << temp2->data << endl;
}

bool Graph::checkList(char nodeX) {			//checks if node exists
	list *temp = listHead, *temp2 = listHead;

	do {							//traverse checkList until there are no more nodes
		temp = temp2;
		if (temp->data == nodeX)		//return true if found
		{
			return 1;
		}
		else if (temp->next != 0)
			temp2 = temp->next;			//temp2 allows loop to run one extra time for last element
	} while (temp->next != 0);

	return 0;						//return false if not found

}

void Graph::setNode(node *&nodeX, char nodeName) {				//sets temp node to an existing node
	list *temp = listHead;
	nodeX = 0;
	do {
		if (temp->data == nodeName)
			nodeX = temp->nodePtr;
		else if (temp->next != 0)
			temp = temp->next;
	} while (nodeX == 0);
}

void Graph::printGraph() {
	list *temp1 = listHead, *temp3 = listHead;		//temp1 refers to the list and temp2 refers to temp1's node's path
	node *temp2;									//temp3 allows loop to go 1 last time for last element
	do {
		temp1 = temp3;

		if (temp1->nodePtr->nextPath != 0) {		//go to temp1's node and check if there is a path
			temp2 = temp1->nodePtr->nextPath;
			cout << temp1->data << "-[" << temp2->weight << "]->" << temp2->nextNode->data << endl;	//print

			while (temp2->nextPath != 0) {			//print every path for temp1's node
				temp2 = temp2->nextPath;
				cout << temp1->data << "-[" << temp2->weight << "]->" << temp2->nextNode->data << endl;
			}
		}

		if (temp1->next != 0)		//go to next number on the list
			temp3 = temp1->next;
		cout << endl;
	} while (temp1->next != 0);		//do until list is finished
}

bool Graph::checkDup(char node1, char node2) {
	node *temp1, *temp2;

	if (!checkList(node2))  //if node 2 isn't on the list, it couldn't be a duplicate
		return 0;
	setNode(temp1, node1);
	setNode(temp2, node2);

	while (temp1->nextPath != 0) {
		if (temp1->nextPath->nextNode->data == node2)
			return 1;
		else
			temp1 = temp1->nextPath;
	}
	return 0;
}

void Graph::SetUpDijkstra() {
	arrayNode *Array;
	Array = new arrayNode[nodeCount];

	InitializeArray(Array);

	Array[0].name = 'A';
	Array[0].prevNode = 'A';
	Array[0].weight = 0;
	Dijkstra(Array);

	char endpoint;
	cout << endl << "Enter a node to find using Dijkstras algorithm.\n";
	cin >> endpoint;
	while (!checkList(endpoint)) {
		cout << "Please enter a node in the graph.\n";
		cin >> endpoint;
	}

	PrintDijkstra(Array, endpoint);

}

void Graph::InitializeArray(arrayNode *&Array) {
	list *temp = listHead;
	int count = 0;

	for (int i = 0; i < 4; i++) {
		if (temp->next != 0)
			temp = temp->next;
	}

	temp = listHead;
	Array[count].name = temp->data;
	count++;

	while (temp->next != 0) {
		temp = temp->next;
		Array[count].name = temp->data;
		count++;
	}

}

void Graph::Dijkstra(arrayNode *Array) {
	bool success = 0;

	if (graphPtr->nextPath != 0)
		AddPaths(Array);

	success = GoToShortPath(Array);

	if (success)
		Dijkstra(Array);

	graphPtr = head; //reset for when Dijkstra is called again
}

void Graph::AddPaths(arrayNode *Array) {
	node *temp = graphPtr->nextPath;
	AddToArray(Array, temp->weight, temp->nextNode->data, graphPtr->data);

	while (temp->nextPath != 0) {
		temp = temp->nextPath;
		AddToArray(Array, temp->weight, temp->nextNode->data, graphPtr->data);
	}

}

void Graph::AddToArray(arrayNode *Array, int weight, char nextLetter, char curLetter) {
	int totalWeight = 0;

	for (int i = 0; i < nodeCount; i++) {
		if (Array[i].name == curLetter) {
			totalWeight = Array[i].weight + weight;
			break;
		}
	}

	for (int i = 0; i < nodeCount; i++) {
		if (Array[i].name == nextLetter) {
			if (totalWeight < Array[i].weight) {
				Array[i].weight = totalWeight;
				Array[i].prevNode = curLetter;
			}
			break;
		}
	}
}

bool Graph::GoToShortPath(arrayNode *&Array) {
	int shortest = 0; //shortest weight
	list *temp = listHead;
	node * nextNode = 0;
	graphPtr->visited = 1;

	for (int i = 0; i < nodeCount; i++) {
		if (temp->nodePtr->visited == 0) {
			if (shortest == 0 || Array[i].weight < shortest) {
				nextNode = temp->nodePtr;
				shortest = Array[i].weight;
			}
		}
		if (temp->next != 0) {
			temp = temp->next;
		}
	}

	if (nextNode != 0) {
		graphPtr = nextNode;
		return 1;
	}
	else
		return 0;

}

void Graph::PrintDijkstra(arrayNode *Array, char endpoint) {
	int letterCount = 0, totalWeight = 0;
	char curPoint = endpoint;

	if (curPoint != listHead->data)
		letterCount++;

	do {
		for (int k = 0; k < nodeCount; k++) {
			letterCount++;
			if (Array[k].name == curPoint) {
				curPoint = Array[k].prevNode;
				break;
			}
		}

	} while (curPoint != listHead->data);

	arrayNode *letterArray;
	letterArray = new arrayNode[letterCount];
	curPoint = endpoint;
	int letterCountB = 0;
	int i = 0;
	do {

		for (i = 0; i < nodeCount; i++) {

			if (Array[i].name == curPoint) {
				if (letterCountB >= 1) {
					letterArray[letterCountB - 1].weight = totalWeight - Array[i].weight;
				}
				if (Array[i].prevNode == Array[i].name)
					letterArray[letterCountB].weight = 0;

				totalWeight = Array[i].weight;

				letterArray[letterCountB].name = curPoint;
				if (Array[i].prevNode != Array[i].name) {
					letterCountB++;
					curPoint = Array[i].prevNode;
				}
				break;
			}
		}

	} while (Array[i].prevNode != Array[i].name);

	totalWeight = 0;

	cout << endl << "Path" << endl << "----" << endl;
	cout << "A";
	for (int j = letterCountB - 1; j >= 0; j--) {
		cout << "-[" << letterArray[j].weight;
		cout << "]->" << letterArray[j].name << endl;

		if (j != 0)
			cout << letterArray[j].name;

		totalWeight = totalWeight + letterArray[j].weight;
	}

	cout << "Minimum distance from A->" << endpoint << " = " << totalWeight << endl;
	cout << "------------------------------------------------------" << endl;


	delete[] letterArray;
}