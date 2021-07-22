#pragma once

#include <vector>

class Vertex {
public:
  int data;
  Vertex *next;
  Vertex *right;
  Vertex *left;
  Vertex(): data(0), next(nullptr), right(nullptr), left(nullptr)  {}
  Vertex(int data) : data(data), next(nullptr), right(nullptr), left(nullptr) {}
};

// class Edge {
// public:
//   Vertex from;
//   Vertex to;
// };

class Graph {
  Vertex *HEAD;
  bool isDiGraph;
  // std::vector<Edge *> edges;

public:
  Graph() : HEAD(nullptr), isDiGraph(true) {}
  Graph(bool isDirected) : HEAD(nullptr), isDiGraph(isDirected) {}
  bool isEmpty();
  bool isDirected();
  void addVertex(Vertex newVertex);
  void addEdge(Vertex fromVertex, Vertex toVertex);
  void removeVertex(Vertex vertexToRemove);
  void removeEdge(Vertex fromVertex, Vertex toVertex);
  int totalVertices();
  int totalEdges();
  int inDegree();
  int outDegree();
  int degree();
  void neighbours(Vertex vertex);
  bool areNeighbours(Vertex vertexOne, Vertex vertexTwo);
};