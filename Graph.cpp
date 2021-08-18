#include "Graph.h"
#include <iostream>

bool Graph::isEmpty() { return HEAD == nullptr ? true : false; }

bool Graph::isDirected() { return isDiGraph; }

void Graph::addVertex(Vertex newVertex) {
  if (!cityCodeExists(newVertex.cityCode)) {

    // add to head
    Vertex *vertexToAdd = new Vertex(newVertex);
    if (isEmpty()) {
      HEAD = vertexToAdd;
    } else {
      vertexToAdd->next = HEAD;
      HEAD = vertexToAdd;
    }
  } else
    throw std::string("City already exists in the graph");
}

bool Graph::cityCodeExists(int cityCode) {
  Vertex *temp = HEAD;

  // traversing down the vertices
  while (temp != nullptr) {
    if (cityCode == temp->cityCode) {
      return true; // return true if cityCode exists
    }
    temp = temp->next;
  }
  return false;
}

bool Graph::edgeExists(Vertex from, Vertex to) {
  Vertex *temp = HEAD;

  // traversing down the vertices
  while (temp != nullptr) {
    if (temp->cityCode == from.cityCode) {
      // vertex 1(from) is found
      Edge *tempRight = temp->edgesHead;
      // traversing right of the vertex 1
      while (tempRight != nullptr) {
        if (tempRight->vertex->cityCode == to.cityCode)
          return true; // return true if edge exists
        tempRight = tempRight->right;
      }
    }
    temp = temp->next;
  }
  return false;
}

void Graph::addEdge(Vertex fromVertex, Vertex toVertex,
                    int distanceInKilometers) {

  // check if the two vertices exists
  Vertex *from = nullptr;
  Vertex *to = nullptr;
  Vertex *temp = HEAD;
  while (temp != nullptr) {
    if (temp->cityCode == fromVertex.cityCode)
      from = temp;
    if (temp->cityCode == toVertex.cityCode)
      to = temp;
    temp = temp->next;
  }
  if (!from || !to)
    throw std::string("Cannot add path, One or more city doesnot exist");

  // check if the edge exists
  bool exists = edgeExists(fromVertex, toVertex);

  if (exists)
    throw std::string("Path already exists");

  if (fromVertex.cityCode == toVertex.cityCode)
    throw std::string("Cannot add path between same city");

  if (isDirected()) {
    Edge *newEdge = new Edge(toVertex, distanceInKilometers);
    // add to head
    if (from->edgesHead == nullptr) {
      from->edgesHead = newEdge;
    } else {
      newEdge->right = from->edgesHead;
      from->edgesHead = newEdge;
    }
  } else {
    // for undirected we add 2 edges
    Edge *newEdgeOne = new Edge(toVertex, distanceInKilometers);
    Edge *newEdgeTwo = new Edge(fromVertex, distanceInKilometers);
    // add to head of vertex 1
    if (from->edgesHead == nullptr) {
      from->edgesHead = newEdgeOne;
    } else {
      newEdgeOne->right = from->edgesHead;
      from->edgesHead = newEdgeOne;
    }

    // add to head of vertex 2
    if (to->edgesHead == nullptr) {
      to->edgesHead = newEdgeTwo;
    } else {
      newEdgeTwo->right = to->edgesHead;
      to->edgesHead = newEdgeTwo;
    }
  }
  edgeCount++; // update the edge counts
}

void Graph::removeVertex(Vertex vertexToRemove) {
  Vertex *temp = HEAD;
  Vertex *parent = nullptr;
  int totalEdgesRemoved = 0;

  // traversing down the verteices and checking if the vertex exists
  while (temp != nullptr && vertexToRemove.cityCode != temp->cityCode) {
    parent = temp;
    temp = temp->next;
  }
  if (temp == nullptr)
    throw std::string("The vertex doesnot exist");

  Edge *edges = temp->edgesHead;

  // removing all edges that leave the vertex one by one from head
  while (temp->edgesHead != nullptr) {
    Edge *edgeToDelete = temp->edgesHead;
    temp->edgesHead = temp->edgesHead->right;
    totalEdgesRemoved++;
    delete edgeToDelete;
  }

  // removing all edges related to the vertex and updating the total edges
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

    if (temp->cityCode == vertex.cityCode) {
      temp = temp->next;
      continue; // no need to check the edges for the vertex which need to be
                // deleted
    }

    Edge *edges = temp->edgesHead;
    Edge *parent = nullptr;

    /* traversing the edges for each vertex and checking if an edge with the
    given vertex exists. If it does, we delete it
    */
    while (edges != nullptr && edges->vertex->cityCode != vertex.cityCode) {
      parent = edges;
      edges = edges->right;
    }
    if (edges != nullptr) {
      // edge is found
      Edge *edgeToDelete = edges;

      if (parent == nullptr)
        temp->edgesHead = edges->right;
      else
        parent->right = edges->right;

      delete edgeToDelete; // handling the pointers and deleting the edge

      totalEdgesRemoved++; // update the edge count
    }

    temp = temp->next;
  }
  return totalEdgesRemoved; // return the total edges removed
}

