#include "Graph.h"
#include <iostream>

int main() {
  Graph graph(true);
  // std::cout << graph.isDirected() << std::endl;
  // std::cout << graph.isEmpty() << std::endl;

  //   int *a;
  //   int b = 5;
  //   a = &b;
  //   std::cout << *a << std::endl;
  //   b = 99;
  //   std::cout << *a << std::endl;

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
  graph.addVertex(four);
  graph.addVertex(five);
  graph.addVertex(six);
  graph.vertices();
  graph.addEdge(one, six);
  graph.addEdge(one, five);
  graph.addEdge(two, three);
  graph.addEdge(two, one);
  graph.addEdge(two, five);
  graph.addEdge(two, four);
  graph.addEdge(three, one);
  graph.addEdge(two, six);
  graph.addEdge(four, two);
  graph.addEdge(six, two);
  graph.addEdge(one, two);
  graph.addEdge(five, two);
  std::cout << "Are neighboours: " << graph.areNeighbours(four, three)
            << std::endl;
  std::cout << "Indegree: " << graph.inDegree(two) << std::endl;
  std::cout << "Total vertices: " << graph.totalVertices() << std::endl;
  graph.removeVertex(two);
  std::cout << "Total vertices: " << graph.totalVertices() << std::endl;
  graph.removeVertex(three);
  graph.removeVertex(four);
  std::cout << "Total vertices: " << graph.totalVertices() << std::endl;

}