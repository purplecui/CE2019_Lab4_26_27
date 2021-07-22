#include "Graph.h"
#include <iostream>

bool Graph::isEmpty() { return HEAD == nullptr ? true : false; }

bool Graph::isDirected() { return isDiGraph; }

void Graph::addVertex(Vertex newVertex) {
  Vertex *vertexToAdd = new Vertex(newVertex);
  if (isEmpty())
    HEAD = vertexToAdd;

  else {
    Vertex *temp = HEAD;
    while (temp->next != nullptr) {
      temp = temp->next;
    }

    temp->next = vertexToAdd;
  }
}

void Graph::vertices() {
  Vertex *tempDown = HEAD;
  while (tempDown != nullptr) {
    std::cout << tempDown->data << " ";
    tempDown = tempDown->next;
  }
  std::cout << "\n";
}
