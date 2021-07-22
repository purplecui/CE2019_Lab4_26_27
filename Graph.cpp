#include "Graph.h"
#include <iostream>

bool Graph::isEmpty() { return HEAD == nullptr ? true : false; }

bool Graph::isDirected() { return isDiGraph; }
