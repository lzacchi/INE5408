/* Copyright 2017 Lucas Zacchi de Medeiros */
#include <./array_list.h>


namespace structures {

template<typename T>

/**
*Class implementing a Binary Tree
*/
class BinaryTree {
public:

    BinaryTree() = default;

    virtual ~BinaryTree() {
        delete root;
        size_ = 0;
    }

    /**
    * Insert
    */
    void insert(const T& data) {
        if (empty()) {
            root = new Node{data};
        } else {
            root->insert(data);
        }
        ++size_;
    }

    /**
    * Remove
    */
    void remove(const T& data) {
        bool check;
        if (empty()) {
            return;
        } else {
            check = root->remove(data);
            if (check) {
                --size_;
            }
        }

    }

    /**
    * Contains
    */
    bool contains(const T& data) const {
        if (empty())
            return false;
        else
            return root->contains(data);
    }

    /**
    * Empty
    */
    bool empty() const {
        return size_ == 0;
    }


    /**
    * Size
    */
    std::size_t size() const {
        return size_;
    }


    /**
    * Pre Order
    */
    ArrayList<T> pre_order() const {
        structures::ArrayList<T> v{};

        if (!empty()) {
            root->pre_order(v);
        }
        return v;
    }


    /**
    * In Order
    */
    ArrayList<T> in_order() const {
        structures::ArrayList<T> v{};

        if (!empty()) {
            root->in_order(v);
        }
        return v;
    }


    /**
    * Post Order
    */
    ArrayList<T> post_order() const {
        structures::ArrayList<T> v{};

        if (!empty()) {
            root->post_order(v);
        }
        return v;
    }

private:
    struct Node {
        Node(const T& data):
            data{data},
            left{nullptr},
            right{nullptr}
        {}

        T data;
        Node* left;
        Node* right;

        void insert(const T& data_) {
            if (data_ < data) {
                // Insert to the left
                if (left == nullptr) {
                    auto new_node = new Node{data_};
                    left = new_node;
                } else {
                    left->insert(data_);
                }
            } else if (data_ > data) {
                // Insert to the right
                if (right == nullptr) {
                    auto new_node = new Node{data_};
                    right = new_node;
                } else {
                    right->insert(data_);
                }
            }
        }

        bool remove(const T& data_) {
            if (data_ == data) {
                if (left != nullptr and right != nullptr) {
                    auto aux_node = left_tree(right);
                    data = aux_node->data;
                    return right->remove(data);
                } else if (right != nullptr) {
                    data = right->data;
                    return right->remove(data);
                } else if (left != nullptr) {
                    data = left->data;
                    return left->remove(data);
                } else {
                    delete this;
                    return true;
                }
            } else {
                if (right != nullptr and data < data_) {
                    return right->remove(data_);
                } else if (left != nullptr and data > data_) {
                    return left->remove(data_);
                }
            }
            return false;
        }

        bool contains(const T& data_) const {
            if (data == data_)
                return true;

            else if (left != nullptr and data_ < data) {
                return left->contains(data_);

            } else if (right != nullptr and data_ > data) {
                return right->contains(data_);
            }

            return false;
        }

        void pre_order(ArrayList<T>& v) const {
            v.push_back(data);  // Root

            if (left != nullptr) {
                left->pre_order(v);
            }
            if (right != nullptr) {
                right->pre_order(v);
            }
        }

        void in_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->in_order(v);
            }

            v.push_back(data);  // Root

            if (right != nullptr) {
                right->in_order(v);
            }
        }

        void post_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->post_order(v);
            }

            if (right != nullptr) {
                right->post_order(v);
            }

            v.push_back(data);  // Root
        }

        Node* left_tree(Node* node) {
            while(node->left != nullptr) {
                node = node->left;
            }
            return node
        }
    };

    Node* root;
    std::size_t size_;
};

}  // namespace structures