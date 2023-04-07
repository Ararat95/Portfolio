#include <iostream>
#include <vector>

void quick_sort(std::vector<int>& container, int begin, int end);
int partition(std::vector<int>& container, int begin, int end);

int main() {

    std::vector<int> array{5,6,8,7,9,5,15,12,56,5,22,24,19,1};
    for (auto i : array) {
        std::cout << i << '|';
    }
    std::cout << std::endl;

    quick_sort(array, 0, array.size() - 1);

    for (auto i : array) {
        std::cout << i << '|';
    }
    std::cout << std::endl;


    return 0;
}


void quick_sort(std::vector<int>& container, int begin, int end) {
    if (begin > end) {
        return;
    }
    int pivot = partition(container, begin, end);
    quick_sort(container, begin, pivot - 1);
    quick_sort(container, pivot + 1, end);
}

int partition(std::vector<int>& container, int begin, int end) {
    int pivotIndex = begin;
    int pivot = container[begin];

    for (int i = pivotIndex + 1; i <= end; ++i) {
        if (container[i] <= pivot) {
            ++pivotIndex;
        }
    }

    std::swap(container[begin], container[pivotIndex]);

    for (int i = begin, j = end; i < pivotIndex && pivotIndex < j;) {
        while(container[i] <= pivot) {
            ++i;
        }
        while(container[j] > pivot) {
            --j;
        }
        if (i < pivotIndex && j > pivotIndex) {
            std::swap(container[i++], container[j--]);
        }
    }
    return pivotIndex;
}