/* "Copyright 2017 Lucas Zacchi de Medeiros" */
#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <cstdint>
#include <stdexcept>
#include "linked_list.h"


namespace structures {


template<typename T>
class LinkedQueue {
 protected:
   structures::LinkedList<int> list{};

 public:
    LinkedQueue() {}

    ~LinkedQueue(){
        list.clear();
    }

    void clear() {
        list.clear();
    }  // limpar

    void enqueue(const T& data) {
        list.push_back(data);
    }  // enfilerar

    T dequeue() {
        list.pop_front();
    }  // desenfilerar

    T& front() const {
        list.at(0);
    }  // primeiro dado

    T& back() const {
        list.at(size()-1);
    }  // último dado

    bool empty() const {
        return list.empty();
    }  // fila vazia

    std::size_t size() const {
        return list.size();
    }  // tamanho

 private:
    class Node {
     public:
        explicit Node(const T& data);
        Node(const T& data, Node* next);

        T& data();  // getter: info
        const T& data() const;  // getter-constante: info

        Node* next();  // getter: próximo
        const Node* next() const;  // getter-constante: próximo

        void next(Node* next);  // setter: próximo
     private:
        T data_;
        Node* next_;
    };

    Node* top_;  // nodo-topo
    std::size_t size_;  // tamanho
};

}  // namespace structures

#endif
