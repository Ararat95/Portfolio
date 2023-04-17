#ifndef CQUEUE_H
#define CQUEUE_H
#include <iostream>
#include <initializer_list>

template <typename T>
class Cqueue {
    T* container;
    std::size_t _size;
    std::size_t _capacity;
    int front_idx;
    int back_idx;
public:
    Cqueue() = delete;
    Cqueue(std::size_t);
    Cqueue(std::initializer_list<T>);
    Cqueue(const Cqueue<T>&);
    Cqueue(Cqueue<T>&&);
    ~Cqueue();
public:
    Cqueue<T> operator = (const Cqueue<T>&) = delete;
    Cqueue<T> operator = (Cqueue<T>&&) = delete;
public:
    T& front();
    T& back();
    bool is_empty();
    bool is_full();
    std::size_t size();
    void push(const T&);
    T pop();
public:
    template <typename U>
    friend std::ostream& operator<< (std::ostream&, const Cqueue<U>&); 
};
#include "Cqueue.hpp"

#endif //CQUEUE_H