#include <iostream>
#include <vector>

void insertion_sort(std::vector<int>& container);
void swap(int&, int&);
int main() {

    std::vector<int> array{5,6,8,7,9,5,15,12,56,5,22,24,19,1};
    for (auto i : array) {
        std::cout << i << '|';
    }
    std::cout << std::endl;

    insertion_sort(array);

    for (auto i : array) {
        std::cout << i << '|';
    }
    std::cout << std::endl;

    return 0;
}

void insertion_sort(std::vector<int>& container) {
    for (int i = 1; i < container.size(); ++i) {
        int key = i;
        while (container[key - 1] > container[key] && key > 0) {
            swap(container[key - 1], container[key]);
            --key;
        }
    }
}

void swap(int& first, int& second) {
    int tmp = std::move(first);
    first = std::move(second);
    second = std::move(tmp);
}