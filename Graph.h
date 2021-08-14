#pragma once

#include <iostream>
#include <vector>

class Vertex {
public:
  int key;
  Vertex *next;  // Pointer to the next vertex
  Vertex *right; // Poiinter to the edges
  Vertex *left;  // Pointer to previous element
  Vertex() : next(nullptr), right(nullptr), left(nullptr) {}
  Vertex(int key) : key(key), next(nullptr), right(nullptr), left(nullptr) {}
};

class Graph {

private:
  Vertex *HEAD;
  bool isDiGraph;
  int edgeCount;
  // std::vector<Edge *> edges;

public:
  Graph() : edgeCount(0), HEAD(nullptr), isDiGraph(true) {}
  Graph(bool isDirected) : edgeCount(0), HEAD(nullptr), isDiGraph(isDirected) {}

  /* Group
   */

  // Checks if the graph is empty
  bool isEmpty();

  // Checks if the graph is directed
  bool isDirected();

  // Prints out the vertices of the graph
  void vertices();

  // Returns the total no of degree of a vertex
  int degree(Vertex vertex);

  /* Solo
   */

  // Adds a vertex to the graph
  void addVertex(Vertex newVertex); // Saskar

  // Chcks if a vertex with given key exists or not
  bool keyExists(int key); // Saskar

  // Adds an edge between two vertices
  void addEdge(Vertex fromVertex, Vertex toVertex); // Gaurav

  // Removes a vertex and it's related edges
  void removeVertex(Vertex vertexToRemove); // Saskar
  void removeEdges(Vertex &vertex);         // Saskar

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