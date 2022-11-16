#pragma once

#include <vector>
#include <string>

// Weighted graph on adjancency matrix
class Graph
{
	
public:
	Graph(size_t size);

	// Method to add edge to graph
	void addEdge(size_t v1, size_t v2, size_t weight);

	// Print graph
	void printGraph();

	// Method to find acyclic graph root
	size_t findRoot();

	std::vector<size_t> findAllPathLengths();
	
private:
	// Graph size
	size_t size;

	// Graph matrix
	std::vector<std::vector<int>> matrix;
	
	// Visited
	std::vector<bool> visited;

	// Check if graph is acyclic
	bool isCyclic();
	bool isCyclicUtil(int v, std::vector<bool>& visited, int parent);

	void findAllPathesUtil(size_t v, size_t dest,
		size_t& pathLength,
		std::vector<size_t>& path,
		std::vector<size_t>& pathLengths);
};