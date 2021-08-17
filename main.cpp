#include "Graph.h"
#include <iostream>

int main() {
  Graph graph(false);
  Vertex one(10);
  Vertex two(88);
  Vertex three(43);
  Vertex four(29);
  Vertex five(19);
  Vertex six(78);
  graph.addVertex(one);
  graph.addVertex(two);
  graph.addVertex(three);
  graph.vertices();
  std::cout << "Total vertices: " << graph.totalVertices() << std::endl;
  graph.addVertex(four);
  graph.addVertex(five);
  graph.addVertex(six);
  graph.vertices();
  std::cout << "Total vertices: " << graph.totalVertices() << std::endl;
  std::cout << std::endl;
  graph.addEdge(one, six);
  graph.addEdge(one, five);

  graph.addEdge(one, two);
  graph.addEdge(two, three);
  graph.addEdge(two, six);
  // graph.addEdge(two, one);
  
  // graph.addEdge(two, four);
  graph.addEdge(three, one);
  
  graph.addEdge(four, two);
  // graph.addEdge(six, two);
  
  graph.addEdge(five, two);
  graph.adjacencyList();
  graph.neighbours(two);
  graph.neighbours(one);
  
  std::cout<< std::endl;
  std::cout << "Are neighboours: " << graph.areNeighbours(one, six) << std::endl;
  std::cout<< std::endl;
  std::cout<< "Degree of vetex two:" << std::endl;
  std::cout << "Indegree: " << graph.inDegree(two) << std::endl;
  std::cout << "OutDegree: " << graph.outDegree(two) << std::endl;
  std::cout << "Degree: " << graph.degree(two) << std::endl;
  
  std::cout<< std::endl;
  std::cout<< "Degree of vetex one:" << std::endl;
  std::cout << "Indegree: " << graph.inDegree(one) << std::endl;
  std::cout << "OutDegree: " << graph.outDegree(one) << std::endl;
  std::cout << "Degree: " << graph.degree(one) << std::endl;

  std::cout << "Total vertices: " << graph.totalVertices() << std::endl;
  std::cout << "Total Edges: " << graph.totalEdges() << std::endl;

  std::cout<< graph.totalEdges();

  graph.removeEdge(five, two);
  std::cout << "\nAfter removing five, two\n" << std::endl;
  std::cout << "Total Edges: " << graph.totalEdges() << std::endl;
  graph.adjacencyList();

  graph.removeVertex(two);
  std::cout << "\nAfter removing vertex two\n" << std::endl;
  graph.adjacencyList();
  std::cout << "Total vertices: " << graph.totalVertices() << std::endl;

  graph.removeEdge(one, five);
  std::cout << "\nAfter removing one, five\n" << std::endl;
  std::cout << "Total Edges: " << graph.totalEdges() << std::endl;
  graph.adjacencyList();

  graph.removeVertex(three);
  std::cout << "\nAfter removing vertex three\n" << std::endl;
  graph.adjacencyList();
  

  graph.removeVertex(four);
  std::cout << "\nAfter removing vertex four\n" << std::endl;
  graph.adjacencyList();
  std::cout << "Total vertices: " << graph.totalVertices() << std::endl;
  std::cout << "Total Edges: " << graph.totalEdges() << std::endl;
}