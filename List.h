#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:
  List(){
    list_size = 0;
  }

  List(const List& other) : list_size(other.size()), first(other.first), last(other.first){
    Node * temp = first.next;
    push_back(temp->datum);
    for (int i = 2; i < other.size() - 1; i++){
        temp = temp.next;
        push_back(temp->datum);
        //temp points to last node in list
    }
    //temp points to null 
    temp = nullptr;
    delete temp;
  };

  ~List(){
    clear();
  }


  List & operator=(const List &other) {
    if (this == &other){
      return *this;
    }
    //pop off all nodes (deletes them)
    clear();

    //nodes are dynamically allocated but everything else isn't
    //here we handle static member variables
    first = other.first;
    last = other.first;
    list_size = other.size;

    Node * temp = first.next;
    push_back(temp->datum);
    //now we copy over dynamic member variables
    for (int i = 2; i < other.size() - 1; i++){
      temp = temp.next;
      push_back(temp->datum);
      //temp points to last node in list

    }
    //temp points to null 
    temp = nullptr;
    delete temp;
  }


  //EFFECTS:  returns true if the list is empty
  bool empty() const;

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
  int size() const;

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front();

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back();

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum);

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum);

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front();

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back();

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear();

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };
      
      


  void Node_init(Node * node, Node * next_in, Node *prev_in, T datum_in){
    node->next = next_in;
    node->prev = prev_in;
    node->datum = datum_in;
  }

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other);

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
  int list_size; //size of list
public:
  ////////////////////////////////////////
  class Iterator {
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here

    // construct an Iterator at a specific position
    Iterator(Node *p);

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const;

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i);

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum);

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


template<typename T>
bool List<T>::empty() const {
  if (first == nullptr){
    return true;
  }
  return false;
}


//EFFECTS: returns the number of elements in this List
//HINT:    Traversing a list is really slow.  Instead, keep track of the size
//         with a private member variable.  That's how std::list does it.

template<typename T>
T & List<T>::front(){   
  assert(empty() == false);
  return first->datum;
}

template<typename T>
T & List<T>::back(){
  assert(empty() == false);
  return last->datum;
};

template<typename T>
void List<T>::push_front(const T &datum){
  //dynamically create a new node
  Node *newNode = new Node;
  //initialize the new node, its next node is the first node in the linked list
  newNode->datum = datum;
  newNode->prev = nullptr;
  newNode->next = first;
  //the first node in the linked list now has this new node as its previous node
  first->prev = newNode;
  //so now the first in the linked list is the new node we created 
  first = newNode;
  list_size += 1;
}

template<typename T>
void List<T>::push_back(const T &datum){
  Node *newNode = new Node;
  newNode->datum = datum;
  newNode->next = nullptr;
  if (empty()){
    first = last = newNode;
  }
  else{
    newNode->prev = last;
    last = last->next = newNode;
  }
  
  list_size += 1;
}


template<typename T>
void List<T>::pop_front(){
  assert(empty() == false);
  //temp points to second node in list
  Node * temp = first;
  first = first->next;
  first->prev = nullptr;
  delete temp;
  list_size -= 1; 
}

template<typename T>
void List<T>::pop_back(){
  assert(empty() == false);
  Node * temp = last;
  (last->prev)->next = nullptr;
  last = last->prev;
  delete temp;
  list_size -= 1;
}

template<typename T>
void List<T>::clear(){
  while (!empty()){
    pop_front();
  }
}

template<typename T>
int List<T>::size() const{
  return list_size;
 }

#endif // Do not remove this. Write all your code above this line.
