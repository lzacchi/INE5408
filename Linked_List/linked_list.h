/* "Copyright 2017 Lucas Zacchi de Medeiros" */
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>


namespace structures {

template<typename T>
/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
class LinkedList {
 public:
    LinkedList() {}  // construtor padrão

    ~LinkedList() {
        clear();
    }

/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
    void clear() {
        // auto _size = size_;
        // for (auto i = 0u; i < _size; ++i) {
        //     pop_front();
        // }
        while (!empty()) {
            pop_front();
        }
    }  // limpar lista

/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
    void push_back(const T& data) {
        auto new_node = new Node{data};
        if (new_node == nullptr) {
            throw std::out_of_range("The list is full");
        }
        if (empty()) {
            head = new_node;
        } else {
            auto previous = head;

            for (auto i = 0u; i < size_ - 1; ++i) {
                previous = previous->next();
            }
            previous->next(new_node);
        }
        ++size_;
    }  // inserir no fim

/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
    void push_front(const T& data) {
        auto new_node = new Node{data};

        new_node->next(head);
        head = new_node;
        ++size_;
    }  // inserir no início

/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
    void insert(const T& data, std::size_t index) {
        if (index > size_) {
            throw std::out_of_range("Invalid index");
        }

        if (empty() || index == 0) {
            return push_front(data);
        }
        auto previous = head;

        for (auto i = 0; i < index - 1; ++i) {
            previous = previous->next();
        }

        auto new_node = new Node{data, previous->next()};
        previous->next(new_node);

        ++size_;
    }  // inserir na posição

/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
    void insert_sorted(const T& data) {
        auto current = head;
        auto i = 0u;

        while (i < size_ && current->data() < data) {
            current = current->next();
            ++i;
        }
        insert(data, i);
    }  // inserir em ordem

/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
    T& at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("WUBBA LUBBA DUB DUB");
        }

        Node *current = head;
        for (auto i = 0u; i < index; ++i) {
            current = current->next();
        }
        return current->data();
    }  // acessar um elemento na posição index

/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
    T pop(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Get Schwifty");
        }

        if (index == 0) {
            return pop_front();

        } else if (index == size_ - 1) {
            return pop_back();

        } else {
            auto current = head;
            for (auto i = 0u; i < index -2; ++i) {
                current = current->next();
            }

            auto aux_node = current->next();
            auto temp = aux_node->next();
            current->next(aux_node->next());
            delete aux_node;
            --size_;
            return temp->data();
        }
    }  // retirar da posição

/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
    T pop_back() {
        if (empty()) {
            throw std::out_of_range("empty");
        }

        if (size_ == 1) {
            return pop_front();
        }
        auto current = head;

        for (auto i = 0u; i < size_ - 2; ++i) {
            current = current->next();
        }
        auto aux_data = current->next()->data();
        delete current->next();
        current->next(nullptr);
        --size_;
        return aux_data;
    }  // retirar do fim

/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
    T pop_front() {
        if (empty()) {
            throw std::out_of_range("BITE ME");
        }
        auto aux_node = head;
        head = head->next();

        auto aux_data = aux_node->data();
        delete aux_node;

        --size_;
        return aux_data;
    }  // retirar do início

/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
    void remove(const T& data) {
        if (find(data) == size_) {
        } else {
            pop(find(data) + 1);
        }
    }  // remover específico

/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
    bool empty() const {
        return size_ == 0;
    }  // lista vazia

/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
    bool contains(const T& data) const {
        return find(data) < size_;
    }  // contém

/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
    std::size_t find(const T& data) const {
        auto current = head;
        auto i = 0;

        if (empty()) {
            throw std::out_of_range("pipoco");
        }
        while (i < size_) {
            if (current->data() == data) {
                break;
            }
            ++i;
            current = current->next();
        }
        return i;
    }  // posição do dado

/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
    std::size_t size() const {
        return size_;
    }  // tamanho da lista

 protected:
/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
    class Node {  // Elemento
     public:
/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
        explicit Node(const T& data):
            data_{data}
        {}

/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
        T& data() {  // getter: dado
            return data_;
        }

/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
        const T& data() const {  // getter const: dado
            return data_;
        }

/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
        Node* next() {  // getter: próximo
            return next_;
        }

/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
        const Node* next() const {  // getter const: próximo
            return next_;
        }

/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
     protected:
        T data_;

/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
        Node* next_{nullptr};
    };

/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
    Node* head{nullptr};

/*! SOMETHING SOMETHING
* ASLASDASD
*SUIDIAHSIDUAHS*/
    std::size_t size_{0u};
};

}  // namespace structures

#endif
