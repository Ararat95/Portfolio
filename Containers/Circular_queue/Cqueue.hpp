#include "Cqueue.h"

template<typename T>
Cqueue<T>::Cqueue(std::size_t size) {
    this->_size = 0;
    this->_capacity = size;
    this->container = new T[this->_capacity];
    this->front_idx = this->back_idx = -1;
}

template <typename T>
Cqueue<T>::Cqueue(std::initializer_list<T> list) {
    this->_size = this->_capacity = list.size();
    this->container = new T[this->_capacity];
    int i = 0;
    for (int it : list) {
        this->container[i] = it;
        ++i;
    }
    this->front_idx = 0;
    this->back_idx = this->_capacity - 1;
}

template <typename T>
Cqueue<T>::Cqueue(const Cqueue<T>& src) {
    this->_size = src._size;
    this->_capacity = src._capacity;
    this->container = new T[this->_capacity];
    for (int i = 0; i < this->_capacity; ++i) {
        this->container[i] = src.container[i];
    }
    this->front_idx = src.front_idx;
    this->back_idx = src.back_idx;
}

template <typename T>
Cqueue<T>::Cqueue(Cqueue<T>&& src) {
    this->_size = std::move(src._size);
    this->_capacity = std::move(src._capacity);
    this->container = std::move(src.container);
    this->front_idx = std::move(src.front_idx);
    this->back_idx = std::move(src.back_idx);
    src.container = nullptr;
}

template <typename T>
Cqueue<T>::~Cqueue() {
    delete[] this->container;
}

template <typename U>
std::ostream& operator<< (std::ostream& os, const Cqueue<U>& src) {
    os << '[';
    int i = src.front_idx;
    while (i != src.back_idx) {
        os << src.container[i] << ',';
        if (i == src._capacity - 1) {
            i = 0;
            continue;
        }
        ++i;
    }
    os << src.container[i] << ']';
    return os;
}

template <typename T>
T& Cqueue<T>::front() {
    return this->container[this->front_idx];
}

template <typename T>
T& Cqueue<T>::back() {
    return this->container[this->back_idx];
}

template <typename T>
bool Cqueue<T>::is_empty() {
    return (this->front_idx == -1);
}

template <typename T>
bool Cqueue<T>::is_full() {
    if (this->front_idx == 0 && this->back_idx == this->_capacity - 1) {
        return true; 
    }
    if (this->back_idx + 1 == this->front_idx) {
        return true;
    }
    return false;
}

template <typename T>
std::size_t Cqueue<T>::size() {
    return this->_size;
}

template <typename T>
void Cqueue<T>::push(const T& data) {
    if (this->is_full()) {
        std::cout << "queue is full\n";
        return;
    }
    if (this->is_empty()) {
        this->back_idx = this->front_idx = 0;
    }
    else if (this->back_idx == this->_capacity - 1) {
        this->back_idx = 0;
    }
    else {
        ++this->back_idx;
    }
    this->container[this->back_idx] = data;
    ++this->_size;
}

template <typename T>
T Cqueue<T>::pop() {
    if (this->is_empty()) {
        std::cout << "queue is empty\n";
        return -1;
    }
    T value = this->container[this->front_idx];
    if (this->back_idx == this->front_idx) {
        this->back_idx = this->front_idx = -1;
    }
    else if (this->front_idx == this->_capacity - 1) {
        this->front_idx = 0;
    }
    else {
        ++this->front_idx;
    }
    --this->_size;
    return value;
}