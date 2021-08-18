#pragma once

#include <iostream>
#include <vector>

class Edge;

class Vertex {
public:
  int cityCode;
  std::string cityName;
  Vertex *next;    // Pointer to the next vertex
  Edge *edgesHead; // Pointer to the edges

  Vertex() : next(nullptr) {}
  Vertex(int cityCode, std::string cityName)
      : cityCode(cityCode), cityName(cityName), next(nullptr),
        edgesHead(nullptr) {}
};

class Edge {
public:
  int distanceInKilometers;
  Vertex *vertex;
  Edge *right;
  // Edge *left;

  Edge(Vertex vertex, int distanceInKilometers)
      : vertex(new Vertex(vertex)), distanceInKilometers(distanceInKilometers),
        right(nullptr) {}

  ~Edge() { delete vertex; }
};

class Graph {

private:
  Vertex *HEAD;
  bool isDiGraph;
  int edgeCount;

public:
  Graph() : edgeCount(0), HEAD(nullptr), isDiGraph(true) {}
  Graph(bool isDirected) : edgeCount(0), HEAD(nullptr), isDiGraph(isDirected) {}

  /* Group
   */

  Graph(int noOfVertices, int noOfEdges, bool isDirected)
      : edgeCount(0), isDiGraph(isDirected), HEAD(nullptr) {

    // setting edge limit for a graph with no loop and no multiple edges
    int edgeLimitForDirected = noOfVertices * (noOfVertices - 1);
    int edgeLimitForUnDirected =
        (noOfVertices * (noOfVertices - 1) / 2);

    if (isDirected && noOfEdges > edgeLimitForDirected)
      throw std::string("A directed graph with " +
                        std::to_string(noOfVertices) +
                        " vertices can only have " +
                        std::to_string(edgeLimitForDirected) + " vertices.");

    else if (!isDirected && noOfEdges > edgeLimitForUnDirected)
      throw std::string("An undirected graph with " +
                        std::to_string(noOfVertices) +
                        " vertices can only have " +
                        std::to_string(edgeLimitForUnDirected) + " vertices.");

    else {
      std::cout << "\nYour random graph with " << noOfVertices
                << " vertices and " << noOfEdges << " edges is:\n"
                << std::endl;
      // adding randoom cities as vertices 
      for (int i = 1; i <= noOfVertices; i++) {
        addVertex(Vertex(i, "city" + std::to_string(i)));
      }
      int edge = 1;

      // adding random edges to the graph with random weight
      while (edge <= noOfEdges) {
        int fromVertex = rand() % noOfVertices + 1;
        int toVertex = rand() % noOfVertices + 1;
        bool hasEdge =
            edgeExists(Vertex(fromVertex, "city" + std::to_string(fromVertex)),
                       Vertex(toVertex, "city" + std::to_string(toVertex)));

        if (hasEdge) 
          continue; // if edge already exists, we try again

        if (fromVertex == toVertex)
          continue; // if the edge is a loop, we try again

        int distance = rand() % 20 * 30;
        addEdge(Vertex(fromVertex, "city" + std::to_string(fromVertex)),
                Vertex(toVertex, "city" + std::to_string(toVertex)), distance);
        edge++;
      }

      // printing out the graph 
      adjacencyList();
    }
  }

  // Checks if the graph is empty
  bool isEmpty();

  // Checks if the graph is directed
  bool isDirected();

  // Prints out the vertices of the graph
  void vertices();

  // Returns the total no of degree of a vertex
  int degree(Vertex vertex);

  // Prints out the adjacency list
  void adjacencyList();

  /* Solo
   */

  // Adds a vertex to the graph
  void addVertex(Vertex newVertex); // Saskar

  // Chcks if a vertex with given key exists or not
  bool cityCodeExists(int cityCode); // Saskar

  // Adds an edge between two vertices
  void addEdge(Vertex fromVertex, Vertex toVertex,
               int distanceInKilometers); // Gaurav

  // Removes a vertex and it's related edges
  void removeVertex(Vertex vertexToRemove); // Saskar
  int removeEdges(Vertex &vertex);          // Saskar

  // Removes an edge from the graph
  void removeEdge(Vertex fromVertex, Vertex toVertex); // Gaurav

  // Checks if an edge exists between two vertices
  bool edgeExists(Vertex from, Vertex to); // Gaurav

  // Returns the total no of vertices in the graph
  int totalVertices(); // Saskar

  // Returns the total no of edges in the graph
  int totalEdges(); // Gaurav

  // Returns the total no of indegree of a vertex
  int inDegree(Vertex vertex); // Saskar

  // Returns the total no of outdegree of a vertex
  int outDegree(Vertex vertex); // Gaurav

  // Prints out the neighbours of a vertex
  void neighbours(Vertex vertex); // Gaurav

  // Checks if two vertices form an edge or not
  bool areNeighbours(Vertex vertexOne, Vertex vertexTwo); // Saskar
};