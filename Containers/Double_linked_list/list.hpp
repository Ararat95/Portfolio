#include "list.h"

template <typename T>
list<T>::list(const list<T>& src) {
    if (src.head) {
        this->_size = src._size;
        this->head = new Node(src.head->value);
        Node* tmp = this->head;
        Node* src_tmp = src.head;
        src_tmp = src_tmp->next;
        while (src_tmp) {
            tmp->next = new Node(src_tmp->value);
            tmp->next->prev = tmp;
            tmp = tmp->next;
            src_tmp = src_tmp->next;
        }
        this->tail = tmp;
    }
    else {
        this->head = this->tail = nullptr;
        this->_size = 0;
    }
}

template <typename T>
list<T>::list(list<T>&& src) {
    if (src.head) {
        this->head = src.head;
        this->tail = src.tail;
        this->_size = src._size;
        src.head = nullptr;
        src.tail = nullptr;
        src->_size = 0;
        
    }
}

template <typename T>
list<T>::list(std::initializer_list<T> src) {
    auto it = src.begin();
    if (it) {
        this->_size = src.size();
        this->head = new Node(*it);
        Node* tmp = this->head;
        ++it;
        while (it != src.end()) {
            tmp->next = new Node(*it);
            tmp->next->prev = tmp;
            tmp = tmp->next;
            ++it;
        }
    }
    else {
        this->head = this->tail = nullptr;
        this->_size = 0;
    }
}

template <typename T>
list<T>::~list() {
    clear();
}

template <typename T>
void list<T>::clear() {
    if (!this->head) {
        return;
    }
    Node* tmp = this->head;
    while (tmp) {
        tmp = tmp->next;
        this->head->prev = nullptr;
        delete this->head;
        this->head = tmp;
    }
    this->head = tmp = this->tail = nullptr;
    this->_size = 0;
}

template <typename T>
list<T> list<T>::operator = (const list<T>& rhs) {
    if (this->head) {
        clear();
    }
    if (rhs.head) {
        this->_size = rhs._size;
        this->head = new Node(rhs.head->value);
        Node* tmp = this->head;
        Node* rhs_tmp = rhs.head;
        rhs_tmp = rhs_tmp->next;
        while (rhs_tmp) {
            tmp->next = new Node(rhs_tmp->value);
            tmp->next->prev = tmp;
            tmp = tmp->next;
            rhs_tmp = rhs_tmp->next;
        }
        this->tail = tmp;
    }
    return *this;
}

template <typename T>
list<T> list<T>::operator = (list<T>&& rhs) {
    if (this->head) {
        clear();
    }
    if (rhs.head) {
        this->head = rhs.head;
        this->tail = rhs.tail;
        this->_size = rhs._size;
        rhs.head = rhs.tail = nullptr;
        rhs._size = 0;
    }
    return *this;
}

template <typename T>
void list<T>::push_back(const T& value) {
    if (!this->tail) {
        this->head = this->tail = new Node(value);
        ++this->_size;
        return;
    }
    Node* tmp = this->tail;
    this->tail = new Node(value);
    tmp->next = this->tail;
    this->tail->prev = tmp;
    ++this->_size;
}

template <typename T>
void list<T>::push_back(T&& value) {
    if (!this->tail) {
        this->head = this->tail = new Node(value);
        ++this->_size;
        return;
    }
    Node* tmp = this->tail;
    this->tail = new Node(value);
    tmp->next = this->tail;
    this->tail->prev = tmp;
    ++this->_size;
}

template <typename T>
void list<T>::pop_back() {
    if (!this->tail) {
        return;
    }
    if (this->head == this->tail) {
        delete this->head;
        this->head = this->tail = nullptr;
        this->_size = 0;
        return;
    }
    Node* tmp = this->tail;
    this->tail = this->tail->prev;
    this->tail->next = nullptr;
    delete tmp;
    --this->_size;
}

template <typename T>
void list<T>::push_front(const T& value) {
    if (!this->head) {
        this->head = this-tail = new Node(value);
        ++this->_size;
        return;
    }
    Node* tmp = this->head;
    this->head = new Node(value);
    this->head->next = tmp;
    tmp->prev = this->head;
    ++this->_size;
}

template <typename T>
void list<T>::push_front(T&& value) {
    if (!this->head) {
        this->head = this->tail = new Node(value);
        ++this->_size;
        return;
    }
    Node* tmp = this->head;
    this->head = new Node(value);
    this->head->next = tmp;
    tmp->prev = this->head;
    ++this->_size;
}

