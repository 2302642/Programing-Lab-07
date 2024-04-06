/*!*******************************************************************************************************************************************************************************************************************************
\file       listint.cpp
\par        Author:          Najih
\par        Email:           n.hajasheikallaudin
\par        Course:          RSE1202
\par        Section:         RSE
\par        Tutorial:        Lab 7
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

#ifndef LISTINT_HPP
#define LISTINT_HPP

#include <iostream>
#include <iomanip>          // for std::setw
#include <cstddef>          // for std::size_t
#include <algorithm>        // for std::swap
#include <initializer_list>
#include <stdexcept>       // include for std::out_of_range

namespace hlp2{
    class ListInt {
        public:
            // Type aliases
            using size_type = std::size_t;
            using value_type = int;
            using reference = value_type&;
            using const_reference = const value_type&;
            using pointer = value_type*;
            using const_pointer = const value_type*;
            
            ListInt();                                                                      // Default constructor
            ListInt(const ListInt& val);                                                    // Copy constructor
            ListInt(std::initializer_list<value_type> list);                                // Single-argument constructor with initializer list
            ~ListInt();                                                                     // Destructor

            // Copy assignment operators
            ListInt& operator=(const ListInt& val);                                         // copy assignment with another ListInt object using copy-and-swap idiom
            ListInt& operator=(std::initializer_list<value_type> list);                     // copy assignment with std::initializer_list<value_type> using copy-and-swap idiom

            // Concatenation operators
            ListInt& operator+=(const ListInt& val);                                        // concatenates with nodes of another ListInt container
            ListInt& operator+=(std::initializer_list<value_type> list);                    // concatenates with std::initializer_list<value_type>

            // Element access operators
            reference operator[](size_type index);                                          // returning the size_type(int) data of node at position index in linked list
            const_reference operator[](size_type index) const;                              // returning the size_type(int) data of node at position index in linked list (const version)

            // Modifiers
            void push_front(value_type value);                                              // adding a new node with the specified value to the front of the linked list
            void push_back(value_type value);                                               // adding a new node with the specified value to the back of the linked list
            value_type pop_front();                                                         // remove and return the value of the node at the front of the linked list
            void clear();                                                                   // remove and return the value of the node at the front of the linked list
            void swap(ListInt& val);                                                        // swaping all the contents ofthis ListInt container with another ListInt container

            // Capacity
            size_type size() const;                                                         // to check the number of nodes in the linked list
            bool empty() const;                                                             // to check if the linked list is empty

            static size_type object_count();                                                // static member function
            friend std::ostream& operator<<(std::ostream& os, const ListInt& val);          // overload operator<< for ListInt

        private:
            // Node structure
            struct Node {
                value_type data;                                                            // Data member to store the value of each node
                Node* next;                                                                 // Pointer to the next node in the list
            };

            // Data members
            Node *head {nullptr};                                                           // Pointer to the first node of the list
            Node *tail {nullptr};                                                           // Pointer to the last node of the list
            size_type counter {0};                                                          // Number of nodes in the list
            Node* new_node(value_type data) const;                                          // Helper function to create a new node with the given data
            static size_type object_counter;                                                // Static member to count the number of objects created from the class

    };
    // three overloads of operator
    ListInt operator+(const ListInt& lhs, const ListInt& rhs);                              // adding two ListInt objects
    ListInt operator+(const ListInt& lhs, std::initializer_list<ListInt::value_type> list); // adding ListInt and std::initializer_list<ListInt::value_tye>
    ListInt operator+(std::initializer_list<ListInt::value_type> list, const ListInt& rhs); // adding std::initializer_list<ListInt::value_tye> and ListInt
}
#endif // LISTINT_HPP
