/* "Copyright [2017] <Lucas Zacchi de Medeiros" */
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>
#include <stdexcept>


namespace structures {

template<typename T>
/*! Class implementing an Array List.
*
* In it are all the methods necessary to a List structure.
*/
class ArrayList {
 public:
    /*! Constructor without arguments.
    *
    */
    ArrayList() {
        max_size_ = DEFAULT_MAX;
        contents = new T[max_size_];
        size_ = 0;
    }

    /*! Constructor with an argument.
    *
    * @arg max_size = the lists maximum available size.
    */
    explicit ArrayList(std::size_t max_size) {
        max_size_ = max_size;
        size_ = 0;
        contents = new T[max_size];
    }

    /*! Destructor.
    *
    */
    ~ArrayList() {
        delete[] contents;
    }

    /*! Clear.
    *
    * Removes elements and resets size_
    */
    void clear() {
        size_ = 0;
    }

    /*! Push Back
    *
    * Inserts element in the lest position
    */
    void push_back(const T& data) {
        insert(data, size_);
    }

    /*! Push front
    *
    * Inserts elements in the first position
    */
    void push_front(const T& data) {
        insert(data, 0);
    }

    /*! Insert
    *
    * Inserts elements at a given position
    * @arg index = position in which the element is going to be inserted.
    */
    void insert(const T& data, std::size_t index) {
        if (full()) {
            throw std::out_of_range("The list is full.");
        }


        if (index > size_) {
            throw std::out_of_range("invalid");
        }
        for (auto i = size_; i > index; --i) {
            contents[i] = contents[i - 1];
        }


        contents[index] = data;
        ++size_;
    }

    /*! Insert Sorted
    *
    * Sorts elements by size.
    */
     void insert_sorted(const T& data) {
        if (full()) {
            throw std::out_of_range("It's full.");
        }

        auto position = 0u;

        while (position < size_ && data > contents[position]) {
            ++position;
        }

        insert(data, position);
    }

    /*! Pop
    *
    * Returns element stored in a given position.
    * @arg index = position to be accessed.
    */
    T pop(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Invalid position.");
        }
        auto stuff = contents[index];

        size_--;

        while (index < size_) {
            contents[index] = contents[index + 1];
                ++index;
        }

        return stuff;
    }

    /*! Pop Back.
    *
    * Returns last element.
    */
    T pop_back() {
        return pop(size_ - 1);
    }

    /*! Pop Front.
    *
    * Returns first element.
    */
    T pop_front() {
        return pop(0);
    }

    /*! Remove.
    *
    * Removes an element from the list.
    */
    void remove(const T& data) {
        pop(find(data));
    }

    /*! Full.
    *
    * Checks if the list is full.
    */
    bool full() const {
        return size_ == max_size_;
    }

    /*! Empty
    *
    * Checks if the list is empty
    */
    bool empty() const {
        return size_ == 0;
    }

    /*! Contains.
    *
    * Checks if an element is stored in the list
    */  
    bool contains(const T& data) const {
        return find(data)< size_;
    }

    /*! Find.
    *
    * Search for an element and return its position.
    */  
    std::size_t find(const T& data) const {
        auto current = 0;

        while (current < size_ && data != contents[current]) {
            current++;
        }
        return current;
    }

    /*! Size.
    *
    * Getter: returns size.
    */  
    std::size_t size() const {
        return size_;
    }

    /*! Max Size.
    *
    * Getter: Returns maximum size.
    */  
    std::size_t max_size() const {
        return max_size_;
    }

    /*! Operator at.
    *
    * Overloads Operator at.
    */  
    T& at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Invalid position.");
        } else {
            return contents[index];
        }
    }

    /*! Operator at.
    *
    * Overloads Operator at.
    */
    T& operator[](std::size_t index) {
        return contents[index];
    }

     /*! Class implementing an Array Queue.
    *
    * In it are all the methods necessary to a Queue structure.
    */  
    const T& at(std::size_t index) const {
        if (empty()) {
            throw std::out_of_range("The list is already empty.");
        }
        if (index >= size_) {
            throw std::out_of_range("Invalid position.");
        } else {
            return contents[index];
        }
    }

    /*! Operator at.
    *
    * Overloads Operator at.
    */  
    const T& operator[](std::size_t index) const {
        return contents[index];
    }

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};

}  // namespace structures

#endif

