#include "Graph.h"
#include <iostream>

bool Graph::isEmpty() { return HEAD == nullptr ? true : false; }

bool Graph::isDirected() { return isDiGraph; }

void Graph::addVertex(Vertex newVertex) {
  if (!keyExists(newVertex.key)) {
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
  } else
    throw std::string("Key already exists in the graph");
}

bool Graph::keyExists(int key) {
  Vertex *temp = HEAD;
  while (temp != nullptr) {
    if (key == temp->key) {
      return true;
    }
    temp = temp->next;
  }
  return false;
}

void Graph::vertices() {
  Vertex *tempDown = HEAD;
  while (tempDown != nullptr) {
    std::cout << tempDown->key << " ";
    tempDown = tempDown->next;
  }
  std::cout << "\n";
}

void Graph::removeVertex(Vertex vertexToRemove) {
  Vertex *temp = HEAD;
  Vertex *parent = nullptr;
  while (temp != nullptr && vertexToRemove.key != temp->key) {
    parent = temp;
    temp = temp->next;
  }
  if (temp == nullptr)
    throw std::string("The vertex doesnot exist");

  Vertex *tempRight = temp->right;
  while (tempRight != nullptr) {
    Vertex *edgeToDelete = tempRight;

    tempRight->left->right = tempRight->right;
    if (edgeToDelete->right != nullptr)
      tempRight->right->left = tempRight->left;

    tempRight = tempRight->left->right;
    delete edgeToDelete;
  }

  removeEdges(vertexToRemove);
  if (parent == nullptr) {
    HEAD = temp->next;
  } else
    parent->next = temp->next;
  delete temp;
}

void Graph::removeEdges(Vertex &vertex) {
  // remove all edges
  // will be implemented after addEdge implementation
}

int Graph::totalVertices() {
  int totalVertices = 0;
  Vertex *temp = HEAD;

  while (temp != nullptr) {
    totalVertices++;
    temp = temp->next;
  }
  return totalVertices;
}

int Graph::inDegree(Vertex vertex) {
  // total indegree of a vertex
  // will be implemented after addEdge implementation
  return 0;
}

int Graph::outDegree(Vertex vertex) { return 0; }

int Graph::degree(Vertex vertex) {
  int inDeg = inDegree(vertex);
  int outDeg = outDegree(vertex);
  // return inDeg + outDeg;
  return inDeg + outDeg;
}

bool Graph::areNeighbours(Vertex vertexOne, Vertex vertexTwo) {
  // checks if two vertices are neighbours or not
  // will be implemented after addEdge implementation
  return false;
}