template <typename T>
void list<T>::pop_front() {
    if (!this->head) {
        return;
    }
    if (this->head == this->tail) {
        delete this->head;
        this->head = this->tail = nullptr;
        this->_size = 0;
    }
    Node* tmp = this->head;
    this->head = this->head->next;
    this->head->prev = nullptr;
    delete tmp;
    this->_size = 0;
}

template <typename T>
bool list<T>::empty() {
    return (!this->_size);
}

template <typename T>
std::size_t list<T>::size() const {
    return this->_size;
}

template <typename T>
typename list<T>::iterator list<T>::begin() const {
    return list<T>::iterator(this->head);
}

template <typename T>
typename list<T>::iterator list<T>::end() const {
    return list<T>::iterator(this->tail);
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
    return list<T>::iterator(this->head);
}

template <typename T>
typename list<T>::iterator list<T>::end() {
    return list<T>::iterator(this->tail);
}

template <typename T>
void list<T>::insert(list<T>::iterator it, const T& value) {
    if (!this->head) {
        this->head = this->tail = new Node(value);
        ++this->_size;
        it = list<T>::iterator(this->head);
        return;
    }
    Node* tmp = this->head;
    while (tmp != it.iter) {
        tmp = tmp->next;  
        if (!tmp) {
            return;
        }      
    }
    if (tmp->prev) {
        Node* curr = tmp->prev;
        curr->next = new Node(value);
        curr->next->prev = curr;
        curr->next->next = tmp;
        tmp->prev = curr->next;
        ++this->_size;
    }
    else {
        tmp->prev = new Node(value);
        this->head = tmp->prev;
        this->head->next = tmp;
        ++this->_size;
    }
}

template <typename T>
void list<T>::erase(list<T>::iterator it) {
    if (!this->head || !it.iter) {
        return;
    }
    Node* tmp = this->head;
    while (tmp != it.iter) {
        tmp = tmp->next;
        if (!tmp) {
            return;
        }
    }
    if (!tmp->next && !tmp->prev) {
        clear();
        return;
    }
    if (tmp->prev) {
        tmp->prev->next = tmp->next;
    }
    else if (tmp->next) {
        this->head = tmp->next;
    }
    if (tmp->next) {
        tmp->next->prev = tmp->prev;
    }
    else if (tmp->prev){
        this->tail = tmp->prev;
    }
    delete tmp;
    --this->_size;
    tmp = nullptr;
}

template <typename T>
void list<T>::erase(list<T>::iterator start, list<T>::iterator end) {
    if (!this->head || !start.iter || !end.iter) {
        return;
    }
    Node* tmp = this->head;
    while (tmp) {
        if (tmp == start.iter) {
            while (tmp != end.iter) {
                Node* tmp_deletabe = tmp;
                tmp = tmp->next;
                if (tmp_deletabe->prev) {
                    tmp_deletabe->prev->next = tmp;
                }
                else if (tmp_deletabe->next) {
                    this->head = tmp_deletabe->next;
                }
                if (tmp_deletabe->next) {
                    tmp->prev = tmp_deletabe->prev;
                }
                else if (tmp_deletabe->prev) {
                    this->tail = tmp_deletabe->prev;
                }
                delete tmp_deletabe;
                tmp_deletabe = nullptr;
                --this->_size;
            }
            return;
        }
        tmp = tmp->next;
    }
}

template <typename T>
list<T>::iterator::iterator(list<T>::Node* const src) {
    this->iter = src;
}

template <typename T>
list<T>::iterator::iterator(const list<T>::iterator& src) {
    this->iter = src.iter;
}

template <typename T>
list<T>::iterator::~iterator() {
    iter = nullptr;
}

template <typename T>
bool list<T>::iterator::operator==(const iterator& src) {
    return (this->iter == src.iter);
}

template <typename T>
bool list<T>::iterator::operator!=(const iterator& src) {
    return (this->iter != src.iter);
}

template <typename T>
T& list<T>::iterator::operator*() {
    return this->iter->value;
}

template <typename T>
T *list<T>::iterator::operator->() {
    return &this->iter->value;
}

template <typename T>
typename list<T>::iterator& list<T>::iterator::operator++() {
    this->iter = this->iter->next;
    return *this;
}

template <typename T>
typename list<T>::iterator list<T>::iterator::operator++(int) {
    iterator tmp(this->iter);
    this->iter = this->iter->next;
    return tmp;
}

template <typename T>
typename list<T>::iterator& list<T>::iterator::operator--() {
    this->iter = this->iter->prev;
    return *this;
}

template <typename T>
typename list<T>::iterator list<T>::iterator::operator--(int) {
    iterator tmp(this->iter);
    this->iter = this->iter->prev;
    return tmp;
}