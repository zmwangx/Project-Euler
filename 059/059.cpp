//
//  main.cpp
//  Prbl059
//  Project Euler
//
//  Created by Zhiming Wang on 12/09/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//  
//  Try all possible passwords and compare results to an English lexicon.
//  ---------------------------------------------------------------------
//  Answer:
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <string>
#include <cctype>

typedef std::set<std::string> Lexicon;

const std::string LEXICON_PATH =
"/Users/ZhimingWang/Dropbox/02ProgrammingProjects/ProjectEuler/C++/Prbl059/"
"englishLexicon.txt";

const double MINIMUM_CHAR_SATISFATORY_RATE = 1.00;
const double MINIMUM_WORD_SATISFATORY_RATE = 0.90;

static void createLexicon(Lexicon& lexicon);
static inline bool isInLexicon(const std::string& word,
                               const Lexicon& lexicon);
static std::string cipher(const std::string& text,
                          const std::string& password);
static bool mayBeEnglishText(const std::string& text, const Lexicon& lexicon);
static std::string readWord(std::istream& input);

int main() {
    Lexicon lexicon;
    createLexicon(lexicon);
    
    std::ifstream input("/Users/ZhimingWang/Dropbox/02ProgrammingProjects/"
                        "ProjectEuler/C++/Prbl059/cipher1.txt");
    if (!input.is_open()) {
        std::cerr << "Error opening cipher1.txt!" << std::endl;
        exit(-1);
    }
    std::string encryptedText;
    while (input.good()) {
        std::string asciiCode;
        std::getline(input, asciiCode, ',');
        if (input.fail()) {
            break;
        }
        if (asciiCode.empty()) {
            continue;
        }
        char character = static_cast<char>(std::atoi(asciiCode.c_str()));
        encryptedText += character;
    }
    
    for (char passChar1 = 'a'; passChar1 <= 'z'; ++passChar1) {
        for (char passChar2 = 'a'; passChar2 <= 'z'; ++passChar2) {
            for (char passChar3 = 'a'; passChar3 <= 'z'; ++passChar3) {
                std::string password;
                password += passChar1;
                password += passChar2;
                password += passChar3;
                
                std::string decryptedText = cipher(encryptedText, password);
                
                if (mayBeEnglishText(decryptedText, lexicon)) {
                    std::cout << "password: " << password << std::endl;
                    std::cout << decryptedText << std::endl;
                    int asciiValueSum = 0;
                    for (std::string::const_iterator i = decryptedText.begin();
                         i != decryptedText.end();
                         ++i) {
                        asciiValueSum += static_cast<int>(*i);
                    }
                    std::cout << "sum of ASCII values: "
                              << asciiValueSum << std::endl;
                    std::cout << std::endl;
                }
            }
        }
    }
    
    return 0;
}

static void createLexicon(Lexicon& lexicon) {
    std::ifstream input(LEXICON_PATH);
    if (!input.is_open()) {
        std::cerr << "Error opening lexicon!" << std::endl;
        exit(-1);
    }
    while (input.good()) {
        std::string word;
        std::getline(input, word);
        std::string legalWord;
        for (std::string::iterator i = word.begin(); i != word.end(); ++i) {
            if (std::isalpha(*i)) {
                legalWord += std::tolower(*i);
            }
        }
        if (!legalWord.empty()) {
            lexicon.insert(legalWord);
        }
    }
}

static inline bool isInLexicon(const std::string& word,
                               const Lexicon& lexicon) {
    return (lexicon.find(word) != lexicon.end());
}

static std::string cipher(const std::string& text,
                          const std::string& password) {
    std::string crypted;
    std::string::size_type passwordLength = password.length();
    std::string::size_type passwordPos = 0;
    for (std::string::const_iterator textIt = text.begin();
         textIt != text.end();
         ++textIt) {
        crypted += (*textIt) xor password[passwordPos];
        ++passwordPos;
        passwordPos %= passwordLength;
    }
    return crypted;
}

static bool mayBeEnglishText(const std::string& text, const Lexicon& lexicon) {
    std::istringstream textStream(text);
    
    // Examine characters.
    int charCounter = 0;
    int legalCharCounter = 0;
    while (textStream.good()) {
        char character;
        textStream.get(character);
        if (textStream.fail()) {
            break;
        }
        ++charCounter;
        if (std::isprint(character) || std::isspace(character)) {
            ++legalCharCounter;
        }
    }
    if (static_cast<double>(legalCharCounter) / charCounter < MINIMUM_CHAR_SATISFATORY_RATE) {
        return false;
    }
    
    // Examine words.
    textStream.clear();
    textStream.seekg(0);
    int wordCounter = 0;
    int englishWordCounter = 0;
    while (true) {
        std::string word = readWord(textStream);
        if (word.empty()) {
            break;
        }
        ++wordCounter;
        if (isInLexicon(word, lexicon)) {
            ++englishWordCounter;
        }
    }
    if (static_cast<double>(englishWordCounter) / wordCounter >=
        MINIMUM_WORD_SATISFATORY_RATE) {
        return true;
    } else {
        return false;
    }
}

static std::string readWord(std::istream& input) {
    std::string word;
    char character;
    while (input.good()) {
        input.get(character);
        if (input.fail() || std::isalpha(character)) {
            break;
        }
    }
    if (input.fail()) {
        return word;
    }
    word += std::tolower(character);
    while (input.good()) {
        input.get(character);
        if (input.fail() || !std::isalpha(character)) {
            break;
        }
        word += std::tolower(character);
    }
    return word;
}