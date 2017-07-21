/* Copyright 2017 Lucas Zacchi de Medeiros*/
#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include "./linked_list.h"
#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
class LinkedStack {
 protected:
    structures::LinkedList<int> list{};
 public:
    LinkedStack() {}

    ~LinkedStack() {
        list.clear();
    }

    void clear() {
        list.clear();
    }  // limpa pilha

    void push(const T& data) {
        return list.push_front(data);
    }  // empilha

    T pop() {
        return list.pop_front();
    }  // desempilha

    T& top() const {
        return list.at(0);
    }  // dado no topo

    bool empty() const {
        return list.empty();
    }  // pilha vazia

    std::size_t size() const {
        return list.size();
    }  // tamanho da pilha

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
