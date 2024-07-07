#include <iostream>
#include "RegList.h"
using namespace std;

RegList::RegList() : head(nullptr), tail(nullptr) { }

RegList::RegList(RegList& otherList, Student* stu) : head(nullptr), tail(nullptr) {
    Node* current = otherList.head;
    while (current != nullptr) {
        if (current->data->getStudent() == stu) {
            add(current->data);
        }
        current = current->next;
    }
}

RegList::~RegList() {
    Node* currNode = head;
    Node* nextNode;
    while (currNode != nullptr) {
        nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    }
}

void RegList::add(Registration* r) {
    Node* newNode = new Node{r, nullptr};
    
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        return;
    }
    
    Node* current = head;
    Node* previous = nullptr;
    
    while (current != nullptr && current->data->lessThan(*r)) {
        previous = current;
        current = current->next;
    }
    
    newNode->next = current;
    
    if (previous == nullptr) {
        head = newNode;
    } else {
        previous->next = newNode;
    }

    if (current == nullptr) {
        tail = newNode;
    }
}

void RegList::cleanData() {
    Node* currNode = head;
    while (currNode != nullptr) {
        delete currNode->data;
        currNode = currNode->next;
    }
    
    head = nullptr;
    tail = nullptr;
}

void RegList::print() const {
    Node* currNode = head;
    while (currNode != nullptr) {
        currNode->data->print();
        currNode = currNode->next;
    }

    if (head != nullptr) {
        cout << "\nHEAD: ";
        head->data->print();
    }
    if (tail != nullptr) {
        cout << "TAIL: ";
        tail->data->print();
    }
}