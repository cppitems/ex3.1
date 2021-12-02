#pragma once
#include <cstddef>
#include <iostream>
#include <iterator>
#include <list>
#include <utility>

template <class T, std::enable_if_t<std::is_default_constructible<T>::value,
                                    bool> = true>
class List { 
public:
  using size_type = std::size_t;
  using value_type = T;

private:
  struct Node { 
    Node *prev = this;
    Node *next = this;
    T value;
  };

  // data members
  Node sentinel;
  Node *root = &sentinel;
  size_type size = 0;

  // helper functions
  void swap(List &&other) {
    std::swap(root, other.root);
    std::swap(size, other.size);
  }

  static void erase(Node *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    // downcast required when deleting
    delete node;
  }
  void append(const List &other) {
    for (const auto &item : other) {
      push_back(item);
    }
  }
  void clear() {
    auto node = root->next;
    while (node != root) {
      const auto next = node->next;
      erase(node);
      node = next;
    }
  }

public:
  void push_back(const value_type &value) {
    const auto new_node = new Node{root->prev, root, value};
    root->prev->next = new_node;
    root->prev = new_node;
    ++size;
  }

  void push_front(const value_type &value) {
    const auto new_node = new Node{root, root->next, value};
    root->next->prev = new_node;
    root->next = new_node;
    ++size;
  }

  List() = default; // default construct 'empty' list with sentinel

  List(List &&other) { // move ctor
    swap(*this, other);
  }

  List &operator=(List &&other) { // move assign
    swap(*this, other);
    return *this;
  }

  List(const List &other) { // copy ctor
    append(other);
  }

  List &operator=(const List &other) { // copy assign
    clear();
    append();
    return *this;
  }

  ~List() { // dtor
    clear();
  }

  // ------------ SOLUTION START
  

  
  // ------------ SOLUTION END
};
