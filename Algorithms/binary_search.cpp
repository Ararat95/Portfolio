#include <iostream>
#include <vector>

int binary_search(const std::vector<int>& container, int begin, int end, int key);

int main() {

    std::vector<int> array {1,2,3,4,5,6,7,8,9,10,11,22,33,44,55,66,77,88,99};

    int key;
    std::cin >> key;
    std::cout << "key found : " << binary_search(array, 0, array.size() - 1, key) << std::endl;

    return 0;
}

int binary_search(const std::vector<int>& container, int begin, int end, int key) {

    int middle = begin + (end - begin) / 2;
    if (begin > end) {
        return -1;
    }
    if (container[middle] == key) {
        return middle;
    }
    else if (container[middle] > key) {
        return binary_search(container, begin, middle - 1, key);
    }
    else {
        return binary_search(container, middle + 1, end, key);
    }
}