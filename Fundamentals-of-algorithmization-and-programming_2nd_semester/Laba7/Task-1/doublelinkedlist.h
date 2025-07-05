#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <cstddef>
#include <utility>

template <typename T>
class DoubleLinkedList {
   private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head_;
    Node* tail_;
    std::size_t size_;

   public:
    DoubleLinkedList() noexcept : head_(nullptr), tail_(nullptr), size_(0) {}
    ~DoubleLinkedList() noexcept { clear(); }

    DoubleLinkedList(const DoubleLinkedList&) = delete;
    DoubleLinkedList(DoubleLinkedList&& other) noexcept {
        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }

    DoubleLinkedList& operator=(const DoubleLinkedList&) = delete;
    DoubleLinkedList& operator=(DoubleLinkedList&& other) noexcept {


        if (this != &other) {
            clear();
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            other.head_ = other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    bool empty() const noexcept { return size_ == 0; }
    std::size_t size() const noexcept { return size_; }
    void clear() noexcept;

    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();
    void swap_min_max_nodes();	 // swaps *nodes*
    void swap_min_max_values();	 // swaps *values* only

    Node* head() const { return head_; }
    Node* find(const T& value) const noexcept;

    class Iterator {
        Node* ptr_;

       public:
        explicit Iterator(Node* p = nullptr) : ptr_(p) {}

        Iterator& operator++() {
            if (ptr_) {
                ptr_ = ptr_->next;
            }
            return *this;
        }
        T& operator*() const { return ptr_->data; }
        Node* operator->() const { return ptr_; }

        bool operator==(const Iterator& other) const {
            return ptr_ == other.ptr_;
        }
        bool operator!=(const Iterator& other) const {
            return ptr_ != other.ptr_;
        }
    };


    Iterator begin() const { return Iterator(head_); }


    Iterator end() const { return Iterator(nullptr); }
};


template <typename T>
void DoubleLinkedList<T>::push_front(const T& value) {
    Node* node = new Node(value);
    node->next = head_;


    if (head_) {
        head_->prev = node;
    }
    head_ = node;


    if (!tail_) {
        tail_ = head_;
    }
    ++size_;
}

template <typename T>
void DoubleLinkedList<T>::push_back(const T& value) {
    Node* node = new Node(value);
    node->prev = tail_;


    if (tail_) {
        tail_->next = node;
    }
    tail_ = node;


    if (!head_) {
        head_ = tail_;
    }
    ++size_;
}

template <typename T>
void DoubleLinkedList<T>::pop_front() {


    if (!head_) {
        return;
    }
    Node* temp = head_;
    head_ = head_->next;


    if (head_) {
        head_->prev = nullptr;
    } else {
        tail_ = nullptr;
    }
    delete temp;
    --size_;
}

template <typename T>
void DoubleLinkedList<T>::pop_back() {


    if (!tail_) {
        return;
    }
    Node* temp = tail_;
    tail_ = tail_->prev;


    if (tail_) {
        tail_->next = nullptr;
    } else {
        head_ = nullptr;
    }
    delete temp;
    --size_;
}

template <typename T>
void DoubleLinkedList<T>::clear() noexcept {
    Node* temp;


    while (head_) {
        temp = head_;
        head_ = head_->next;
        delete temp;
    }
    tail_ = nullptr;
    size_ = 0;
}

template <typename T>
typename DoubleLinkedList<T>::Node* DoubleLinkedList<T>::find(
    const T& value) const noexcept {
    Node* current = head_;


    while (current) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template <typename T>
void DoubleLinkedList<T>::swap_min_max_nodes() {


    if (!head_ || !head_->next) {
        return;
    }

    Node* min_node = head_;
    Node* max_node = head_;


    for (Node* curr = head_->next; curr; curr = curr->next) {
        if (curr->data < min_node->data) {
            min_node = curr;
        }
        if (curr->data > max_node->data) {
            max_node = curr;
        }
    }


    if (min_node == max_node) {
        return;
    }


    if (min_node->next == max_node || max_node->next == min_node) {
        Node* first = (min_node->next == max_node) ? min_node : max_node;
        Node* second = (first == min_node) ? max_node : min_node;
        Node* before = first->prev;
        Node* after = second->next;

        if (before) {
            before->next = second;
        }
        if (after) {
            after->prev = first;
        }

        second->prev = before;
        second->next = first;
        first->prev = second;
        first->next = after;
    } else {
        std::swap(min_node->prev, max_node->prev);
        std::swap(min_node->next, max_node->next);

        if (min_node->prev) {
            min_node->prev->next = min_node;
        }
        if (min_node->next) {
            min_node->next->prev = min_node;
        }
        if (max_node->prev) {
            max_node->prev->next = max_node;
        }
        if (max_node->next) {
            max_node->next->prev = max_node;
        }
    }


    if (head_ == min_node) {
        head_ = max_node;
    } else if (head_ == max_node) {
        head_ = min_node;
    }


    if (tail_ == min_node) {
        tail_ = max_node;
    } else if (tail_ == max_node) {
        tail_ = min_node;
    }
}

template <typename T>
void DoubleLinkedList<T>::swap_min_max_values() {


    if (!head_ || !head_->next) {
        return;
    }

    Node* min_node = head_;
    Node* max_node = head_;


    for (Node* curr = head_->next; curr; curr = curr->next) {
        if (curr->data < min_node->data) {
            min_node = curr;
        }
        if (curr->data > max_node->data) {
            max_node = curr;
        }
    }


    if (min_node != max_node) {
        std::swap(min_node->data, max_node->data);
    }
}

#endif	// DOUBLELINKEDLIST_H
