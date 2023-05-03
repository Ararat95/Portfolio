#include "BST.h"

template <typename T>
BST<T>::BST(const T& val) {
    this->root = new Node(val);
}

template <typename T>
BST<T>::BST(const BST& src) {
    if (!src.root) {
        this->root = nullptr;
        return;
    }
    copy(this->root, src.root);
}

template <typename T>
void BST<T>::copy(Node*& dest, const Node* src) noexcept {
    if (!src) {
        return;
    }
    dest = new Node(src->value);
    copy(dest->left, src->left);
    copy(dest->right, src->right);
}

template <typename T>
BST<T>::BST(BST<T>&& src) {
    if (!src.root) {
        this->root = nullptr;
        return;
    }
    this->root = std::move(src.root);
    src.root = nullptr;
}

template <typename T>
BST<T>::~BST() {
    if (this->root) {
        clear();
    }
}

template <typename T>
BST<T> BST<T>::operator= (const BST<T>& rhs) {
    if (!rhs.root) {
        clear();
        this->root = nullptr;
        return *this;
    }
    std::queue<Node*> order;
    order.push(rhs.root);
    while (!order.empty()) {
        Node* curr = order.front();
        insert(curr->value);
        order.pop();
        if (curr->left) {
            order.push(curr->left);
        }
        if (curr->right) {
            order.push(curr->right);
        }
    }
    return *this;
}

template <typename T>
BST<T> BST<T>::operator= (BST<T>&& rhs) {
    clear();
    this->root = std::move(rhs.root);
    rhs.root = nullptr;
}

template <typename T>
void BST<T>::insert(const T val) noexcept {
    if (!this->root) {
        this->root = new Node(val);
        return;
    }
    make_insert(this->root, val);
}

template <typename T>
void BST<T>::make_insert(Node*& node, const T val) noexcept {
    if (val < node->value) {
        if (node->left) {
            make_insert(node->left, val);
            return;
        }
        node->left = new Node(val);
        return;
    }
    else if (val > node->value) {
        if (node->right) {
            make_insert(node->right, val);
            return;
        }
        node->right = new Node(val);
        return;
    }
    else {
        std::cout << "[WARNING]: Value exists!! " << std::endl; 
    }
}

template <typename T>
void BST<T>::remove(const T val) noexcept {
    if (!this->root) {
        std::cout << "[WARNING]: Tree is empty!! " << std::endl;
        return;
    }
    Node* curr = this->root;
    Node* parent = nullptr;
    while (curr) {
        if (val > curr->value) {
            parent = curr;
            curr = curr->right;
        }
        else if (val < curr->value) {
            parent = curr;
            curr = curr->left;
        }
        else {
            if (!curr->left && !curr->right) {
                if (!parent) {
                    clear();
                    break;
                }
                delete curr;
                (parent->value > val ? parent->left : parent->right) = nullptr;
                break;
            }
            else if (curr->left && curr->right) {
                T successor = get_min_of(curr->right);
                remove(successor);
                curr->value = successor;
                break;
            }
            else {
                if (curr->left) {
                    T successor = get_min_of(curr->left);
                    remove(successor);
                    curr->value = successor;
                    break;
                }
                else if (curr->right) {
                    T successor = get_min_of(curr->right);
                    remove(successor);
                    curr->value = successor;
                    break;
                }
            }
        }
    }
}

template <typename T>
T BST<T>::get_min() const noexcept {
    if (!this->root) {
        return T(0);
    }
    return get_min_of(this->root);
}

template <typename T>
T BST<T>::get_max() const noexcept {
    if(!this->root) {
        return T(0);
    }
    return get_max_of(this->root);
}

template <typename T>
T BST<T>::get_min_of(Node* node) const noexcept {
    if (!node->left) {
        return node->value;
    }
    return get_min_of(node->left);
}

template <typename T>
T BST<T>::get_max_of(Node* node) const noexcept {
    if(!node->right) {
        return node->value;
    }
    return get_max_of(node->right);
}

template <typename T>
bool BST<T>::contains(const T value) const noexcept {
    if (!this->root) {
        return 0;
    }
    return search(value, this->root);
}

template <typename T>
bool BST<T>::search(const T val, Node* node) const noexcept {
    if (!node) {
        return 0;
    }
    if (val == node->value) {
        return 1;
    }
    return val < node->value ? contains(val, node->left) : contains(val, node->right);
}

template <typename T>
void BST<T>::clear() noexcept {
    if (!this->root) {
        return;
    }
    delete_tree(this->root);
}

template <typename T>
void BST<T>::delete_tree(Node*& node) const noexcept {
    if (!node) {
        return;
    }
    delete_tree(node->left);
    delete_tree(node->right);

    delete node;
    node = nullptr;
}

template <typename T>
void BST<T>::print_inorder() const noexcept {
    inorder(this->root);
}

template <typename T>
void BST<T>::print_postorder() const noexcept {
    postorder(this->root);
}

template <typename T>
void BST<T>::print_preorder() const noexcept {
    preorder(this->root);
}

template <typename T>
void BST<T>::preorder(Node* node) const noexcept {
    if (!node) {
        return;
    }
    std::cout << node->value << ',';
    preorder(node->left);
    preorder(node->right);
}

template <typename T>
void BST<T>::postorder(Node* node) const noexcept {
    if (!node) {
        return;
    }
    postorder(node->left);
    postorder(node->right);
    std::cout << node->value << ',';
}

template <typename T>
void BST<T>::inorder(Node* node) const noexcept {
    if (!node) {
        return;
    }
    inorder(node->left);
    std::cout << node->value << ',';
    inorder(node->right);
}

template <typename T>
void BST<T>::print_levelorder() const noexcept {
    std::queue<Node*> order;
    order.push(this->root);
    while (!order.empty()) {
        Node* curr = order.front();
        std::cout << curr->value << ',';
        order.pop();
        if (curr->left) {
            order.push(curr->left);
        }
        if (curr->right) {
            order.push(curr->right);
        }
    }
    std::cout << std::endl;
}