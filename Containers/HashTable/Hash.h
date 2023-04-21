#ifndef HASH_H
#define HASH_H

#include <string>
template <typename Key>
class Hash {
public:
    std::size_t operator() (const Key& key) const noexcept {
        return std::size_t(key);
    }
};

template <>
class Hash<std::string> {
public:
    std::size_t operator() (const std::string& str) const noexcept {
        std::size_t hashValue = 0;
        unsigned seed = 33;
        for (auto it : str) {
            hashValue = seed * hashValue + std::size_t(it);
        }
        return hashValue;
    }
};

template <typename Key, typename Value>
class Hash<std::pair<Key, Value>> {
public:
    std::size_t operator() (const std::pair<Key, Value>& input) const noexcept {
        return input.first;
    }
};

template <typename Value>
class Hash<std::pair<std::string, Value>> {
public:
    std::size_t operator() (const std::pair<std::string, Value>& input) const noexcept {
        std::size_t hashValue = 0;
        unsigned seed = 33;
        for (auto it : input.first) {
            hashValue = seed * hashValue + std::size_t(it);
        }
        return hashValue;
    }
};

#endif //HASH_H