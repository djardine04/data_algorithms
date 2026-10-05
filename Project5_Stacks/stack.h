#ifndef STACK_H 
#define STACK_H

#include <iostream>
#include <stdexcept>
#include <string>

template <typename T>
class Stack {
private:
    struct Node {
        T value;
        Node* next;
        Node(const T& v) : value(v), next(nullptr) {}
    };

    Node* head;
    int _size;

public:
    Stack() : head(nullptr), _size(0) {}
    ~Stack();

    int push(const T& value); // push an item onto the stack, increases the size by 1, and returns the new size
    T pop(); // remove the top item from the stack and return it. Raise an IndexError if the stack is empty. Size decreases by 1.
    T& top(); // return a reference to the top item on the stack without removing it. Raise an IndexError if the stack is empty.
    const T& top() const;
    int size() const; // return the number of items currently in the stack
    void clear(); // remove all items from the stack, leaving it empty


};

bool higher_or_equal_precedence(char op1, char op2); // helper function to determine operator precedence
std::string in2post (std::string expr); // accepts the string parameter expr and returns an equivalent postfix expression as a string. If expr is not a avlid infix expression, raise a runtime_error with the description string set to "SyntaxError".
double eval_postfix (std::string expr); // takes a postfix string as input, evaluates it, and returns the result as a number. If the expression is not valid, raise a runtime_error with the description string set to "SyntaxError".

#endif