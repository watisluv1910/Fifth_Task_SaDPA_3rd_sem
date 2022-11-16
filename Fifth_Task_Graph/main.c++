#include <iostream>
#include <algorithm>

#include "Graph.h"

void printMenu();

int main()
{
	printMenu();
	
	Graph graph(5);

	graph.addEdge(1, 3, 9);
	graph.addEdge(2, 3, 5);
	graph.addEdge(4, 3, 7);
	graph.addEdge(5, 3, 8);

	graph.printGraph();

	// Find root
	std::cout << "\nRoot: " << graph.findRoot() + 1 << "\n";

	std::vector<size_t> pathLengths = graph.findAllPathLengths();

	// Find longest path
	std::cout << "Longest path: "
		<< *std::max_element(pathLengths.begin(), pathLengths.end()) << "\n";

	// Find shortest path
	std::cout << "Shortest path: "
		<< *std::min_element(pathLengths.begin(), pathLengths.end()) << "\n";

	system("pause");
	system("cls"); // Clear screen
	
	return 0;
}

void printMenu()
{
	std::cout << "Practical task num.5\nIKBO-24-21 Nasevich V.V.\n"
		"Variant num. 16.\n";
}