#include "Graph.h"
#include <iostream>

int main() {

  try {
    Graph graph(false);
    Vertex ktm(1011, "Kathmandu");
    Vertex jhapa(7897, "Jhapa");
    Vertex morang(7545, "Morang");
    Vertex illam(4440, "Illam");
    Vertex pokhara(3189, "Pokhara");
    Vertex chitwan(5014, "Chitwan");
    graph.addVertex(ktm);
    graph.addVertex(jhapa);
    graph.addVertex(morang);
    std::cout << "\nVertices: ";
    graph.vertices();
    std::cout << "Total vertices: " << graph.totalVertices() << std::endl;
    graph.addVertex(illam);
    graph.addVertex(pokhara);
    graph.addVertex(chitwan);
    std::cout << "Vertices: ";
    graph.vertices();
    std::cout << "Total vertices: " << graph.totalVertices() << std::endl;
    // std::cout << std::endl;
    graph.addEdge(ktm, chitwan, 100);
    graph.addEdge(ktm, pokhara, 200);
    graph.addEdge(ktm, jhapa, 496);
    graph.addEdge(jhapa, morang, 32);
    graph.addEdge(jhapa, chitwan, 596);
    graph.addEdge(morang, ktm, 496 - 32);
    graph.addEdge(illam, jhapa, 75);
    graph.addEdge(pokhara, jhapa, 696);
    std::cout << "Adjacenecy List: " << std::endl;
    graph.adjacencyList();
    std::cout << "\nNeighbours of Jhapa: ";
    graph.neighbours(jhapa);
    std::cout << "\n";
    std::cout << "Neighbours of Kathmandu: ";
    graph.neighbours(ktm);
    std::cout << "\n";

    std::cout << std::endl;

    std::cout << "Are neighbours(jhapa and ktm): "
              << graph.areNeighbours(ktm, chitwan) << std::endl;
    std::cout << "\n";
    std::cout << "Degree of vetex Jhapa:" << std::endl;
    std::cout << "Indegree: " << graph.inDegree(jhapa) << std::endl;
    std::cout << "OutDegree: " << graph.outDegree(jhapa) << std::endl;
    std::cout << "Degree: " << graph.degree(jhapa) << std::endl;

    std::cout << "Total Edges: " << graph.totalEdges() << std::endl;

    graph.removeVertex(jhapa);
    std::cout << "\nAfter removing vertex Jhapa" << std::endl;
    std::cout << "Total vertices: " << graph.totalVertices() << std::endl;

    graph.removeEdge(ktm, pokhara);
    std::cout << "\nAfter removing edge Ktm, Pokhara" << std::endl;
    std::cout << "Total Edges: " << graph.totalEdges() << std::endl;

    graph.removeVertex(morang);
    std::cout << "\nAfter removing vertex morang" << std::endl;
    std::cout << "Total vertices: " << graph.totalVertices() << std::endl;
    std::cout << "Total Edges: " << graph.totalEdges() << std::endl;

    std::cout << "\nFinal Graph:" << std::endl;
    graph.adjacencyList();
  } catch (std::string error) {
    std::cout << error << std::endl;
  }

  bool generate;
  std::cout << "\nDo you want to generate a random graph?(1/0): ";
  std::cin >> generate;
  std::cout << "\nThe random graph will be a simple graph with no loop and no "
               "multiple/"
               "parallel edges\n "
            << std::endl;

  if (generate) {
    int totalVertices;
    int totalEdges;
    bool isDirected;
    std::cout << "Enter total number of vertices: ";
    std::cin >> totalVertices;
    std::cout << "Enter total number of edges: ";
    std::cin >> totalEdges;
    std::cout << "Directed or Unidirected(1/0): ";
    std::cin >> isDirected;

    try {
      Graph random(totalVertices, totalEdges, isDirected);
      std::cout << "\nTotal Edges: " << random.totalEdges() << std::endl;
      std::cout << "Total vertices: " << random.totalVertices() << std::endl;
    } catch (std::string error) {
      std::cout << error << std::endl;
    }
  }
}