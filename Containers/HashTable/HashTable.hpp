#include "HashTable.h"

template <typename Key, typename Value>
HashTable<Key, Value>::HashTable() : 
m_size{0},
m_capacity{5},
m_list_capacity{20},
tables(m_capacity) 
{}

template <typename Key, typename Value>
HashTable<Key, Value>::HashTable(const std::size_t size) : 
m_size{0},
m_capacity{size},
m_list_capacity{20},
tables(m_capacity) 
{}

template <typename Key, typename Value>
HashTable<Key, Value> HashTable<Key, Value>::operator= (const HashTable<Key, Value>& rhs) noexcept {
    this->m_list_capacity = rhs.m_list_capacity;
    this->m_size = rhs.m_size;
    for (int i{}; i < rhs.tables.size(); ++i) {
        this->tables[i] = rhs.tables[i];
    }
    rehash();
    return *this;
} 

template <typename Key, typename Value>
HashTable<Key, Value> HashTable<Key, Value>::operator= (HashTable<Key, Value>&& rhs) noexcept {
    this->m_list_capacity = std::move(rhs.m_list_capacity);
    this->m_size = std::move(rhs.m_size);
    for (int i{}; i < rhs.tables.size(); ++i) {
        this->tables[i] = std::move(rhs.tables[i]);
    }
    rhs.m_capacity = 0;
    rehash();
    return *this;
}

template <typename Key, typename Value>
void HashTable<Key, Value>::check_list(const std::pair<Key, Value>& src) noexcept {
    auto& cell = this->tables[hashing(src.first)];
    if (this->m_list_capacity == cell.size()) {
        resize();
    }
}

template <typename Key, typename Value>
void HashTable<Key, Value>::resize() noexcept {
    m_capacity *= 2;
    std::vector<std::list<std::pair<Key, Value>>> tmp(m_capacity);
    tmp = std::move(this->tables);
    this->tables = std::move(tmp);
}

template <typename Key, typename Value>
void HashTable<Key, Value>::rehash() noexcept {
    std::vector<std::pair<Key, Value>> data;
    for (auto& vIter : this->tables) {
        if (vIter.empty()) continue;
        for (auto& lIter : vIter) {
            data.emplace_back(lIter);
        }
    }
    clear();
    for (auto& iter : data) {
        insert(iter);
    }
}

template <typename Key, typename Value>
bool HashTable<Key, Value>::is_empty() const noexcept {
    if (this->m_size) {
        return false;
    }
    return true;
}

template <typename Key, typename Value>
std::size_t HashTable<Key, Value>::size() const noexcept {
    return this->m_size;
}

template <typename Key, typename Value>
void HashTable<Key, Value>::insert(const std::pair<Key, Value>& src) noexcept {
    check_list(src);
    auto& cell = this->tables[hashing(src.first)];
    auto it = cell.begin();
    bool exists = false;
    for (; it != cell.end(); ++it) {
        if (it->first == src.first) {
            exists = true;
            it->second = src.second;
            std::cout << "[WARNING] Key exists, Value replaced. " << std::endl;
        }
    }
    if (!exists) {
        cell.emplace_back(src);
        ++this->m_size;
    }
}

template <typename Key, typename Value>
void HashTable<Key, Value>::remove(const Key& key) noexcept {
    if (!this->m_size) {
        std::cout << "[WARNING] Table is empty. " << std::endl;
        return;
    }
    auto& cell = this->tables[hashing(key)];
    auto it = cell.begin();
    bool exists = false;
    for (; it != cell.end(); ++it) {
        if (it->first == key) {
            exists = true;
            it = cell.erase(it);
            --this->m_size;
            std::cout << "[INFO] Data removed. " << std::endl;
        }
    }
    if (!exists) {
        std::cout << "[WARNING] Key doesn't exists: " << std::endl; 
    }
}

template <typename Key, typename Value>
bool HashTable<Key, Value>::contains(const Key& key) const noexcept {
    auto& cell = this->tables[hashing(key)];
    auto iter = cell.begin();
    for (; iter != cell.end(); ++iter) {
        if (iter->first == key) {
            return true;
        }
    }
    return false;
}

template <typename Key, typename Value>
void HashTable<Key, Value>::clear() noexcept {
    for (auto& iter : this->tables) {
        iter.clear();
    }
    this->m_size = 0;
}

template <typename Key, typename Value>
std::size_t HashTable<Key, Value>::hashing(const Key& key) const noexcept {
    static Hash<Key> hashObj;
    return (hashObj(key) % this->tables.size());
}

