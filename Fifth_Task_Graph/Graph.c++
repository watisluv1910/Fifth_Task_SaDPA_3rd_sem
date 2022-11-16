#include <iostream>

#include "Graph.h"

Graph::Graph(size_t size) : size(size)
{
	matrix.resize(size);
	//visited.resize(size);
	
	for (std::vector<int>& row : matrix)
	{
		row.resize(size);
	}

	visited.resize(size);

	std::cout << "\nGraph initialized.\n";
}

void Graph::addEdge(size_t v1, size_t v2, size_t weight)
{
	// Check if edge was already defined
	if (matrix[v1 - 1][v2 - 1] != 0)
	{
		std::cerr << "\nError: Edge already defined.\n";
		return;
	}
	matrix.at(v1 - 1).at(v2 - 1) = weight;
	matrix.at(v2 - 1).at(v1 - 1) = weight;
}

void Graph::printGraph()
{
	std::cout << "\nGraph:\n";

	for (size_t i = 0; i < size; i++)
	{
		std::cout << i + 1 << ": ";
		for (size_t j = 0; j < size; j++)
		{
			std::cout << matrix[i][j] << " ";
		}

		std::cout << "\n";
	}
}

// Check is graph cyclic
bool Graph::isCyclic()
{
	// Mark all the vertices as not
	// visited and not part of recursion
	// stack
	std::vector<bool> visited(size);

	// Call the recursive helper
	// function to detect cycle in different
	// DFS trees
	for (int u = 0; u < size; u++) {

		// Don't recur for u if
		// it is already visited
		if (!visited.at(u))
		{
			if (isCyclicUtil(u, visited, -1))
			{
				return true;
			}
		}
	}
	return false;
}

bool Graph::isCyclicUtil(int v, 
	std::vector<bool>& visited, int parent)
{
	// Mark the current node as visited
	visited.at(v) = true;

	// Recur for all the vertices
	// adjacent to this vertex
	for (size_t i = 0; i < size; i++)
	{
		// If an adjacent is not
		// visited, then recur for
		// that adjacent
		if (matrix.at(v).at(i) != 0)
		{
			if (!visited.at(i))
			{
				if (isCyclicUtil(i, visited, v))
				{
					return true;
				}
			}

			// If an adjacent is visited
			// and not parent of current
			// vertex, then there is a cycle
			else if (i != parent)
			{
				return true;
			}
		}
	}
	return false;
}

// Find root of acyclic graph
size_t Graph::findRoot()
{
	// Check if graph is acyclic
	if (isCyclic())
	{
		std::cerr << "\nError: Graph is cyclic.\n";
		return 0;
	}

	// Find root
	for (size_t i = 0; i < size; i++)
	{
		bool isRoot = true;

		for (size_t j = 0; j < size; j++)
		{
			if (matrix[i][j] == 0 && i != j)
			{
				isRoot = false;
				break;
			}
		}

		if (isRoot)
		{
			return i;
		}
	}

	std::cerr << "\nError: Root not found.\n";
	return 0;
}

// Find all pathes
std::vector<size_t> Graph::findAllPathLengths()
{
	// Find longest path
	size_t pathLength = 0;
	std::vector<size_t> path;
	std::vector<size_t> pathesLength;
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (i != j)
			{
				findAllPathesUtil(i, j, pathLength, path, pathesLength);
			}
		}
	}

	return pathesLength;
}

void Graph::findAllPathesUtil(size_t v1, size_t v2,
	size_t& pathLength, std::vector<size_t>& path, std::vector<size_t>& pathLengths)
{
	// Mark the current node as visited
	visited.at(v1) = true;

	// If current vertex is same as v2,
	// then print current path[]
	if (v1 == v2)
	{
		if (pathLength > path.size())
		{
			for (size_t i = 0; i < visited.size(); i++)
			{
				if (visited[i])
				{
					path.push_back(i);
				}
			}
		}
	}

	// If current vertex is not v2
	else
	{
		// Recur for all the vertices
		// adjacent to current vertex
		for (size_t i = 0; i < size; i++)
		{
			if (matrix.at(v1).at(i) != 0)
			{
				if (!visited.at(i))
				{
					pathLength += matrix.at(v1).at(i);
					findAllPathesUtil(i, v2, pathLength, path, pathLengths);
					pathLengths.push_back(pathLength);
					pathLength -= matrix.at(v1).at(i);
				}
			}
		}
	}

	// Mark the current node as unvisited
	visited.at(v1) = false;
}