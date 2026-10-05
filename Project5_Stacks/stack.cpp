#include "stack.h"
#include <unordered_map>
#include <regex>


template <typename T>
Stack<T>::~Stack() { //destructor to free memory
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

template <typename T>
int Stack<T>::push(const T& value) {
    Node* new_node = new Node(value); //create a new node

    if (head == nullptr) { //if the stack is empty, make the new node the head
        head = new_node;
    }
    else {  //otherwise, make the new node point to the current head and then make it the new head
        new_node->next = head;
        head = new_node;
    }
    _size++;
    return _size;
}

template <typename T>
T Stack<T>::pop() {
    if (head == nullptr) { //if the stack is empty, raise an error
        throw std::out_of_range("IndexError: Stack is empty");
    }
    else {  //otherwise, remove the head node and make the next node the new head
        T popped_value = head->value; //store the value of the head node to return later
        Node* temp = head;
        head = head->next;
        delete temp; //free memory of the old head node
        _size--;
        return popped_value; //return the value of the removed node
    }
}

template <typename T>
T& Stack<T>::top() {
    if (head == nullptr) { //if the stack is empty, raise an error
        throw std::out_of_range("IndexError: Stack is empty");
    }
    else {  //otherwise, return a reference to the value of the head node
        return head->value;
    }
}

template <typename T>
int Stack<T>::size() const {
    return _size;
}

template <typename T>
void Stack<T>::clear() {
    while (head) { //while there are still nodes in the stack
        Node* temp = head;
        head = head->next;
        delete temp; //delete each node to free memory
    }
    _size = 0; //reset size to 0
}


bool higher_or_equal_precedence(char op1, char op2) {
    // Define operator precedence
    std::unordered_map<char, int> precedence = {
        {'+', 1},
        {'-', 1},
        {'*', 2},
        {'/', 2}
    };

    return precedence[op1] >= precedence[op2];
}

std::string in2post(std::string expr) {
    if (!expr.empty()) {
        expr = std::regex_replace(expr, std::regex("\\s+"), ""); //remove spaces from the input expression
    }
    Stack<char> operator_stack; //stack to hold operators
    std::string output; //string to hold the output postfix expression
    int parenthesis = 0; //flag to track if a closed parenthesis has been encountered

    for (long unsigned int i = 0; i < expr.length(); i++) {

        if (isalpha(expr[i])) { //if the character is a letter, the expression is invalid
            throw std::runtime_error("SyntaxError");
        }
        
        if (isdigit(expr[i])) {
            output += expr[i];
            while (i + 1 < expr.length() && isdigit(expr[i + 1])) {
                output += expr[++i];
            }
            output += " ";
            continue;
        }

        if (expr[i] == '(') {
            parenthesis++;
            operator_stack.push(expr[i]);
            continue;
        }

        if (expr[i] == ')') {
            parenthesis--;
            try {
                int j = operator_stack.pop();
                while (j != '(') {
                    output += j;
                    output += " ";
                    j = operator_stack.pop();
                }
            }
            catch (const std::out_of_range& e) {}
            continue;
        }

        try {
            while (higher_or_equal_precedence(operator_stack.top(), expr[i])) {
                char val = operator_stack.pop();
                output += val;
                output += " ";
            }
        }
        catch (const std::out_of_range& e) {}
        operator_stack.push(expr[i]);
    }

    while (operator_stack.size() > 0) {
        char val = operator_stack.pop();
        output += val;
        output += " ";
    }

    if (parenthesis != 0) { //if there were unmatched parentheses, the expression is invalid
        throw std::runtime_error("SyntaxError");
    }

    return output;
}



double eval_postfix(std::string expr) {
    if (expr.empty()) {
        throw std::runtime_error("SyntaxError");
    }

    Stack<double> number_stack; //stack to hold numbers for computation

    for (long unsigned int i = 0; i < expr.length(); i++) {

        if (expr[i] == ' ') {
            continue; //skip spaces in the expression
        }

        if (isdigit(expr[i]) || expr[i] == '.') {
            std::string value;
            value += expr[i];
            while (i + 1 < expr.length() && isdigit(expr[i + 1])) {
                value += expr[++i];
            }
            number_stack.push(std::stod(value));
            continue;
        }
        try{
            double a = number_stack.pop();
            double b = number_stack.pop();

            switch (expr[i]) {
            case '+':
                number_stack.push(b + a);
                break;
            case '-':
                number_stack.push(b - a);
                break;
            case '*':
                number_stack.push(b * a);
                break;
            case '/':
                if (a == 0) {
                    throw std::runtime_error("ZeroDivisionError");
                }
                number_stack.push(b / a);
                break;
            }
        }
        catch (const std::out_of_range& e) {
            throw std::runtime_error("SyntaxError");
        }
    }

    if (number_stack.size() != 1) { //if there are not exactly 1 number left on the stack, the expression was invalid
        throw std::runtime_error("SyntaxError");
    }
    return number_stack.pop(); //the final result should be the only number left on the stack
}