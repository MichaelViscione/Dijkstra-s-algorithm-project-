#include <iostream>
using namespace std;

class Graph {
	private:
		int nodeCount = 1;

	public:
		struct node
		{
			char data = '0';
			int weight = 0;
			bool visited = 0;
			node *nextPath = 0;
			node *nextNode = 0;
		};

		struct list
		{
			char data = '0';
		
			node *nodePtr;
			list *next = 0;
		};

		struct arrayNode {
			int weight = 100;		//100 is infinity since weight will never be bigger than 9
			char name = '0';
			char prevNode = '0';
		};

		node *head = new node;
		list *listHead = new list;	
		node *graphPtr = head;

		Graph();
		void createNodes(char nodeA, char nodeB, int pathWeight);
		bool checkList(char nodeX);
		void setNode(node *&nodeX, char nodeName);
		void printGraph();
		void addToList(node *nodeX, char nodeName);
		bool checkDup(char node1, char node2);
		void SetUpDijkstra();
		void InitializeArray(arrayNode *&Array);
		void Dijkstra(arrayNode *Array);
		void AddPaths(arrayNode *Array);
		void AddToArray(arrayNode *Array, int weight, char nextLetter, char curLetter);
		bool GoToShortPath(arrayNode *&Array);
		void PrintDijkstra(arrayNode *Array, char endpoint);

};

Graph::Graph(void) {
	head->data = 'A';				//label node A 
	listHead->data = 'A';			//add node A to the list 
	listHead->nodePtr = head;
}
