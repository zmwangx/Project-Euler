//
//  main.cpp
//  Prbl102
//  Project Euler
//
//  Created by Zhiming Wang on 12/16/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Calculating signed area of OAB, OBC, and OCA. If they are of the same sign,
//  then O is contained in the interior of ABC; otherwise not.
//  ----------------------------------------------------------
//  Answer: 228
//

#include <iostream>
#include <fstream>
#include <sstream>

struct Point {
    int x;
    int y;
   
public:
    
    Point() {
        // Do nothing.
    }
    
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
    
    Point(const Point& other) {
        *this = other;
    }
    
    ~Point() {
        // Do nothing.
    }
    
    Point& operator=(const Point& other) {
        x = other.x;
        y = other.y;
        return *this;
    }
    
};

static const Point ORIGIN(0, 0);

static double
computeSignedAreaOfTriangle(Point point1, Point point2, Point point3);
static int getSign(double x);

int main() {
    std::ifstream input("/Users/ZhimingWang/Dropbox/02ProgrammingProjects/"
                        "ProjectEuler/C++/Prbl102/triangles.txt");
    if (!input.is_open()) {
        std::cerr << "Error opening triangles.txt!" << std::endl;
        exit(-1);
    }
    int nContains = 0;
    while (input.good()) {
        std::string line;
        std::getline(input, line);
        if (line.empty()) {
            break;
        }
        std::istringstream lineStream(line);
        std::string x1String;
        std::string y1String;
        std::string x2String;
        std::string y2String;
        std::string x3String;
        std::string y3String;
        std::getline(lineStream, x1String, ',');
        std::getline(lineStream, y1String, ',');
        std::getline(lineStream, x2String, ',');
        std::getline(lineStream, y2String, ',');
        std::getline(lineStream, x3String, ',');
        std::getline(lineStream, y3String, ',');
        int x1 = std::atoi(x1String.c_str());
        int y1 = std::atoi(y1String.c_str());
        int x2 = std::atoi(x2String.c_str());
        int y2 = std::atoi(y2String.c_str());
        int x3 = std::atoi(x3String.c_str());
        int y3 = std::atoi(y3String.c_str());
        Point point1(x1, y1);
        Point point2(x2, y2);
        Point point3(x3, y3);
        int sign1 = getSign(computeSignedAreaOfTriangle(ORIGIN,
                                                        point2, point3));
        int sign2 = getSign(computeSignedAreaOfTriangle(ORIGIN,
                                                        point3, point1));
        int sign3 = getSign(computeSignedAreaOfTriangle(ORIGIN,
                                                        point1, point2));
        if ((sign1 == 1 && sign2 == 1 && sign3 == 1) ||
            (sign1 == -1 && sign2 == -1 && sign3 == -1)) {
            ++nContains;
        }
    }
    std::cout << nContains << std::endl;
    return 0;
}

static double
computeSignedAreaOfTriangle(Point point1, Point point2, Point point3) {
    int x1 = point1.x;
    int y1 = point1.y;
    int x2 = point2.x;
    int y2 = point2.y;
    int x3 = point3.x;
    int y3 = point3.y;
    return x1 * y2 + x2 * y3 + x3 * y1 - x2 * y1 - x3 * y2 - x1 * y3;
}

static int getSign(double x) {
    if (x > 0) {
        return 1;
    } else if (x < 0) {
        return -1;
    } else {
        return 0;
    }
}