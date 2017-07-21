/* Copyright [2017] <Lucas Zacchi de Medeiros>*/
#ifndef STRUCTURES_DOUBLY_LINKED_LIST_H
#define STRUCTURES_DOUBLY_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>



namespace structures {

template<typename T>
class DoublyLinkedList {
public:
    DoublyLinkedList()
    {}

    ~DoublyLinkedList() {
        clear();
    }
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    void push_back(const T& data) {
        insert(data,size_);
        // auto new_node = new Node {data};
        //
        // if (new_node == nullptr) {
        //     throw std::out_of_range("The list is full");
        // }
        // if (empty()) {
        //     head = new_node;
        // } else {
        //     auto previous = head;
        //
        //     for (auto i = 0u; i < size_ - 1; ++i) {
        //         previous = previous->next();
        //     }
        //
        //     new_node->prev(previous);
        //     previous->next(new_node)
        // }
        //
        // ++size_;
    }  // insere no fim

    void push_front(const T& data) {
        auto new_node = new Node{data};
        new_node->next(head);
        head = new_node;
        ++size_;
    }  // insere no início

    void insert(const T& data, std::size_t index) {
        if (index > size_) {
            throw std::out_of_range("Out of range(insert)");
        }

        if (empty() || index == 0) {
            return push_front(data);
        }

        auto previous = head;

        for (auto i = 0u; i < index - 1; ++i) {
            previous = previous->next();
        }

        auto new_node = new Node{data, previous, previous->next()};
        new_node->next(previous->next());
        previous->next(new_node);
        if(new_node->next() != nullptr) {
            new_node->next()->prev(new_node);
        }
        ++size_;


//         before = node(index-1);
// novo->next(before->next());
// before->next(novo);
// novo->prev(before);
// if (novo->next() != nullptr) {
//     novo->next()->prev(novo);
// }
// size_++;
    }  // insere na posição

    void insert_sorted(const T& data) {
        auto current = head;
        auto i = 0u;

        while (i < size_ && current->data() < data) {
            current = current->next();
            ++i;
        }
        insert(data, i);
    }  // insere em ordem

    T pop(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index can't be bigger than size_ (pop)");
        }

        if (index == 0) {
            return pop_front();

        } else if (index == size_ - 1) {
            return pop_back();

        } else {
            auto current = head;

            for (auto i = 0u; i < index - 2; ++i) {
                current = current->next();
            }

            auto aux_node = current->next();
            auto temp = aux_node->next();
            current->next(aux_node->next());
            current->prev(aux_node->prev());
            delete aux_node;
            --size_;
            return temp->data();
        }
    } // retira da posição

    T pop_back() {
        if (empty()) {
            throw std::out_of_range("Empty (pop_back)");
        }

        if (size_ == 1) {
            return pop_front();
        }

        auto current = head;

        for (auto i = 0u; i < size_-2; ++i) {
            current = current->next();
        }
        auto aux_data = current->next()->data();
        delete current->next();
        current->next(nullptr);
        --size_;
        return aux_data;
    } // retira do fim

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
    } // retira do início

    void remove(const T& data) {
        if (find(data) == size_) {
        } else {
            pop(find(data) + 1);
        }
    } // retira específico

    bool empty() const {
        return size_ == 0;
    } // lista vazia

    bool contains(const T& data) const {
        return find(data) < size_;
    } // contém

    T& at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Out of range: Invalid index (at)");
        }

        Node *current = head;
        for (auto i = 0u; i < index; ++i) {
            current = current->next();
        }
        return current->data();
    } // acesso a um elemento (checando limites)

    const T& at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Out of range: Invalid index (at)");
        }

        Node *current = head;
        for (auto i = 0u; i < index; ++i) {
            current = current->next();
        }
        return current->data();
    } // getter constante a um elemento

    std::size_t find(const T& data) const {
        auto current = head;
        auto i = 0u;

        if (empty()) {
            throw std::out_of_range("Empty (find)");
        }

        while (i < size_) {
            if (current->data() == data) {
                break;
            }
            ++i;
            current = current->next();
        }
        return i;
    } // posição de um dado

    std::size_t size() const {
        return size_;
    } // tamanho

 private:
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        Node(const T& data, Node* prev, Node* next):
            data_{data},
            prev_{prev},
            next_{next}
        {}

        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
        }

        Node* prev() {
            return prev_;
        }
        const Node* prev() const {
            return prev_;
        }

        void prev(Node* node) {
            prev_ = node;
        }

        Node* next() {
            return next_;
        }
        const Node* next() const {
            return next_;
        }

        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* prev_{nullptr};
        Node* next_{nullptr};
    };

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namepsace structures

#endif
