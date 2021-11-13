// Дан массив, который получен путем нескольких циклических сдвигов \
исходного отсортированного массива. Нужно найти индекс элемента, с которого начинался \
исходный массив

#include <iostream>

#define OK 0

int main() {
    int n = 0;
    std::cin >> n;
    int *array = new int[n];
    int start = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> array[i];
    }
    for (int j = 1; j < n; j++) {
        if (array[j] < array[j - 1])
            start = j;
    }
    std::cout << start;
    delete[] array;
    return OK;
}