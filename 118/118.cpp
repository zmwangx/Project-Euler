//
//  main.cpp
//  Prbl118
//  Prioject Euler
//
//  Created by Zhiming Wang on 12/23/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Exhaust all possible divisions.
//  -------------------------------
//  Answer: 44680
//

#include <map>
#include <set>
#include <string>

#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    std::ifstream input("/Users/ZhimingWang/Documents/02Programming/Projects/"
                        "ProjectEuler/C++/Prbl118/prbl118.txt");
    if (!input.is_open()) {
        std::cerr << "Error opening data file!" << std::endl;
        exit(-1);
    }
    
    // Key data structure
    std::map<std::string, int> nPrimes;
    
    while (input.good()) {
        std::string line;
        std::getline(input, line);
        if (line.empty()) {
            break;
        }
        
        std::istringstream lineStream(line);
        lineStream.get(); // '{'
        
        int membersIntForm;
        lineStream >> membersIntForm;
        std::string membersStringForm = std::to_string(membersIntForm);
        
        lineStream.get(); // ','
        lineStream.get(); // ' '
        
        int correspondingNPrimes;
        lineStream >> correspondingNPrimes;
        
        nPrimes[membersStringForm] = correspondingNPrimes;
    }
    
    int enclosure[9 + 1];
    std::string members[6];
    
    // Key data structure
    std::map<std::string, int> divisions;
 
    enclosure[1] = 0;
    members[enclosure[1]] += '0' + 1;
 
    for (enclosure[2] = 0; enclosure[2] < 6; ++enclosure[2]) {
     members[enclosure[2]] += '0' + 2;
     
     for (enclosure[3] = 0; enclosure[3] < 6; ++enclosure[3]) {
      members[enclosure[3]] += '0' + 3;
      
      for (enclosure[4] = 0; enclosure[4] < 6; ++enclosure[4]) {
       members[enclosure[4]] += '0' + 4;
       
       for (enclosure[5] = 0; enclosure[5] < 6; ++enclosure[5]) {
        members[enclosure[5]] += '0' + 5;
        
        for (enclosure[6] = 0; enclosure[6] < 6; ++enclosure[6]) {
         members[enclosure[6]] += '0' + 6;
         
         for (enclosure[7] = 0; enclosure[7] < 6; ++enclosure[7]) {
          members[enclosure[7]] += '0' + 7;
          
          for (enclosure[8] = 0; enclosure[8] < 6; ++enclosure[8]) {
           members[enclosure[8]] += '0' + 8;
           
           for (enclosure[9] = 0; enclosure[9] < 6; ++enclosure[9]) {
            members[enclosure[9]] += '0' + 9;
            
               std::set<std::string> memberStrings;
               for (int i = 0; i < 6; ++i) {
                   if (!members[i].empty()) {
                       memberStrings.insert(members[i]);
                   }
               }
               std::string concatenation;
               for (auto i = memberStrings.begin();
                    i != memberStrings.end();
                    ++i) {
                   concatenation += *i + ' ';
               }
               if (divisions.find(concatenation) != divisions.end()) {
                   members[enclosure[9]].pop_back();
                   continue;
               }
               int product = 1;
               for (auto i = memberStrings.begin();
                    i != memberStrings.end();
                    ++i) {
                   product *= nPrimes[*i];
               }
               divisions[concatenation] = product;
               
               
            members[enclosure[9]].pop_back();
           }
           
           members[enclosure[8]].pop_back();
          }
          
          members[enclosure[7]].pop_back();
         }
         
         members[enclosure[6]].pop_back();
        }
        
        members[enclosure[5]].pop_back();
       }
       
       members[enclosure[4]].pop_back();
      }
      
      members[enclosure[3]].pop_back();
     }
     
     members[enclosure[2]].pop_back();
    }
 
    members[enclosure[1]].pop_back();
    
    int nTotal = 0;
    for (auto i = divisions.begin(); i != divisions.end(); ++i) {
        nTotal += i->second;
    }
    std::cout << nTotal << std::endl;
    
    return 0;
}