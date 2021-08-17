#include "Graph.h"
#include <iostream>

bool Graph::isEmpty() { return HEAD == nullptr ? true : false; }

bool Graph::isDirected() { return isDiGraph; }

void Graph::addVertex(Vertex newVertex) {
  if (!keyExists(newVertex.key)) {

    // add to head
    Vertex *vertexToAdd = new Vertex(newVertex);
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

  // traversing down the vertices
  while (temp != nullptr) {
    if (key == temp->key) {
      return true; // return true if key exists
    }
    temp = temp->next;
  }
  return false;
}

bool Graph::edgeExists(Vertex from, Vertex to) {
  Vertex *temp = HEAD;

  // traversing down the vertices
  while (temp != nullptr) {
    if (temp->key == from.key) {
      // vertex 1(from) is found
      Vertex *tempRight = temp->right;
      // traversing right of the vertex 1
      while (tempRight != nullptr) {
        if (tempRight->key == to.key)
          return true; // return true if edge exists
        tempRight = tempRight->right;
      }
    }
    temp = temp->next;
  }
  return false;
}

void Graph::addEdge(Vertex fromVertex, Vertex toVertex) {

  // check if vertex exists
  bool fromExists = keyExists(fromVertex.key);
  bool ToExists = keyExists(toVertex.key);
  Vertex *temp = HEAD;

  if (fromExists && ToExists) {
    if (!edgeExists(fromVertex, toVertex)) {

      if (isDirected()) {
        Vertex *newEdge = new Vertex(toVertex);
        Vertex *temp = HEAD;

        // traversing down to find the vertex
        while (temp != nullptr && temp->key != fromVertex.key) {
          temp = temp->next;
        }
        // add to head
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
        // if undirected then we add 2 edges
        Vertex *newEdgeOne = new Vertex(toVertex);
        Vertex *newEdgeTwo = new Vertex(fromVertex);
        Vertex *temp = HEAD;

        // traversing down the find the vertices
        while (temp != nullptr) {

          if (temp->key == fromVertex.key) {
            // found the 1st vertex
            // add to head
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
            // found the 2nd vertex
            // add to head
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
      edgeCount++; // update the edge count
    } else {
      throw std::string("Cannot add edge, The edge already exists");
    }
  } else
    throw std::string("Cannot add edge, One or more vertices doesnot exist");
}

void Graph::removeVertex(Vertex vertexToRemove) {
  Vertex *temp = HEAD;
  Vertex *parent = nullptr;
  int totalEdgesRemoved = 0;

  // find the vertex
  while (temp != nullptr && vertexToRemove.key != temp->key) {
    parent = temp;
    temp = temp->next;
  }
  if (temp == nullptr)
    throw std::string("The vertex doesnot exist");

  // remove all edges to the left of the vertex to remove one by one
  Vertex *tempRight = temp->right;
  while (tempRight != nullptr) {
    Vertex *edgeToDelete = tempRight;

    tempRight->left->right = tempRight->right;
    if (edgeToDelete->right != nullptr)
      tempRight->right->left = tempRight->left;

    tempRight = tempRight->left->right;
    totalEdgesRemoved++;
    delete edgeToDelete;
  }

  // remove all edges related to the vertex and update the total edges removed
  totalEdgesRemoved += removeEdges(vertexToRemove);

  // update the edge count
  edgeCount -= isDirected() ? totalEdgesRemoved : (totalEdgesRemoved / 2);

  if (parent == nullptr) {
    HEAD = temp->next;
  } else
    parent->next = temp->next;

  // remove the vertex itself
  delete temp;
}

int Graph::removeEdges(Vertex &vertex) {
  int totalEdgesRemoved = 0;
  Vertex *temp = HEAD;
  // traversing down the vertices
  while (temp != nullptr) {
    if (temp->key == vertex.key) {
      temp = temp->next;
      continue; // no need to check the right for the vertex which need to be
                // deleted
    }

    Vertex *tempRight = temp->right;

    /* traversing right for each vertex and checking if an edge with the given
    vertex exists. If it does, we delete it
    */
    while (tempRight != nullptr) {
      if (tempRight->key == vertex.key) {
        // edge is found
        Vertex *edgeToDelete = tempRight;
        tempRight->left->right = tempRight->right;
        if (edgeToDelete->right != nullptr)
          tempRight->right->left = tempRight->left;

        tempRight = tempRight->left->right;
        delete edgeToDelete; // handling the pointers, deleting the edge and
                             // breaking out of the right traversal

        totalEdgesRemoved++; // update the edge count
        break;
      }
      tempRight = tempRight->right;
    }
    temp = temp->next;
  }
  return totalEdgesRemoved; // return the total edges removed
}

void Graph::removeEdge(Vertex fromVertex, Vertex toVertex) {

  // check if vertex exists
  bool fromExists = keyExists(fromVertex.key);
  bool ToExists = keyExists(toVertex.key);
  Vertex *temp = HEAD;

  if (fromExists && ToExists) {
    if (edgeExists(fromVertex, toVertex)) {
      if (isDirected()) {
        // traverse down to find the vertex
        Vertex *temp = HEAD;
        while (temp != nullptr && temp->key != fromVertex.key) {
          temp = temp->next;
        }

        temp = temp->right;
        // traversing right to find the edge and delete it
        while (temp != nullptr) {
          if (temp->key == toVertex.key) {
            // edge to delete found
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
        // if undirected then we remove 2 edges

        Vertex *temp = HEAD;

        // traversing down to find the vertices
        while (temp != nullptr) {
          Vertex *tempRight = temp;

          if (temp->key == fromVertex.key) {
            // vertex one found
            // traversing right to find the edge and deleting it
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
            // vertex two found
            // traversing right to find the edge and deleting it
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
      edgeCount--; // update the edge count
    } else {
      throw std::string("Cannot remove edge, The edge doesnot exists");
    }
  } else
    throw std::string("Cannot remove edge, One or more vertices doesnot exist");
}

void Graph::vertices() {
  // traversing down the vertices
  Vertex *tempDown = HEAD;
  while (tempDown != nullptr) {
    std::cout << tempDown->key << " "; // print each vertex
    tempDown = tempDown->next;
  }
  std::cout << "\n";
}

int Graph::totalVertices() {
  int totalVertices = 0;
  Vertex *temp = HEAD;

  // traversing down the vertices
  while (temp != nullptr) {
    totalVertices++; // updating count
    temp = temp->next;
  }
  return totalVertices;
}

int Graph::inDegree(Vertex vertex) {
  int inDegree = 0;
  Vertex *temp = HEAD;

  // finding the veretx
  while (temp != nullptr && temp->key != vertex.key) {
    temp = temp->next;
  }

  if (temp == nullptr)
    throw std::string("The vertex doesnot exist");

  temp = HEAD;
  // traversing down the vertices
  while (temp != nullptr) {
    Vertex *tempRight = temp->right;
    // traversing right for each edge
    while (tempRight != nullptr) {
      if (tempRight->key == vertex.key)
        inDegree++; // update the count if edge exists
      tempRight = tempRight->right;
    }
    temp = temp->next;
  }
  return inDegree;
}

bool Graph::areNeighbours(Vertex vertexOne, Vertex vertexTwo) {
  Vertex *temp = HEAD;
  Vertex *first = nullptr;
  Vertex *second = nullptr;

  // finding the first and second vertex
  while (temp != nullptr) {
    if (temp->key == vertexOne.key)
      first = temp; // found 1st vertex

    if (temp->key == vertexTwo.key)
      second = temp; // found 2nd vertex

    temp = temp->next;
  }
  if (first == nullptr || second == nullptr)
    return false;

  first = first->right;

  // checking the edges of 1st vertex by traversing right
  while (first != nullptr) {
    if (first->key == vertexTwo.key)
      return true; // return true if edge extists
    first = first->right;
  }

  second = second->right;

  // if there is no edge from vertex 1 to 2
  // check the edges of 2nd vertex by traversing right
  while (second != nullptr) {
    if (second->key == vertexOne.key)
      return true; // return true if edge extists
    second = second->right;
  }
  return false;
}

void Graph::adjacencyList() {
  Vertex *tempDown = HEAD;

  // traversing down the vertices
  while (tempDown != nullptr) {
    Vertex *tempRight = tempDown->right;
    std::cout << tempDown->key << "->";

    // traversing right for all vertices
    while (tempRight != nullptr) {
      std::cout << tempRight->key << " ";
      tempRight = tempRight->right;
    }
    tempDown = tempDown->next;
    std::cout << "\n";
  }
}

int Graph::totalEdges() {
  int totalEdges = 0;
  Vertex *temp = HEAD;

  // traversing down the verteices
  while (temp != nullptr) {
    Vertex *tempRight = temp->right;

    // traversing right for each vertex
    while (tempRight != nullptr) {
      totalEdges++; // updating the count for each edge
      tempRight = tempRight->right;
    }
    temp = temp->next;
  }
  return edgeCount;
}

int Graph::outDegree(Vertex vertex) {
  int outDegree = 0;
  Vertex *temp = HEAD;

  // finding the vertex
  while (temp != nullptr && vertex.key != temp->key) {
    temp = temp->next;
  }
  if (temp == nullptr)
    throw std::string("The vertex doesnot exist");

  temp = temp->right;

  // traversing right for the vertex
  while (temp != nullptr) {
    temp = temp->right;
    outDegree++; // updating count for each edge
  }
  return outDegree;
}

int Graph::degree(Vertex vertex) {
  int inDeg = inDegree(vertex);
  int outDeg = outDegree(vertex);
  return inDeg + outDeg; // degree = indgree + outdegree
}

void Graph::neighbours(Vertex vertex) {
  Vertex *temp = HEAD;

  // finding the vertex
  while (temp != nullptr && temp->key != vertex.key) {
    temp = temp->next;
  }
  if (temp == nullptr)
    throw std::string("The given vertex doesnot exist");

  temp = temp->right;

  // traversing right and printing out all the neighbours one after another
  while (temp != nullptr) {
    std::cout << temp->key << " ";
    temp = temp->right;
  }
  std::cout << "\n";
}

