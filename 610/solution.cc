#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

typedef long double ld;

const ld P = 0.14;
const std::string chars = "#IVXLCDM";
struct cmpRomanDenom {
    bool operator()(const char& lhs, const char& rhs) const
    {
        return std::find(chars.begin(), chars.end(), lhs) < std::find(chars.begin(), chars.end(), rhs);
    };
};

// Trie node.
class Node {
    std::string graphviz(std::string id, bool is_root = false);

public:
    int value;
    ld probability;
    std::map<char, std::unique_ptr<Node>, cmpRomanDenom> children;

    Node(int value = -1);
    void insert(const char*, int value);
    void insert(const std::string&, int value);
    ld weighted_sum(ld probability);
    std::string graphviz();
};

Node::Node(int value)
    : value(value)
    , probability(0)
{
}

void Node::insert(const char* s, int value)
{
    Node* curr = this;
    while (*s) {
        if (curr->children.find(*s) == curr->children.end()) {
            curr->children[*s] = std::make_unique<Node>();
        }
        curr = curr->children[*s].get();
        s++;
    }
    curr->value = value;
}

void Node::insert(const std::string& s, int value)
{
    this->insert(s.c_str(), value);
}

ld Node::weighted_sum(ld probability)
{
    this->probability = probability;
    if (value >= 0) {
        return probability * value;
    }
    int k = children.size();
    ld sum = 0;
    ld denominator = 1 - (8 - k) * P;
    for (auto& [ch, child] : children) {
        sum += child->weighted_sum(probability * ((ch == '#') ? (1 - 7 * P) : P) / denominator);
    }
    return sum;
}

std::string Node::graphviz(std::string id, bool is_root)
{
    std::string result;
    std::string nonempty_id = is_root ? "__" : id;
    if (is_root) {
        result += "graph \"\" {\n";
        result += "  __[label=\"\"];\n";
    }
    for (auto& [ch, child] : children) {
        if (ch == '#') {
            std::string leaf_id = id + "_";
            result += " " + nonempty_id + " -- " + leaf_id + ";\n";
            result += " " + leaf_id + "[label=\"#" + std::to_string(child->value) + "\\n" + std::to_string(child->probability) + "\"];\n";
            continue;
        }
        std::string child_id = id + ch;
        result += "  " + nonempty_id + " -- " + child_id + ";\n";
        result += "  " + child_id + "[label=\"" + ch + "\\n" + std::to_string(child->probability) + "\"];\n";
        result += child->graphviz(child_id);
    }
    if (is_root) {
        result += "}\n";
    }
    return result;
}

std::string Node::graphviz()
{
    return graphviz("", true);
}

inline std::string to_roman(int n)
{
    assert(n >= 0 && n <= 999);
    std::string C[] = { "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" };
    std::string X[] = { "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" };
    std::string I[] = { "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };
    return C[(n % 1000) / 100] + X[(n % 100) / 10] + I[(n % 10)];
}

int main()
{
    std::unique_ptr<Node> root = std::make_unique<Node>();
    for (int n = 0; n <= 999; ++n) {
        root->insert(to_roman(n) + "#", n);
    }
    ld sum = 0;
    for (auto& [ch, child] : root->children) {
        sum += child->weighted_sum((ch == '#') ? (1 - 7 * P) : P);
    }
    ld expectation = (P * 1000 + sum) / (1 - P);
    // std::cout << root->graphviz() << std::endl;
    std::cout << std::fixed << std::setprecision(8) << expectation << std::endl;
    return 0;
}
