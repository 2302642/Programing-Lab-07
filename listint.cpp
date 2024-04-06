/*!*******************************************************************************************************************************************************************************************************************************
\file       listint.cpp
\par        Author:          Najih
\par        Email:           n.hajasheikallaudin
\par        Course:          RSE1202
\par        Section:         RSE
\par        Tutorial:        Lab 6
\par        File created on: 08/03/2024
\brief      Singly Linked List Implementation using class

\par        File information:
            This file contains 
            3 constructurs & 1 destructor function 
            2 copy assignment, 2 concatenation & 2 element accessor operators
            5 modifer functions
            2 capacity & 2 object counter status functions
            3 overloaded "+" operator functions
            to be called by main inlistint-driver.
*********************************************************************************************************************************************************************************************************************************/
#include "listint.hpp"

namespace hlp2 {
//################################################################################################################################################################################################################################
//================================================================================================================================================================================================================================
//|                                                                                CONSTRUCTORS SECTION                                                                                                                          |
//================================================================================================================================================================================================================================
    ListInt::ListInt() : head(nullptr), tail(nullptr), counter(0) { ++object_counter; }                                 // default constructor
    ListInt::ListInt(const ListInt& val) : head(nullptr), tail(nullptr), counter(0) {                                   // copy constructor
        Node* current = val.head;
        while (current != nullptr) {
            push_back(current->data);                                                                                   // copying each element from val
            current = current->next;
        }
        ++object_counter;                                                                                               // incrementing the object counter
    }
    ListInt::ListInt(std::initializer_list<value_type> list) : head(nullptr), tail(nullptr), counter(0) {               // single-argument constructor with initializer list
        for (const auto& value : list) { push_back(value); }                                                            // adding each value from the initializer list to the list
        ++object_counter;                                                                                               // incrementing the object counter
    }
    ListInt::~ListInt() { clear();   --object_counter; }                                                                // destructor to call clear function to deallocate memory and decrementing object counter
    ListInt::Node* ListInt::new_node(value_type data) const { return new Node{data, nullptr}; }                         // creating a new node with data taken as the head of the new node
//================================================================================================================================================================================================================================
//|                                                                               COPY ASSIGNMENT OPERATORS                                                                                                                      |
//================================================================================================================================================================================================================================
    ListInt& ListInt::operator=(const ListInt& val) {                                                                   // copy assignment with another ListInt object using copy-and-swap idiom
        if (this != &val) {
            clear();                                                                                                    // clearing the current list
            Node* current = val.head;
            while (current != nullptr) {
                push_back(current->data);                                                                               // copying each element from val
                current = current->next;
            }
        }
        return *this;                                                                                                   // returning a reference to the modified list
    }
    ListInt& ListInt::operator=(std::initializer_list<value_type> list) {                                               // copy assignment with std::initializer_list<value_type> using copy-and-swap idiom
        clear();                                                                                                        // clearing the current list
        for (const auto& value : list) {
            push_back(value);                                                                                           // adding each value from the initializer list to the list
        }
        return *this;                                                                                                   // returning a reference to the modified list
    }
//================================================================================================================================================================================================================================
//|                                                                               CONCATENATION OPERATORS                                                                                                                        |
//================================================================================================================================================================================================================================
    ListInt& ListInt::operator+=(const ListInt& val) {                                                                  // concatenates with nodes of another ListInt container
        Node* current = val.head;                                                                                       // starting from the head of the list
        while (current != nullptr) {
            push_back(current->data);                                                                                   // appending each element from the initializer list to the end of this list 
            current = current->next;                                                                                    // moving to the next node in the list
        }
        return *this;
    }
    ListInt& ListInt::operator+=(std::initializer_list<value_type> list) {                                              // concatenates with std::initializer_list<value_type>
        for (const auto& value : list) { push_back(value); }                                                            // appending each element from the initializer list to the end of this list 
        return *this;
    }
//================================================================================================================================================================================================================================
//|                                                                               ELEMENT ACCESSOR OPERATORS                                                                                                                     |
//================================================================================================================================================================================================================================
    ListInt::value_type& ListInt::operator[](size_type index) {                                                         // returning the size_type(int) data of node at position index in linked list
        if (index >= counter) { throw std::out_of_range("Index out of range"); }                                        // checking if the index is out of bounds
        Node* current = head;
        for (size_type j = 0; j < index; ++j) {
            current = current->next;                                                                                    // moving to the next node in the list till the specified noad is found
        }
        return current->data;
    } 
    ListInt::const_reference ListInt::operator[](size_type index) const { return const_cast<ListInt&>(*this)[index]; }  // returning the size_type(int) data of node at position index in linked list (const version)
//================================================================================================================================================================================================================================
//|                                                                                   MODIFIER FUNCTIONS                                                                                                                         |
//================================================================================================================================================================================================================================
    void ListInt::push_front(value_type value) {                                                                        // adding a new node with the specified value to the front of the linked list
        Node* new_node = new Node{value, head};                                                                         // creating a new node with the given value
        if (empty()) { tail = new_node; }
        head = new_node;
        ++counter;                                                                                                      // incrementing the counter to show the addition of a new node
    }
    void ListInt::push_back(value_type value) {                                                                         // adding a new node with the specified value to the back of the linked list
        Node* new_node = new Node{value, nullptr};                                                                      // creating a new node with the given value  
        if (empty()) { head = new_node; } 
        else { tail->next = new_node; }                                                                                 // else add the new node to the back of the list
        tail = new_node;
        ++counter;
    }
    ListInt::value_type ListInt::pop_front() {                                                                          // remove and return the value of the node at the front of the linked list
        if (empty()) { return 0; }                                                                                      // if the list is empty, return 0 
        value_type value = head->data;                                                                                  // storing the value of the node at the front of the list
        Node* old_head = head;                                                                                          // Storing the pointer to the current head node
        head = head->next;                                                                                              // moving the head pointer to the next node
        delete old_head;                                                                                                // deleting the old head node to free memory
        --counter;                                                                                                      // decrementing the counter to show the removal of a node
        return value;                                                                                                   // returning the value of the removed node
    }
    void ListInt::clear() {                                                                                             // remove and return the value of the node at the front of the linked list
        while (head != nullptr) {                                                                                       // looping through the linked list and delete each node
            Node* temp = head;                                                                                          // storing a pointer to the current head node
            head = head->next;;                                                                                         // moving the head pointer to the next node
            delete temp;                                                                                                // deleting the current node to free memory
        }
        tail = nullptr;                                                                                                 // seting the tail to nullptr to indicate an empty lis
        counter = 0;                                                                                                    // reseting the counter to zero
    }
    void ListInt::swap(ListInt& val) {                                                                                  // swaping all the contents ofthis ListInt container with another ListInt container
        std::swap(head, val.head);                                                                                      // Swaping the head with another head in the other ListInt container
        std::swap(tail, val.tail);                                                                                      // Swaping the tail with another tail in the other ListInt container
        std::swap(counter, val.counter);                                                                                // Swaping the counter with another counter in the other ListInt container
    }
//================================================================================================================================================================================================================================
//|                                                                       CAPACITY AND OBJECT COUNTER STATUS FUNCTIONS                                                                                                           |
//================================================================================================================================================================================================================================
    ListInt::size_type ListInt::size() const { return counter; }                                                        // to check the number of nodes in the linked list
    bool ListInt::empty() const { return counter == 0; }                                                                // to check if the linked list is empty
//****************************************************************************************************************************************************************************************************************************
    ListInt::size_type ListInt::object_counter = 0;                                                                     // initializing the static member object_counter to 0
    ListInt::size_type ListInt::object_count() { return object_counter; }                                               // returning the current count of ListInt objects
//================================================================================================================================================================================================================================
//|                                                                 OVERLOADED OPERATOR SECTION (overloading "+" operator)                                                                                                       |
//================================================================================================================================================================================================================================
    ListInt operator+(const ListInt& lhs, const ListInt& rhs) {                                                         // adding two ListInt objects
        ListInt result = lhs;
        return result += rhs;
    }
    ListInt operator+(const ListInt& lhs, std::initializer_list<ListInt::value_type> list) {                            // adding ListInt and std::initializer_list<ListInt::value_tye>
        ListInt result = lhs;
        return result += list;
    }
    ListInt operator+(std::initializer_list<ListInt::value_type> list, const ListInt& rhs) {                            // adding std::initializer_list<ListInt::value_tye> and ListInt
        ListInt result = list;
        return result += rhs;
    }
//================================================================================================================================================================================================================================
//|                                                                                   GIVEN CODE SECTION                                                                                                                         |
//================================================================================================================================================================================================================================
    std::ostream& operator<<(std::ostream& os, const ListInt& rhs) {
        ListInt::Node* current = rhs.head;
        while (current != nullptr) {                                                                                    // Until we reach the end of the list
            os << std::setw(4) << current->data;                                                                        // print the data in this node
            current = current->next;                                                                                    // move to the next node
        }
        os << std::endl;                                                                                                // extra newline for readability
        return os;
    }
//################################################################################################################################################################################################################################
}  // End of namespace hlp2
