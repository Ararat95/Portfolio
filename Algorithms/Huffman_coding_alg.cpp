#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

struct Huff_node {
    char data;
    int frequency;
    Huff_node* left;
    Huff_node* right;
    Huff_node(const char data, const int frequenty) : left{nullptr}, right{nullptr} {
        this->data = data;
        this->frequency = frequenty;
    }
};

struct compare {
    bool operator() (Huff_node* left, Huff_node* right) {
        return (left->frequency > right->frequency);
    }
};

template<typename Queue>
Huff_node* Huffman_alg(Queue& data);

template<typename Queue>
void count_text_data(Queue&, std::string&);

void store_code(Huff_node*, std::map<char, std::string>&, std::string);
std::string decode(Huff_node*, std::string&);
std::string get_code(std::map<char, std::string>&, std::string&);
void print(std::map<char, std::string>&);
void delete_nodes(Huff_node*);

int main() {

    std::string text{"geeksforgeeks"};
    std::priority_queue<std::pair<char,int>, std::vector<std::pair<char, int>>, std::greater<std::pair<char, int>>> data;
    count_text_data(data, text);
    
    std::map<char, std::string> code;

    Huff_node* root = Huffman_alg(data);
    store_code(root, code, "");
    std::string encoded = get_code(code, text);
    print(code);
    std::cout << "encoded code: " << encoded;
    std::string decoded = decode(root, encoded);
    std::cout << std::endl << decoded << std::endl;
    delete_nodes(root);

    return 0;
}



template<typename Queue>
void count_text_data(Queue& data, std::string& text) {
    std::vector<char> chars;
    for (int i = 0; i < text.size();) {
        int count = 0;
        if (std::find(chars.begin(), chars.end(), text[i]) == chars.end()) {
            chars.push_back(text[i]);
            for(int j = i; j < text.size(); ++j) {
                if (text[i] == text[j]) {
                    ++count;
                }
            }
            data.push({text[i], count});
            ++i;
        }
        else {
            ++i;
        }
    }
}

template <typename Queue>
Huff_node* Huffman_alg(Queue& data) {
    Huff_node *left, *right, *top;
    std::priority_queue<Huff_node*, std::vector<Huff_node*>, compare> pq;

    while (!data.empty()) {
        pq.push(new Huff_node(data.top().first, data.top().second));
        data.pop();
    }

    while (pq.size() != 1) {
        left = pq.top();
        pq.pop();

        right = pq.top();
        pq.pop();

        top = new Huff_node('#', left->frequency + right->frequency);
        top->left = left;
        top->right = right;
        pq.push(top);
        left = right = top = nullptr;
    }
    return pq.top();
}

void store_code(Huff_node* root, std::map<char, std::string>& map,  std::string code) {

    if (!root) {
        return;
    }
    if (root->data != '#') {
        map[root->data] = code;
    }    
    store_code(root->left, map, code + '0');
    store_code(root->right, map, code + '1');
}

std::string decode(Huff_node* root, std::string& code) {
    Huff_node* current = root;
    std::string decoded{""};
    for (int i = 0; i < code.size(); ++i) {
        if (code[i] == '0') {
            current = current->left;
        }
        else {
            current = current->right;
        }

        if (current->left == nullptr && current->right == nullptr) {
            decoded += current->data;
            current = root;
        }
    }
    
    return decoded;
}

std::string get_code(std::map<char, std::string>& map, std::string& text) {
    std::string code{""};

    for (auto& key : text) {
        code += map[key];
    }

    return code;
}

void print(std::map<char, std::string>& map) {
    for (auto key : map) {
        std::cout << key.first << " :: " << key.second << std::endl;
    }
}

void delete_nodes(Huff_node* root) {
    if (!root) {
        return;
    }
    delete_nodes(root->left);
    delete_nodes(root->right);
    delete root;
    root = nullptr;
}