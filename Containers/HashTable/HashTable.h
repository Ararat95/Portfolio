#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <iostream>
#include "Hash.h"

template <typename Key, typename Value>
class HashTable {
public:
    HashTable();
    explicit HashTable(const std::size_t);
    HashTable(const HashTable<Key, Value>&) = default;
    HashTable(HashTable<Key, Value>&&) = default;
public:
    HashTable<Key, Value> operator= (const HashTable<Key, Value>&) noexcept;
    HashTable<Key, Value> operator= (HashTable<Key, Value>&&) noexcept;
    template <typename T, typename U>
    friend std::ostream& operator<< (std::ostream& os, const HashTable<T, U>& src) {
        os << "{\n";
        for (auto& vIter : src.tables) {
            if (vIter.empty()) continue;
            for (auto& lIter : vIter) {
                os << '\t' << "Key: " << lIter.first << " Value: " << lIter.second << '\n';
            }
        }
        os << '}';
        return os;
    }
public:
    bool is_empty() const noexcept;
    void insert(const std::pair<Key, Value>&) noexcept;
    void remove(const Key&) noexcept;
    bool contains(const Key&) const noexcept;
    void clear() noexcept;
    std::size_t size() const noexcept;
private:
    void check_list(const std::pair<Key, Value>&) noexcept;
    void resize() noexcept;
    std::size_t hashing(const Key&) const noexcept;
    void rehash() noexcept;
private:
    std::size_t m_size;
    std::size_t m_capacity;
    std::size_t m_list_capacity;
    std::vector<std::list<std::pair<Key, Value>>> tables;
};
#include "HashTable.hpp"

#endif //HASHTABLE_H