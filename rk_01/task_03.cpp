/*
Задано N точек на плоскости. Указать (N-1)-звенную несамопересекающуюся замкнутую ломаную, проходящую через все эти точки.
Предполагается, что никакие три точки не лежат на одной прямой.
Стройте ломаную от точки, имеющей наименьшую координату x. Если таких точек несколько, то используйте точку с наименьшей координатой y. Точки на ломаной расположите в порядке убывания углов лучей от начальной точки до всех остальных точек.
Для сортировки точек реализуйте алгоритм сортировки вставками.
*/

#include <iostream>
#define OK 0

typedef struct {
    int x;
    int y;
} dot_t;

void sort(dot_t *array, int length) {
    for (int i = 0; i < length; i++)
        for (int j = i; j > 0 && (array[j - 1].x >= array[j].x && array[j - 1].y > array[j].y); j--) {
            dot_t t = array[j - 1];
            array[j - 1] = array[j];
            array[j] = t;
        }
}

int isAngleBigger(dot_t left, dot_t rigth, dot_t first) {
    double tanLeft = ((double)(left.y - first.y) / (left.x - first.x));
    double tanRigth = ((double)(rigth.y - first.y) / (rigth.x - first.x));
    if (tanLeft > 0 && tanRigth > 0) {
        if (left.x < 0 && rigth.x < 0) {
            return tanLeft > tanRigth;
        }
        // остальные случаи не успел
    }
}

void sortByAngles(dot_t*array, dot_t firstDot, int length) {
    for (int i = 0; i < length; i++)
        for (int j = i; j > 0 && (isAngleBigger(array[j - 1], array[j], firstDot)); j--) {
            dot_t t = array[j - 1];
            array[j - 1] = array[j];
            array[j] = t;
        }
}


int main() {
    int n = 0;
    std::cin >> n;
    dot_t *array = new dot_t[n];
    dot_t *result = new dot_t[n - 1];
    for (int i = 0; i < n; i++) {
        std::cin >> array[i].x;
        std::cin >> array[i].y;
    }
    sort(array, n);
    result[0] = array[0];
    // остальное не успел, но может хоть сколько баллов будет
    delete[] array;
    delete[] result;
    return OK;
}