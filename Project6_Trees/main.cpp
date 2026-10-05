#include <iostream>
#include "bst.h"
#include <fstream>
#include <cctype>
#include <vector>



class Pair {
public:
    char letter;
    mutable int count; // allow const Pair, but still be able to mutate count

    Pair(char c, int n = 0) : letter(c), count(n) {}

    bool operator<(const Pair& other) const {
        return letter < other.letter;
    }

    bool operator>(const Pair& other) const {
        return letter > other.letter;
    }

    bool operator==(const Pair& other) const {
        return letter == other.letter;
    }

    void increment() const {
        ++count;
    }
};

//pretty print the Pair
std::ostream& operator<<(std::ostream& os, const Pair& p) {
    os << "(" << p.letter << ", " << p.count << ")";
    return os;
}


BST<Pair> make_tree() {
    BST<Pair> tree;
    char ch;
    std::fstream fin ("around-the-world-in-80-days-3.txt", std::fstream::in);
    while (fin >> ch) {
        ch = tolower(ch);
        if (isalnum(ch)) {
            try {
                tree.find(Pair(ch)).increment(); //if the letter is already in the tree, increment the count
            }
            catch (const std::runtime_error& e) { //if the letter is not in the tree, add it to the tree
                tree.add(Pair(ch, 1));
            }
        }
    }
    return tree;
}

int main() 
{
    BST<Pair> tree = make_tree();
    std::vector<Pair> characters = tree.inorder();
    for (const auto& character : characters) {
        std::cout << character << std::endl;
    }

    int height = tree.height();
    int size = tree.size();
    std::cout << "Height: " << height << std::endl;
    std::cout << "Size: " << size << std::endl;
}