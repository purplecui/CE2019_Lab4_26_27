#include "Graph.h"
#include <iostream>

bool Graph::isEmpty() { return HEAD == nullptr ? true : false; }

bool Graph::isDirected() { return isDiGraph; }

void Graph::addVertex(Vertex newVertex) {
  if (!keyExists(newVertex.key)) {

    Vertex *vertexToAdd = new Vertex(newVertex);
    // add to head
    if (isEmpty())
      HEAD = vertexToAdd;

    else {
      vertexToAdd->next = HEAD;
      HEAD = vertexToAdd;
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


void Graph::addEdge(Vertex fromVertex, Vertex toVertex) {
  bool fromExists = keyExists(fromVertex.key);
  bool ToExists = keyExists(toVertex.key);
  Vertex *temp = HEAD;

  if (fromExists && ToExists) {
    if (!edgeExists(fromVertex, toVertex)) {

      if (isDirected()) {
        Vertex *newEdge = new Vertex(toVertex);
        Vertex *temp = HEAD;

        while (temp != nullptr && temp->key != fromVertex.key) {
          temp = temp->next;
        }

        if (temp->right == nullptr) {
          temp->right = newEdge;
          newEdge->left = temp;
        } else {
          newEdge->right = temp->right;
          temp->right->left = newEdge;
          newEdge->left = temp;
          temp->right = newEdge;
        }
      } else {
        Vertex *newEdgeOne = new Vertex(toVertex);
        Vertex *newEdgeTwo = new Vertex(fromVertex);
        Vertex *temp = HEAD;

        while (temp != nullptr) {

          if (temp->key == fromVertex.key) {
            if (temp->right == nullptr) {
              temp->right = newEdgeOne;
              newEdgeOne->left = temp;
            } else {
              newEdgeOne->right = temp->right;
              temp->right->left = newEdgeOne;
              newEdgeOne->left = temp;
              temp->right = newEdgeOne;
            }
            temp = temp->next;
          } else if (temp->key == toVertex.key) {
            if (temp->right == nullptr) {
              temp->right = newEdgeTwo;
              newEdgeTwo->left = temp;
            } else {
              newEdgeTwo->right = temp->right;
              temp->right->left = newEdgeTwo;
              newEdgeTwo->left = temp;
              temp->right = newEdgeTwo;
            }
            temp = temp->next;

          } else
            temp = temp->next;
        }
      }
      edgeCount++; 
    } else {
      throw std::string("Cannot add edge, The edge already exists");
    }
  } else
    throw std::string("Cannot add edge, One or more vertices doesnot exist");
}

bool Graph::edgeExists(Vertex from, Vertex to) {
  Vertex *temp = HEAD;

  while (temp != nullptr) {
    if (temp->key == from.key) {
      Vertex *tempRight = temp->right;
      while (tempRight != nullptr) {
        if (tempRight->key == to.key)
          return true;
        tempRight = tempRight->right;
      }
    }
    temp = temp->next;
  }
  return false;
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

void Graph::removeEdge(Vertex fromVertex, Vertex toVertex) {
  bool fromExists = keyExists(fromVertex.key);
  bool ToExists = keyExists(toVertex.key);
  Vertex *temp = HEAD;

  if (fromExists && ToExists) {
    if (edgeExists(fromVertex, toVertex)) {
      if (isDirected()) {
        Vertex *temp = HEAD;

        while (temp != nullptr && temp->key != fromVertex.key) {
          temp = temp->next;
        }

        temp = temp->right;
        while (temp != nullptr) {
          if (temp->key == toVertex.key) {
            Vertex *edgeToDelete = temp;
            temp->left->right = temp->right;
            if (edgeToDelete->right != nullptr)
              temp->right->left = temp->left;

            temp = temp->left->right;
            delete edgeToDelete;
            break;
          }
          temp = temp->right;
        }
      } else {
        Vertex *temp = HEAD;

        while (temp != nullptr) {
          Vertex *tempRight = temp;

          if (temp->key == fromVertex.key) {
            while (tempRight != nullptr) {
              if (tempRight->key == toVertex.key) {
                Vertex *edgeToDelete = tempRight;
                tempRight->left->right = tempRight->right;
                if (edgeToDelete->right != nullptr)
                  tempRight->right->left = tempRight->left;
                tempRight = tempRight->left->right;
                delete edgeToDelete;
                break;
              }
              tempRight = tempRight->right;
            }
          }

          if (temp->key == toVertex.key) {
            while (tempRight != nullptr) {
              if (tempRight->key == fromVertex.key) {
                Vertex *edgeToDelete = tempRight;
                tempRight->left->right = tempRight->right;
                if (edgeToDelete->right != nullptr)
                  tempRight->right->left = tempRight->left;
                tempRight = tempRight->left->right;
                delete edgeToDelete;
                break;
              }
              tempRight = tempRight->right;
            }
          }
          temp = temp->next;
        }
      }
      edgeCount--;
    } else {
      throw std::string("Cannot remove edge, The edge doesnot exists");
    }
  } else
    throw std::string("Cannot remove edge, One or more vertices doesnot exist");
}

void Graph::removeEdges(Vertex &vertex) {

  Vertex *temp = HEAD;
  while (temp != nullptr) {
    if (temp->key == vertex.key) {
      temp = temp->next;
      continue;
    }

    Vertex *tempRight = temp->right;

    while (tempRight != nullptr) {
      if (tempRight->key == vertex.key) {
        Vertex *edgeToDelete = tempRight;
        tempRight->left->right = tempRight->right;
        if (edgeToDelete->right != nullptr)
          tempRight->right->left = tempRight->left;

        tempRight = tempRight->left->right;
        delete edgeToDelete;
        edgeCount--;
        break;
      }
      tempRight = tempRight->right;
    }
    temp = temp->next;
  }
}

int Graph::totalEdges() {
  int totalEdges = 0;
  Vertex *temp = HEAD;
  while (temp != nullptr) {
    Vertex *tempRight = temp->right;
    while (tempRight != nullptr) {
      totalEdges++;
      tempRight = tempRight->right;
    }
    temp = temp->next;
  }
  return edgeCount;
}

void Graph::vertices() {
  Vertex *tempDown = HEAD;
  while (tempDown != nullptr) {
    std::cout << tempDown->key << " ";
    tempDown = tempDown->next;
  }
  std::cout << "\n";
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
  int inDegree = 0;
  Vertex *temp = HEAD;

  while (temp != nullptr && temp->key != vertex.key) {
    temp = temp->next;
  }

  if (temp == nullptr)
    throw std::string("The vertex doesnot exist");

  temp = HEAD;
  while (temp != nullptr) {
    Vertex *tempRight = temp->right;
    while (tempRight != nullptr) {
      if (tempRight->key == vertex.key)
        inDegree++;
      tempRight = tempRight->right;
    }
    temp = temp->next;
  }
  return inDegree;
}

int Graph::outDegree(Vertex vertex) {
  int outDegree = 0;
  Vertex *temp = HEAD;
  while (temp != nullptr && vertex.key != temp->key) {
    temp = temp->next;
  }
  if (temp == nullptr)
    throw std::string("The vertex doesnot exist");

  temp = temp->right;
  while (temp != nullptr) {
    temp = temp->right;
    outDegree++;
  }
  return outDegree;
}


int Graph::degree(Vertex vertex) {
  int inDeg = inDegree(vertex);
  int outDeg = outDegree(vertex);
  return inDeg + outDeg;
}


void Graph::neighbours(Vertex vertex) {
  Vertex *temp = HEAD;
  while (temp != nullptr && temp->key != vertex.key) {
    temp = temp->next;
  }
  if (temp == nullptr)
    throw std::string("The given vertex doesnot exist");
  temp = temp->right;
  while (temp != nullptr) {
    std::cout << temp->key << " ";
    temp = temp->right;
  }
  std::cout << "\n";
}


bool Graph::areNeighbours(Vertex vertexOne, Vertex vertexTwo) {

  Vertex *temp = HEAD;
  Vertex *first = nullptr;
  Vertex *second = nullptr;

  while (temp != nullptr) {
    if (temp->key == vertexOne.key)
      first = temp;

    if (temp->key == vertexTwo.key)
      second = temp;

    temp = temp->next;
  }
  if (first == nullptr || second == nullptr)
    return false;

  first = first->right;

  while (first != nullptr) {
    if (first->key == vertexTwo.key)
      return true;
    first = first->right;
  }

  second = second->right;

  while (second != nullptr) {
    if (second->key == vertexOne.key)
      return true;
    second = second->right;
  }
  return false;

  // // More time complexity
  // Vertex *temp = HEAD;
  // while (temp != nullptr) {
  //   if (vertexOne.key == temp->key) {
  //     Vertex *tempRight = temp->right;
  //     while (tempRight != nullptr) {
  //       if (vertexTwo.key == tempRight->key)
  //         return true;
  //       tempRight = tempRight->right;
  //     }
  //   } else if (vertexTwo.key == temp->key) {
  //     Vertex *tempRight = temp->right;
  //     while (tempRight != nullptr) {
  //       if (vertexOne.key == tempRight->key)
  //         return true;
  //       tempRight = tempRight->right;
  //     }
  //   } else {
  //     temp = temp->next;
  //     continue;
  //   }
  //   temp = temp->next;
  // }
  // return false;
}

void Graph::adjacencyList() {
  Vertex *tempDown = HEAD;

  while (tempDown != nullptr) {
    Vertex *tempRight = tempDown->right;
    std::cout << tempDown->key << "->";
    while (tempRight != nullptr) {
      std::cout << tempRight->key << " ";
      tempRight = tempRight->right;
    }
    tempDown = tempDown->next;
    std::cout << "\n";
  }
}