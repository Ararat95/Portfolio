#include <iostream>

void selection_sort(int*&, const int);
void swap(int&, int&);

int main() {

    int size = 10;
    int* array = new int[size]{9,5,8,5,6,4,5,2,6,9};
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << '|';
    }
    std::cout << std::endl;

    selection_sort(array, size);
    
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << '|';
    }
    std::cout << std::endl;

    delete[] array;

    return 0;
}

void selection_sort(int*& array, const int size) {

    int min_idx;
    for (int i = 0; i < size; ++i) {
        min_idx = i;
        for (int j = i + 1; j < size; ++j) {
           min_idx = array[min_idx] > array[j] ? j : min_idx;
        }
        if (min_idx != i) {
            swap(array[min_idx], array[i]);
        }
    }
}

void swap(int& first, int& second) {
    int tmp = first;
    first = second;
    second = tmp;
}