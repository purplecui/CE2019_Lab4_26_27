#include "Graph.h"
#include <iostream>

int main() {
  Graph graph;
  std::cout << graph.isDirected() << std::endl;
  std::cout << graph.isEmpty() << std::endl;

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
}