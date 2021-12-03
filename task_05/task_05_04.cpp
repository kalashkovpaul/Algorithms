// Во всех задачах данного раздела необходимо реализовать и использовать сортировку слиянием \
в виде шаблонной функции.
// Решение должно поддерживать передачу функции сравнения снаружи.
// На числовой прямой окрасили N отрезков. Известны координаты левого и правого
// концов каждого \
отрезка (Li и Ri). Найти сумму длин частей числовой прямой, окрашенных ровно в \
один слой.

#include <iostream>

typedef struct {
  int value;
  int diff;
} dot_t;

struct DotComparator {
  bool operator()(const dot_t& l, const dot_t& r) { return l.value < r.value; }
};

template <class Type>
struct DefaultComparator {
  bool operator()(const Type& l, const Type& r) { return l < r; }
};

template <class T, class Comparator=DefaultComparator<T>>
void merge(T array[], size_t left, size_t middle, size_t right, Comparator comp) {
  size_t leftSubArray = middle - left + 1;
  size_t rigthSubArray = right - middle;

  T* leftArray = new T[leftSubArray];
  T* rightArray = new T[rigthSubArray];

  for (size_t i = 0; i < leftSubArray; i++) leftArray[i] = array[left + i];
  for (size_t j = 0; j < rigthSubArray; j++)
    rightArray[j] = array[middle + 1 + j];

  size_t indexForLeftSubArray = 0;
  size_t indexForRigthSubArray = 0;
  size_t indexForMerged = left;

  while (indexForLeftSubArray < leftSubArray &&
         indexForRigthSubArray < rigthSubArray) {
    if (comp(leftArray[indexForLeftSubArray],
             rightArray[indexForRigthSubArray])) {
      array[indexForMerged] = leftArray[indexForLeftSubArray];
      indexForLeftSubArray++;
    } else {
      array[indexForMerged] = rightArray[indexForRigthSubArray];
      indexForRigthSubArray++;
    }
    indexForMerged++;
  }

  while (indexForLeftSubArray < leftSubArray) {
    array[indexForMerged] = leftArray[indexForLeftSubArray];
    indexForLeftSubArray++;
    indexForMerged++;
  }

  while (indexForRigthSubArray < rigthSubArray) {
    array[indexForMerged] = rightArray[indexForRigthSubArray];
    indexForRigthSubArray++;
    indexForMerged++;
  }
}

template <class T, class Comparator=DefaultComparator<T>>
void mergeSort(T array[], size_t start, size_t end, Comparator comp) {
  if (start >= end) return;

  size_t middle = start + (end - start) / 2;
  mergeSort<T, Comparator>(array, start, middle, comp);
  mergeSort<T, Comparator>(array, middle + 1, end, comp);
  merge<T, Comparator>(array, start, middle, end, comp);
}

int main() {
  int segmentsAmount;
  int dotsAmount;
  int value;

  std::cin >> segmentsAmount;
  dotsAmount = segmentsAmount * 2;
  dot_t* dots = new dot_t[dotsAmount];
  for (int i = 0; i < segmentsAmount; i++) {
    std::cin >> value;
    dots[i * 2].value = value;
    dots[i * 2].diff = 1;
    std::cin >> value;
    dots[i * 2 + 1].value = value;
    dots[i * 2 + 1].diff = -1;
  }
  DotComparator comparator;
  mergeSort<dot_t, DotComparator>(dots, 0, dotsAmount - 1, comparator);

  int length = 0;
  int thickness = 0;
  for (int i = 0; i < dotsAmount - 1; i++) {
    thickness += dots[i].diff;
    if (thickness == 1) length += (dots[i + 1].value - dots[i].value);
  }
  std::cout << length << std::endl;
  return 0;
}
