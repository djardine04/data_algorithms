#ifndef SLIST_H
#define SLIST_H

#include <stdexcept>
#include <iostream>

template <typename T>
class SList {
private:
    struct Node {
        T value;
        Node* next;
        Node(const T& v) : value(v), next(nullptr) {}
    };

    Node* head;
    int _size;

public:
    SList() : head(nullptr), _size(0) {}
    ~SList();

    void insert(const T& value);
    bool remove(const T& value);
    bool remove_all(const T& value);
    int find(const T& value) const;
    T& at(int index);
    const T& at(int index) const;

    int size() const;

    // Indexing
    T& operator[](int index);
    const T& operator[](int index) const;

    // Iterator support (for range-based for)
    class Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* node) : current(node) {}
        T& operator*() { return current->value; }
        Iterator& operator++() {
            current = current->next;
            return *this;
        }
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }

    class ConstIterator {
    private:
        const Node* current;
    public:
        ConstIterator(const Node* node) : current(node) {}

        const T& operator*() const { return current->value; }

        ConstIterator& operator++() {
            current = current->next;
            return *this;
        }

        bool operator!=(const ConstIterator& other) const {
            return current != other.current;
        }
    };

    ConstIterator begin() const { return ConstIterator(head); }
    ConstIterator end()   const { return ConstIterator(nullptr); }

    friend std::ostream& operator<<(std::ostream& os, const SList<T>& list) {
        Node* cur = list.head;
        while (cur) {
            os << cur->value << "\n";
            cur = cur->next;
        }
        return os;
    }
};

template <typename T>
SList<T>::~SList() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

template <typename T>
void SList<T>::insert(const T& value) {
    Node* new_node = new Node(value);   //create a new node with the value passed into the function
    
    if (!head || new_node->value < head->value) {   //if there is no head, or if the value of the new node is less than the value of the head
        new_node->next = head;                      //assign the next pointer in new_node to head to place the head in front of new_node
        head = new_node;                            //make new_node the head
    }
    else {
        Node* current_node = head;            //create a current_node pointer to keep track of where we are in the list, starting at the head value of the list    
        while(current_node->next && current_node->next->value <= new_node->value) {   //have it iterate through the list until either at the end of the list or find a value that is greater than new_node (this doesn't skip anything because we already compare the head value above)
            current_node = current_node->next;              //increment current_node
        }

        new_node->next = current_node->next;    //the current node's next becomes new_node next because the next node is greater than new_node (or we are at the tail)
        current_node->next = new_node;          //and the current node's next becomes the new_node, inserting it into the list

    }
    _size++;  //iterate the size
}

template <typename T>
int SList<T>::find(const T& value) const {
    Node* i = head;    //create an i pointer to keep track of where we are in the list, starting at the head value of the list
    int index = 0;     //create an index variable to keep track of the index of i
    
    while(i != nullptr) {    //while i is not at the end of the list
        if(i->value == value) {   //if the value of i is equal to the value we are looking for
            return index;          //return index (the index of the found value)
        }
        i = i->next;            //increment i
        index++;                //increment index
    }
     return -1;              //if we are at the end of the list and haven't found the value, return -1 (not found)
}

template <typename T>
bool SList<T>::remove(const T& value) {
    if(!head) {   //if there is no head, return false because there is nothing to remove
        return false;
    }

    else if(value == head->value) {     //if the value at the head is the value we are looking for
        Node* temp = head;              //create a temp pointer to the head so we can delete it after we change the head pointer
        head = head->next;              //make the node after head the new head, which removes the current head
        delete temp;                    //delete the old head node to free memory
        _size--;                        //decrement the size
        return true;                    //return true because we removed something
    }

    else {
        Node* current_node = head;            //create a current_node pointer to keep track of where we are in the list, starting at the head value of the list
        while(current_node->next != nullptr && current_node->next->value != value) {   //have it iterate through the list until either at the end of the list or find a node equal to the value we're looking for (this doesn't skip anything because we already compare the head value above)
            current_node = current_node->next;
        }

        if(current_node->next == nullptr) {     //if we are at the end
            return false;                       //this means we didn't find any values equal to the one we were looking for, so return false
        }
        else {                                  //if not at the end
            Node* temp = current_node->next;    //create a temp pointer to the node we want to remove so we can delete it after we change the pointers
            current_node->next = temp->next;    //change the pointer to skip the node with the value matching 'value' (temp is the node with the value matching 'value')
            delete temp;                        //delete the node we removed to free memory
            _size--;                            //decrement the size
            return true;                        //return true because we removed something

        }
    }
}

template <typename T>
bool SList<T>::remove_all(const T& value) {
    if(!head) {   //if there is no head, return false because there is nothing to remove
        return false;
    }
    else {
        int count = 0;    //create a count variable to keep track of how many nodes we remove
        
        while(head && value == head->value) {      //if the value at the head is the value we are looking for
            Node* temp = head;          //create a temp pointer to the head so we can delete it after we change the head pointer
            head = head->next;          //make the node after head the new head, which removes the current head
            delete temp;                //delete the old head node to free memory
            count++;                    //increment count
        }
        
        Node* current_node = head;            //create a current_node pointer to keep track of where we are in the list, starting at the head value of the list
        while(current_node && current_node->next != nullptr) {        //have it iterate through the list until either at the end of the list or the list is emtpy
            
            if(value == current_node->next->value) {    //if the value after current_node is equal to 'value'
                Node* temp = current_node->next;        //create a temp pointer to the node we want to remove so we can delete it after we change the pointers
                current_node->next = temp->next;        //change the pointer to skip the node with the value matching 'value'
                delete temp;                            //delete the node we removed to free memory
                count++;                                //increment count

            }
            else{
                current_node = current_node->next;      //move forward in the list
            }
        }

        if(count == 0) {    //if we are at the end and haven't removed anything return false
            return false;                   
        }
        else{                   //anything else means we removed something, so return true
            _size -= count;     //decrement the size by the number of nodes we removed
            return true; 
        }
    }
}

template <typename T>
int SList<T>::size() const {
    return _size;
}

template <typename T>
T& SList<T>::at(int index) {
    if (index < 0 || index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    
    Node* i = head;     //create i to iterate through the list                         
    for(int j = 0; j < index; j++) {   //iterate through the list until we reach the index we are looking for
        i = i->next;    //increment i
    }
    return i->value;  //return the value of i (the index)
}

template <typename T>
const T& SList<T>::at(int index) const {
       if (index < 0 || index >= _size) {
           throw std::out_of_range("Index out of range");
       }
    
    const Node* i = head;     //create i to iterate through the list                         
    for(int j = 0; j < index; j++) {   //iterate through the list until we reach the index we are looking for
        i = i->next;    //increment i
    }
    return i->value;  //return the value of i (the index)
}

template <typename T>
T& SList<T>::operator[](int index) {
    return at(index);   //use the at function to do the work of indexing, which will also handle out of range errors
}

template <typename T>
const T& SList<T>::operator[](int index) const {
    return at(index);   //use the at function to do the work of indexing, which will also handle out of range errors
}

#endif