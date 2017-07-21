/* Copyright [2017] <Lucas Zacchi de Medeiros>*/

//g++ tests_circular_list.cpp -lgtest -o tests; gtester tests

#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
class CircularList {
 public:
    CircularList() = default;

    ~CircularList() {
        clear();
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    } // limpar lista

    void push_back(const T& data) {
        // insert(data, size_);
        auto new_node = new Node{data};
        if (empty()) {
            head = new_node;
            head->next(new_node);
        } else {
            auto previous = head;

            for (auto i = 0u; i < size_ - 1; ++i) {
                previous = previous->next();
            }
            previous->next(new_node);
            new_node->next(head);
        }
        ++size_;
    } // inserir no fim

    void push_front(const T& data) {
        auto new_node = new Node{data};
        new_node->next(head);
        head = new_node;
        ++size_;
    } // inserir no início

    void insert(const T& data, std::size_t index) {
        if (index > size_) {
            throw std::out_of_range("Out of range (insert)");
        }

        if (empty() || index == 0) {
            push_front(data);
        }

        if (index == size_) {
            push_back(data);
        }
        auto previous = head;

        for (auto i = 0u; i < index - 1; ++i) {
            previous = previous->next();
        }

        auto new_node = new Node{data, previous->next()};
        previous->next(new_node);
        //new_node->next(head);
        ++size_;
    } // inserir na posição

    void insert_sorted(const T& data) {
        if (empty() || data <= head->data()) {
            push_front(data);
        } else {
            auto previous = head;
            auto current = previous->next();
            for (auto i = 0u; i < size_ - 1; ++i) {
                if (data <= current->data()) {
                    break;
                }
                previous = current;  // previous->next();
                current = previous->next();  // current->next();
            }
            auto new_node = new Node{data};
            previous->next(new_node);
            new_node->next(current);
            ++size_;
        }
    } // inserir em ordem


    T& at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Out of range (at)");
        }

        auto current = head;
        for (auto i = 0u; i < index; ++i) {
            current = current->next();
        }
        return current->data();
    } // acessar em um indice (com checagem de limites)

    const T& at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Out of range (at)");
        }

        auto current = head;
        for (auto i = 0u; i < index; ++i) {
            current = current->next();
        }
        return current->data();
    } // versão const do acesso ao indice


    T pop(std::size_t index) {
        if (empty()) {
            throw std::out_of_range("Out of range (pop)");
        }

        if (index >= size_) {
            throw std::out_of_range("Invalid index");
        }

        if (index == 0) {
            return pop_front();
        }

        auto current = head;

        for (auto i = 0u; i < index - 1; ++i) {
            current = current->next();
        }

        auto aux_node = current->next();
        auto temp = aux_node->data();
        current->next(aux_node->next());
        delete aux_node;

        --size_;

        return temp;

    } // retirar da posição

    T pop_back() {
        return pop(size_ - 1);
    } // retirar do fim

    T pop_front() {
        if (empty()) {
            throw std::out_of_range("Empty (pop_front)");
        }

        auto aux_node = head;
        head = head->next();

        auto aux_data = aux_node->data();
        delete aux_node;

        --size_;
        return aux_data;
    } // retirar do início

    void remove(const T& data) {
        if (find(data) == size_) {
        } else {
            pop(find(data));
        }
    } // remover dado específico

    bool empty() const {
        return size_ == 0;
    } // lista vazia

    bool contains(const T& data) const {
        return find(data) < size_;
    } // lista contém determinado dado?

    std::size_t find(const T& data) const {
        auto current = head;
        auto i = 0u;

        if (empty()) {
            throw std::out_of_range("Out of range (find)");
        }

        while (i < size_) {
            if (current->data() == data) {
                break;
            }
            ++i;
            current = current->next();
        }
        return i;
    } // posição de um item na lista

    std::size_t size() const {
        return size_;
    } // tamanho da lista

 private:
   class Node {  // Elemento
    public:
       explicit Node(const T& data):
           data_{data}
       {}

       Node(const T& data, Node* next):
           data_{data},
           next_{next}
       {}

       T& data() {  // getter: dado
           return data_;
       }

       const T& data() const {  // getter const: dado
           return data_;
       }

       Node* next() {  // getter: próximo
           return next_;
       }

       const Node* next() const {  // getter const: próximo
           return next_;
       }

       void next(Node* node) {  // setter: próximo
           next_ = node;
       }

     private:
       T data_;
       Node* next_{nullptr};
   };

   Node* end() {  // último nodo da lista
       auto it = head;
       for (auto i = 1u; i < size(); ++i) {
           it = it->next(head);
       }
       return it;
   }

   Node* head{nullptr};
   std::size_t size_{0u};
};

}  // namespace structures

#endif
