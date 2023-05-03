#ifndef BST_H
#define BST_H

#include <iostream>
#include <queue>

template <typename T>
class BST {
public:
    BST(const T&);
    BST(const BST&);
    BST(BST&&);
    ~BST();
public:
    BST operator= (const BST&);
    BST operator= (BST&&);
public:
    void insert(const T) noexcept;
    void remove(const T) noexcept;
private:
    struct Node {
        T value;
        Node* left;
        Node* right;
        Node() : value{0}, left{nullptr}, right{nullptr} {};
        Node(const T val) : value{val}, left{nullptr}, right{nullptr} {};
    } *root;
private:
    void make_insert(Node*&, const T) noexcept;
    T get_max_of(Node*) const noexcept;
    T get_min_of(Node*) const noexcept;
    bool search(const T, Node*) const noexcept;
    void preorder(Node*) const noexcept;
    void postorder(Node*) const noexcept;
    void inorder(Node*) const noexcept;
    void delete_tree(Node*&) const noexcept;
    void copy(Node*&, const Node*) noexcept;
public:
    bool contains(const T) const noexcept;
    T get_max() const noexcept;
    T get_min() const noexcept;
    void print_preorder() const noexcept;
    void print_postorder() const noexcept;
    void print_inorder() const noexcept;
    void print_levelorder() const noexcept;
    void clear() noexcept;
};

#include "BST.hpp"

#endif //BST_H