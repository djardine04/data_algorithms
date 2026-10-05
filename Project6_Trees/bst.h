#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>

template <typename T>
class BST {
    private:
        struct Node {
            T value;
            Node* left;
            Node* right;
            Node(const T& v) : value(v), left(nullptr), right(nullptr) {} //defines pointers and data for BST
        };

        Node* root;
        int _size;  //the raw number of nodes in the tree, not the depth
        void destroy(Node* node); //helper function for destructor to free memory
        void inorder(const Node* node, std::vector<T>& result) const; //helper function for inorder traversal
        void preorder(const Node* node, std::vector<T>& result) const; //helper function for preorder traversal
        void postorder(const Node* node, std::vector<T>& result) const; //helper function for postorder traversal
        
        int height(Node* node) const; //helper function for height calculation

    public:
        BST() : root(nullptr), _size(0) {}  //member initializer list
        ~BST(); //destructor

        bool is_empty() const; //Returns True if there aren't any nodes in the tree
        int height() const; //returns the height of the tree
        int size() const; //returns the number of nodes in the tree

        BST<T>& add(const T& value); 
        BST<T>& remove(const T& value);
        const T& find(const T& value) const;

        std::vector<T> inorder() const;
        std::vector<T> preorder() const;
        std::vector<T> postorder() const;

        std::string print_tree() const;
};


template <typename T>
void BST<T>::destroy(Node* node) { //helper function for destructor to free memory
    if (node) {
        destroy(node->left); //recursively destroy left subtree
        destroy(node->right); //recursively destroy right subtree
        delete node; //delete the current node
    }
}

template <typename T>
BST<T>::~BST() { //destructor to free memory
    destroy(root); //call the destroy helper function on the root node
    root = nullptr; //set root to nullptr after destroying the tree
    _size = 0; //reset size to 0
}

template <typename T>
bool BST<T>::is_empty() const { //Returns True if there aren't any nodes in the tree
    return _size == 0; //if the size is 0, the tree is empty
}

template <typename T>
int BST<T>::size() const { //returns the number of nodes in the tree
    return _size; //return the size member variable
}

template <typename T>
int BST<T>::height() const { //returns the height of the tree
    return height(root); //call the height helper function on the root node
}

template <typename T>
int BST<T>::height(Node* node) const { //returns the height of the tree
    if (node == nullptr) { //if the tree is empty, the height is -1
        return -1;
    }
    else {
        int left_height = height(node->left); //get the height of the left subtree
        int right_height = height(node->right); //get the height of the right subtree
        return 1 + std::max(left_height, right_height); //return 1 + the maximum of the left and right heights
    }
}

template <typename T>
BST<T>& BST<T>::add(const T& value) {
    Node* new_node = new Node(value); //create new node
    
    if (!root) {
        root = new_node;
        _size++;
        return *this;
    }

    Node* currentNode = root;
    while (currentNode) {
        if (value < currentNode->value) {
            if (!currentNode->left) {
                currentNode->left = new_node;
                _size++;
                return *this;
            }
            currentNode = currentNode->left;
        }

        else if (value > currentNode->value) {
            if (!currentNode->right) {
                currentNode->right = new_node;
                _size++;
                return *this;
            }
            currentNode = currentNode->right;
        }

        else { //if the value is already in the tree
            delete new_node;
            return *this;
        }
    }
    return *this;
}

template <typename T>
BST<T>& BST<T>::remove(const T& value) {

    if (!root) {
        return *this;
    }

    Node* currentNode = root;
    Node* parentNode = nullptr;
    while (currentNode) {
        if (value == currentNode->value) {
            if (!currentNode->left && !currentNode->right) {
                
                if (!parentNode) { //if there is no parent node, we are at the root
                    root = nullptr;
                    delete(currentNode);
                    _size--;
                    return *this;
                }

                else if (parentNode->left == currentNode) {
                    parentNode->left = nullptr;
                    delete(currentNode);
                    _size--;
                    return *this;
                }

                else { //(parentNode->right == currentNode)
                    parentNode->right = nullptr;
                    delete(currentNode);
                    _size--;
                    return *this;
                }
            }

            else if (!currentNode->right) {
                if (!parentNode) {
                    root = currentNode->left;
                    delete(currentNode);
                    _size--;
                    return *this;
                }

                else if (parentNode->left == currentNode) {
                    parentNode->left = currentNode->left;
                    delete(currentNode);
                    _size--;
                    return *this;
                }

                else { //parent->right == currentNode
                    parentNode->right = currentNode->left;
                    delete(currentNode);
                    _size--;
                    return *this;
                }
            }

            else if (!currentNode->left) {
                if (!parentNode) {
                    root = currentNode->right;
                    delete(currentNode);
                    _size--;
                    return *this;
                }

                else if (parentNode->left == currentNode) {
                    parentNode->left = currentNode->right;
                    delete(currentNode);
                    _size--;
                    return *this;
                }

                else { //parent->right == currentNode
                    parentNode->right = currentNode->right;
                    delete(currentNode);
                    _size--;
                    return *this;
                }
            }

            else {  //currentNode has two children
                Node* successorParent = currentNode;
                Node* successor = currentNode->right;

                while (successor->left) {
                    successorParent = successor;
                    successor = successor->left;
                }

                currentNode->value = successor->value;

                if (successorParent->left == successor) {
                    successorParent->left = successor->right;
                }
                else {
                    successorParent->right = successor->right;
                }

                delete(successor);
                _size--;
                return *this;

            }
        }

        else if (value > currentNode->value) {
            parentNode = currentNode;
            currentNode = currentNode->right;
        }

        else { //value < currentNode->value
            parentNode = currentNode;
            currentNode = currentNode->left;

        }
    }

    return *this;
}

template <typename T>
const T& BST<T>::find(const T& value) const{

    if (!root) {
        throw std::runtime_error("Value not found in tree; empty tree");
    }

    const Node* currentNode = root;

    while (currentNode) {
        
        if (currentNode->value == value) {
            return currentNode->value;
        }

        else if (value > currentNode->value) {
            currentNode = currentNode->right;
        }

        else { //value < currentNode->value
            currentNode = currentNode->left;
        }
    }
    
    throw std::runtime_error("Value not found in tree");
}

template <typename T>
std::vector<T> BST<T>::inorder() const {
    std::vector<T> result;
    inorder(root, result);
    return result;
}

template <typename T>
void BST<T>::inorder(const Node* node, std::vector<T>& result) const {
    if (!node) {
        return;
    }

    inorder(node->left, result);
    result.push_back(node->value);
    inorder(node->right, result);
}

template <typename T>
std::vector<T> BST<T>::preorder() const {
    std::vector<T> result;
    preorder(root, result);
    return result;
}

template <typename T>
void BST<T>::preorder(const Node* node, std::vector<T>& result) const {
    if (!node) {
        return;
    }

    result.push_back(node->value);
    preorder(node->left, result);
    preorder(node->right, result);
}

template <typename T>
std::vector<T> BST<T>::postorder() const {
    std::vector<T> result;
    postorder(root, result);
    return result;
}

template <typename T>
void BST<T>::postorder(const Node* node, std::vector<T>& result) const {
    if (!node) {
        return;
    }

    postorder(node->left, result);
    postorder(node->right, result);
    result.push_back(node->value);
}

template <typename T>
std::string BST<T>::print_tree() const {
    std::string output;
    std::vector<T> values = inorder(); //get the values in sorted order using inorder traversal

    for (const T& value : values) {
        output += std::to_string(value) + "\n"; //append each value to the output string with a newline
    }

    return output;
}