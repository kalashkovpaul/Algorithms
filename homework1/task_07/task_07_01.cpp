// 7_1. MSD для строк.
// Дан массив строк. Количество строк не больше 105. Отсортировать массив
// методом поразрядной \
сортировки MSD по символам. Размер алфавита - 256 символов. Последний символ строки = ‘\0’

#include <cstdio>
#include <iostream>
#include <string>
    using std::string;

constexpr int initSize = 2;
constexpr int sizeIteration = 2;
constexpr int wrongIndex = -1;
constexpr int notFound = -1;

void msdSort(string strings[], int start, int end, int digit, int R) {
  if (end <= start || end - start <= 1) return;

  int size = end - start;
  int countersSize = R + 1;
  int *counters = new int[countersSize];
  int *oldCounters = new int[countersSize];

  for (int i = 0; i < countersSize; i++) {
    counters[i] = 0;
  }

  for (int i = start; i < end; i++) {
    counters[strings[i][digit]]++;
  }
  oldCounters[0] = counters[0];
  for (int i = 0; i < countersSize - 1; i++) {
    counters[i + 1] += counters[i];
    oldCounters[i + 1] = counters[i + 1];
  }
  string *auxStrings = new string[size];
  int auxIdx = 0;
  for (int arrIdx = end - 1; arrIdx >= start; arrIdx--) {
    auxIdx = arrIdx;
    if (strings[arrIdx].size() >= digit) {
      auxIdx = counters[strings[arrIdx][digit]] - 1;
      counters[strings[arrIdx][digit]]--;
    }
    auxStrings[auxIdx] = strings[arrIdx];
  }

  for (int i = start; i < end; i++) {
    strings[i] = auxStrings[i - start];
  }
  delete[] auxStrings;
  for (int i = 0; i < countersSize - 1; i++) {
    if (oldCounters[i] != oldCounters[i + 1] &&
        oldCounters[i] < oldCounters[i + 1] - 1)
      msdSort(strings, start + oldCounters[i], start + oldCounters[i + 1],
              digit + 1, R);
  }
  delete[] counters;
  delete[] oldCounters;
}

template <class Type>
struct DefaultComparator {
  bool operator()(const Type &l, const Type &r) { return l > r; }
};

template <class T = int, class Comparator = DefaultComparator<T>>
class Vector {
 private:
  size_t capacity;
  size_t length;

  Comparator comp;

  void expand() {
    T *newData = new T[length * sizeIteration];
    for (size_t i = 0; i < capacity; i++) newData[i] = data[i];
    delete[] data;
    data = newData;
    length *= sizeIteration;
  }

 public:
  T *data;
  Vector() {
    data = new T[initSize];
    capacity = 0;
    length = initSize;
  }

  Vector(const Vector &) = delete;
  Vector(Vector &&) = delete;

  Vector &operator=(const Vector &) = delete;
  Vector &operator=(const Vector &&) = delete;

  void append(T element) {
    if (capacity >= length) expand();
    data[capacity] = element;
    capacity++;
  }

  ~Vector() {
    delete[] data;
    capacity = 0;
    length = 0;
  }
  
  int count() { return capacity; }
};

int main(void) {
  Vector<string> array;
  string str;
  while (std::cin >> str) {
    array.append(str);
  }
  msdSort(array.data, 0, array.count(), 0, 256);
  for (int i = 0; i < array.count(); i++) {
    std::cout << array.data[i] << std::endl;
  }
  return 0;
}
