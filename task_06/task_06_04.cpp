// Дано множество целых чисел из [0..10^9] размера n.
// Используя алгоритм поиска k-ой порядковой статистики, требуется найти
// следующие параметры \
множества:
// 10%  перцентиль
// медиана
// 90%  перцентиль
// Реализуйте стратегию выбора опорного элемента “случайный элемент”. Функцию
// Partition \
реализуйте методом прохода двумя итераторами от конца массива к началу.

#include <iostream>

template <class Type=int>
struct DefaultComparator {
  bool operator()(const Type &l, const Type &r) { return l <= r; }
};

template <class T, class SortComparator = DefaultComparator<T>>
size_t partition(T *data, size_t start, size_t end, SortComparator comp) {
  int pivot = start + rand() % (end - start);
  std::swap(data[pivot], data[end - 1]);
  size_t i = start;
  while (i < end - 1 && comp(data[i], data[end - 1])) i++;
  size_t j = i;
  while (j < end - 1 && comp(data[end - 1], data[j])) j++;
  while (j != end - 1) {
    if (!comp(data[j], data[end - 1]))
      j++;
    else {
      std::swap(data[i], data[j]);
      i++;
      j++;
    }
  }
  std::swap(data[end - 1], data[i]);
  return i;
}

template <class T, class SortComparator=DefaultComparator<T>>
void kthElement(T *data, size_t size, size_t k, SortComparator comp) {
  int l = 0;
  int r = size;

  while (true) {
    int m = partition<T, SortComparator>(data, l, r, comp);
    if (m == k) {
      return;
    } else if (m < k) {
      l = m + 1;
    } else {
      r = m;
    }
  }
}

int main() {
  int length;
  std::cin >> length;
  int *array = new int[length];
  for (int i = 0; i < length; i++) {
    std::cin >> array[i];
  }
  size_t k;
  k = length * 10 / 100;
  DefaultComparator<> comp;
  kthElement(array, length, k, comp);
  std::cout << array[k] << std::endl;
  k = length / 2;
  kthElement(array, length, k, comp);
  std::cout << array[k] << std::endl;
  k = length * 90 / 100;
  kthElement(array, length, k, comp);
  std::cout << array[k] << std::endl;
  delete[] array;
  return 0;
}