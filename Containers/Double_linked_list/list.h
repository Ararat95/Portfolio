#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <iterator>
#include <initializer_list>

template <typename T>
class list {
public:
    list() : head{nullptr}, tail{nullptr}, _size{0} {};
    list(const list<T>&);
    list(list<T>&&);
    list(const T&);
    list(std::initializer_list<T>);
    ~list();
public:
    list<T> operator = (const list<T>&);
    list<T> operator = (list<T>&&);
public:
    void push_back(const T&);
    void push_back(T&&);
    void pop_back();
    void push_front(const T&);
    void push_front(T&&);
    void pop_front();
    void clear();
    bool empty();
private:
    struct Node {
        T value;
        Node* next;
        Node* prev;
        Node() : next{nullptr}, prev{nullptr}, value{0} {};
        Node(const T& val) : next{nullptr}, prev{nullptr}, value{val} {};
    }*head, *tail;
    std::size_t _size;
public:
    class iterator : std::iterator<std::bidirectional_iterator_tag, T> {
    public:
    friend class list<T>;
        iterator() : iter{nullptr} {};
        iterator(Node* const);
        iterator(const iterator&);
        ~iterator();
    public:
        bool operator == (const iterator&);
        bool operator != (const iterator&);
        T& operator * ();
        T* operator -> ();
        iterator& operator ++ ();
        iterator operator ++ (int);
        iterator& operator -- ();
        iterator operator -- (int);
    private:
        Node* iter;
    };
public:
    iterator begin();
    iterator begin() const;
    iterator end();
    iterator end() const;
    void insert(iterator, const T&);
    void erase(iterator);
    void erase(iterator, iterator);
    size_t size() const;
    friend std::ostream& operator << (std::ostream& os, list<T>& src) {
        Node* tmp = src.head;
        os << "{ ";
        while (tmp) {
            os << tmp->value << ' ';
            tmp = tmp->next;
        }
        os << "}";
        return os;
    }
};
#include "list.hpp"

#endif // LIST_H