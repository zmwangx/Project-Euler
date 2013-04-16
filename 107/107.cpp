//
//  main.cpp
//  Prbl107
//  Project Euler
//
//  Created by Zhiming Wang on 12/17/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Kruskal's algorithm for minimum spanning tree.
//  ----------------------------------------------
//  Answer: 259679
//

#include "unionFindSet.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <string>

static const int NUMBER_OF_VERTECES = 40;
static const std::string NO_EDGE_INDICATOR = "-";

typedef int NodeNo;

struct Edge {
    NodeNo start;
    NodeNo finish;
    int weight;
    
public:
    
    Edge() {
        // Do nothing.
    }
    
    Edge(NodeNo start, NodeNo finish, int weight) {
        this->start = start;
        this->finish = finish;
        this->weight = weight;
    }
    
    Edge(const Edge& other) {
        *this = other;
    }
    
    ~Edge() {
        // Do nothing.
    }
    
    Edge& operator=(const Edge& other) {
        start = other.start;
        finish = other.finish;
        weight = other.weight;
        return *this;
    }
    
    friend bool operator<(const Edge& edge1, const Edge& edge2);
    
};

bool operator<(const Edge& edge1, const Edge& edge2) {
    if (edge1.weight < edge2.weight) {
        return true;
    } else if (edge2.weight < edge1.weight) {
        return false;
    } else if (edge1.start < edge2.start) {
        return true;
    } else if (edge2.start < edge1.start) {
        return false;
    } else if (edge1.finish < edge2.finish) {
        return true;
    } else {
        return false;
    }
}

int main() {
    std::set<Edge> edgeList; // set as priority queue
    
    std::ifstream input("/Users/ZhimingWang/Dropbox/02ProgrammingProjects/"
                        "ProjectEuler/C++/Prbl107/network.txt");
    if (!input.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        exit(-1);
    }
    
    for (int i = 0; i < NUMBER_OF_VERTECES; ++i) {
        std::string line;
        std::getline(input, line);
        std::istringstream lineStream(line);
        for (int j = 0; j < NUMBER_OF_VERTECES; ++j) {
            std::string edgeWeightString;
            std::getline(lineStream, edgeWeightString, ',');
            if (j <= i) {
                // There is no edge when j == i, and the edge has been
                // considered when j < i.
                continue;
            }
            if (edgeWeightString != NO_EDGE_INDICATOR) {
                int weight = std::atoi(edgeWeightString.c_str());
                edgeList.insert({i, j, weight});
            }
        }
    }
    
    int graphTotalWeight = 0;
    for (auto i = edgeList.begin(); i != edgeList.end(); ++i) {        graphTotalWeight += i->weight;
    }
    
    UnionFindSet<NodeNo> unionFindSet;
    for (NodeNo i = 0; i < NUMBER_OF_VERTECES; ++i) {
        unionFindSet.insert(i);
    }
    std::set<Edge> minimumSpanningTree;
    while (minimumSpanningTree.size() != NUMBER_OF_VERTECES - 1) {
        Edge minimalEdge = *(edgeList.begin());
        edgeList.erase(edgeList.begin());
        if (unionFindSet.tryToUnionSetsByKeys(minimalEdge.start,
                                              minimalEdge.finish)) {
            minimumSpanningTree.insert(minimalEdge);
        }
    }
    
    int minimumSpanningTreeTotalWeight = 0;
    for (auto i = minimumSpanningTree.begin();
         i != minimumSpanningTree.end();
         ++i) {
        minimumSpanningTreeTotalWeight += i->weight;
    }
    
    std::cout << graphTotalWeight - minimumSpanningTreeTotalWeight << std::endl;
    
    return 0;
}