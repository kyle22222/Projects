#ifndef LIST_H
#define LIST_H

template <typename T>
class List {
  class Node {
  public:
    T data;     
    Node* next;
    Node(T d, Node* n): data(d), next(n) {}
  };

  public:
    List() : head(nullptr) {}
    ~List() {
      Node* currNode = head;
      Node* nextNode;

      while (currNode != nullptr) {
        nextNode = currNode->next;
        delete currNode->data;
        delete currNode;
        currNode = nextNode;
      }
    }
    List& operator+=(T data) {
      Node* newNode = new Node(data, nullptr);

      if (!head) {
        head = newNode;
      } else {
        Node* curr = head;
        while (curr->next) {
          curr = curr->next;
        }
        curr->next = newNode;
      }

      return *this;
    }
    void convertToArray(T* arr, int& size) const {
      Node* currNode = head;
      size = 0;

      while (currNode != nullptr) {
        arr[size++] = currNode->data;
        currNode = currNode->next;
      }
    }

  private:
    Node* head;
};

#endif