void Graph::removeEdge(Vertex fromVertex, Vertex toVertex) {

  // check if the two vertices exists
  Vertex *from = nullptr;
  Vertex *to = nullptr;
  Vertex *temp = HEAD;
  while (temp != nullptr) {
    if (temp->cityCode == fromVertex.cityCode)
      from = temp;
    if (temp->cityCode == toVertex.cityCode)
      to = temp;
    temp = temp->next;
  }
  if (!from || !to)
    throw std::string("Cannot add edge, One or more vertices doesnot exist");

  // check if the edge exists
  bool exists = edgeExists(fromVertex, toVertex);

  if (!exists)
    throw std::string("Edge already exists");

  if (isDirected()) {
    Edge *edges = from->edgesHead;
    Edge *parent = nullptr;
    // traversing the edges until the edge is found and deleting it
    while (edges != nullptr & edges->vertex->cityCode != toVertex.cityCode) {
      parent = edges;
      edges = edges->right;
    }

    if (edges != nullptr) {
      // edge is found
      Edge *edgeToDelete = edges;

      if (parent == nullptr)
        temp->edgesHead = edges->right;
      else
        parent->right = edges->right;

      delete edgeToDelete;
    }

  } else {
    // for undirected we delete 2 edges
    Edge *edges = from->edgesHead;
    Edge *parent = nullptr;

    // traversing the edges until the edge of vertex 1-2 is found and deleting
    // it
    while (edges != nullptr && edges->vertex->cityCode != toVertex.cityCode) {
      parent = edges;
      edges = edges->right;
    }

    if (edges != nullptr) {
      // edge found
      Edge *edgeToDelete = edges;
      if (parent == nullptr)
        from->edgesHead = edges->right;
      else
        parent->right = edges->right;

      delete edgeToDelete;
    }

    edges = to->edgesHead;
    parent = nullptr;
    // traversing the edges until the edge of vertex 2-1 is found and deleting
    // it
    while (edges != nullptr && edges->vertex->cityCode != fromVertex.cityCode) {
      parent = edges;
      edges = edges->right;
    }

    if (edges != nullptr) {
      // edge found
      Edge *edgeToDelete = edges;
      if (parent == nullptr)
        to->edgesHead = edges->right;
      else
        parent->right = edges->right;

      delete edgeToDelete;
    }
  }
  edgeCount--;
}

void Graph::vertices() {
  // traversing down the vertices
  Vertex *tempDown = HEAD;
  while (tempDown != nullptr) {
    std::cout << tempDown->cityName << " "; // print each vertex
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

  // traversing down the veretices and checking if the vertex exists
  while (temp != nullptr && temp->cityCode != vertex.cityCode) {
    temp = temp->next;
  }

  if (temp == nullptr)
    throw std::string("The city doesnot exist");

  temp = HEAD;

  // traversing down the vertices
  while (temp != nullptr) {
    Edge *edges = temp->edgesHead;
    // traversing the edges for each vertex
    while (edges != nullptr) {
      if (edges->vertex->cityCode == vertex.cityCode)
        inDegree++; // update the count if edge exists
      edges = edges->right;
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
    if (temp->cityCode == vertexOne.cityCode)
      first = temp; // found 1st vertex

    if (temp->cityCode == vertexTwo.cityCode)
      second = temp; // found 2nd vertex

    temp = temp->next;
  }
  if (first == nullptr || second == nullptr)
    return false;

  Edge *edges = first->edgesHead;

  // checking the edges of 1st vertex by traversing right
  while (edges != nullptr) {
    if (edges->vertex->cityCode == vertexTwo.cityCode)
      return true; // return true if edge extists
    edges = edges->right;
  }

  edges = second->edgesHead;

  // if there is no edge from vertex 1 to 2
  // check the edges of 2nd vertex by traversing right
  while (edges != nullptr) {
    if (edges->vertex->cityCode == vertexOne.cityCode)
      return true; // return true if edge extists
    edges = edges->right;
  }
  return false;
}

void Graph::adjacencyList() {
  Vertex *tempDown = HEAD;

  // traversing down the vertices
  while (tempDown != nullptr) {
    Edge *tempRight = tempDown->edgesHead;
    std::cout << tempDown->cityName
              << ((tempDown->edgesHead == nullptr) ? " -->" : "");

    // traversing the edges for eac vertex
    while (tempRight != nullptr) {
      std::cout << " -- (" << tempRight->distanceInKilometers << ") --> "
                << tempRight->vertex->cityName;
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
    Edge *edges = temp->edgesHead;

    // traversing the edges for each vertex
    while (edges != nullptr) {
      totalEdges++; // updating the count for each edge
      edges = edges->right;
    }
    temp = temp->next;
  }
  return edgeCount;
}

int Graph::outDegree(Vertex vertex) {
  int outDegree = 0;
  Vertex *temp = HEAD;

  // finding the vertex
  while (temp != nullptr && vertex.cityCode != temp->cityCode) {
    temp = temp->next;
  }
  if (temp == nullptr)
    throw std::string("The city doesnot exist");

  Edge *edges = temp->edgesHead;

  // traversing the edges for the vertex
  while (edges != nullptr) {
    edges = edges->right;
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

  // traversing down the vertices and checking if it exists
  while (temp != nullptr && temp->cityCode != vertex.cityCode) {
    temp = temp->next;
  }
  if (temp == nullptr)
    throw std::string("The city doesnot exist");

  Edge *edges = temp->edgesHead;

  // traversing the edges and printing out all the neighbours one after another
  while (edges != nullptr) {
    std::cout << edges->vertex->cityName << " ";
    edges = edges->right;
  }
  std::cout << "\n";
}
