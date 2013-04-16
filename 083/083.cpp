//
//  main.cpp
//  Prbl083
//  Project Euler
//
//  Created by Zhiming Wang on 12/12/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Minimal distance in graph. Dijkstra's algorithm.
//  ------------------------------------------------
//  Answer: 425185
//

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <sstream>

static const unsigned RANGE = 80;

struct Node;
struct Arc;
class Graph;

struct Node {
    
    unsigned row, col;
    int value;
    std::vector<Arc*> arcs;
    
    Node();
    Node(unsigned row, unsigned col, int value) {
        this->row = row;
        this->col = col;
        this->value = value;
    }
    
};

// Directed, not weighted
struct Arc {
    
    Node* begin;
    Node* end;
    
    Arc();
    Arc(Node* begin, Node* end) {
        this->begin = begin;
        this->end = end;
    }
    
};

class Graph {
    
    std::vector<Node*> nodes;
    std::vector<Arc*> arcs;
    
public:
    
    Graph();
    Graph(const int matrix[RANGE + 1][RANGE + 1]) {
        // Construct nodes
        for (unsigned row = 1; row <= RANGE; ++row) {
            for (unsigned col = 1; col <= RANGE; ++col) {
                Node* node = new Node(row, col, matrix[row][col]);
                nodes.push_back(node);
            }
        }
        // Construct arcs
        // Horizontal ones
        for (unsigned row = 1; row <= RANGE; ++row) {
            for (unsigned col = 1; col <= RANGE - 1; ++col) {
                Node* node1 = findNode(row, col);
                Node* node2 = findNode(row, col + 1);
                Arc* arc1 = new Arc(node1, node2);
                Arc* arc2 = new Arc(node2, node1);
                node1->arcs.push_back(arc1);
                node2->arcs.push_back(arc2);
                arcs.push_back(arc1);
                arcs.push_back(arc2);
            }
        }
        // Vertical ones
        for (unsigned col = 1; col <= RANGE; ++col) {
            for (unsigned row = 1; row <= RANGE - 1; ++row) {
                Node* node1 = findNode(row, col);
                Node* node2 = findNode(row + 1, col);
                Arc* arc1 = new Arc(node1, node2);
                Arc* arc2 = new Arc(node2, node1);
                node1->arcs.push_back(arc1);
                node2->arcs.push_back(arc2);
                arcs.push_back(arc1);
                arcs.push_back(arc2);
            }
        }
    }
    
    ~Graph() {
        for (std::vector<Arc*>::iterator i = arcs.begin();
             i != arcs.end();
             ++i) {
            delete *i;
        }
        for (std::vector<Node*>::iterator i = nodes.begin();
             i != nodes.end();
             ++i) {
            delete *i;
        }
    }
    
    Node* findNode(unsigned row, unsigned col) {
        return nodes[(row - 1) * RANGE + (col - 1)];
    }
};

// Used for Dijkstra's algorithm
struct Path {
    Node* endNode;
    int cost;
    
    Path();
    Path(const Path& other) {
        *this = other;
    }
    Path(Arc* arc) {
        endNode = arc->end;
        cost = arc->begin->value + arc->end->value;
    }
    Path(const Path& originalPath, Node* newEndNode) {
        endNode = newEndNode;
        cost = originalPath.cost + newEndNode->value;
    }
    
    Path& operator=(const Path& other) {
        endNode = other.endNode;
        cost = other.cost;
        return *this;
    }
    
    friend bool operator<(const Path& lhs, const Path& rhs);
};

bool operator<(const Path& lhs, const Path& rhs) {
    if (lhs.cost < rhs.cost) {
        return true;
    } else if (lhs.cost > rhs.cost) {
        return false;
    } else if (lhs.endNode < rhs.endNode) {
        return true;
    } else {
        return false;
    }
}

int main() {
    std::ifstream input("/Users/ZhimingWang/Dropbox/02ProgrammingProjects/"
                        "ProjectEuler/C++/Prbl082/matrix.txt");
    if (!input.is_open()) {
        std::cerr << "Error opening matrix.txt!" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    // Read matrix.
    int matrix[RANGE + 1][RANGE + 1];
    for (int row = 1; row <= RANGE; ++row) {
        std::string line;
        std::getline(input, line);
        std::istringstream lineStream(line);
        for (int col = 1; col <= RANGE; ++col) {
            std::string element;
            std::getline(lineStream, element, ',');
            matrix[row][col] = std::atoi(element.c_str());
        }
    }
    
    // Construct graph.
    Graph graph(matrix);
    
    // Perform Dijkstra's algorithm.
    
    // Priority queue of paths, modeled by ordered set.
    std::set<Path> paths;
    std::set<Node*> fixedDistanceNodes;
    
    Node* departure = graph.findNode(1, 1);
    Node* destination = graph.findNode(RANGE, RANGE);
    
    fixedDistanceNodes.insert(departure);
    for (std::vector<Arc*>::const_iterator i = departure->arcs.begin();
         i != departure->arcs.end();
         ++i) {
        Path path(*i);
        paths.insert(path);
    }
    
    while (true) {
        Path newPath = *(paths.begin());
        paths.erase(paths.begin());
        Node* newEndNode = newPath.endNode;
        if (fixedDistanceNodes.find(newEndNode) != fixedDistanceNodes.end()) {
            continue;
        }
        if (newEndNode == destination) {
            std::cout << newPath.cost << std::endl;
            break;
        }

        // <code>newEndNode</code> has not been fixed.
        fixedDistanceNodes.insert(newEndNode);
        std::vector<Arc*> extensionArcs = newEndNode->arcs;
        for (std::vector<Arc*>::const_iterator i = extensionArcs.begin();
             i != extensionArcs.end();
             ++i) {
            Arc* const& extensionArc = *i;
            Path extensionPath(newPath, extensionArc->end);
            paths.insert(extensionPath);
        }
    }
    
    return 0;
}