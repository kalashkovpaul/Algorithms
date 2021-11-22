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
class Heap {
 private:
  // T *data;
  size_t capacity;
  size_t length;

  Comparator comp;

  void siftUp(size_t idx);
  void siftDown(size_t idx);

  void heapify(size_t i) {
    size_t leftChild;
    size_t rightChild;
    size_t biggestChild;
    while (true) {
      leftChild = 2 * i + 1;
      rightChild = 2 * i + 2;
      biggestChild = i;
      if (leftChild < capacity && comp(data[biggestChild], data[leftChild])) {
        biggestChild = leftChild;
      }
      if (rightChild < capacity && comp(data[biggestChild], data[rightChild])) {
        biggestChild = rightChild;
      }
      if (biggestChild == i) {
        break;
      }
      T t = data[i];
      data[i] = data[biggestChild];
      data[biggestChild] = t;
      i = biggestChild;
    }
  }

  void expand() {
    T *newData = new T[length * sizeIteration];
    for (size_t i = 0; i < capacity; i++) newData[i] = data[i];
    delete[] data;
    data = newData;
    length *= sizeIteration;
  }

  template <class SortComparator = DefaultComparator<T>>
  int Partition(int start, int end, SortComparator comp = SortComparator()) {
    int pivot = end;
    int j = start;
    for (int i = start; i < end; ++i) {
      if (comp(data[i], data[pivot])) {
        std::swap(data[i], data[j]);
        ++j;
      }
    }
    std::swap(data[j], data[pivot]);
    return j;
  }

  template <class SortComparator = Comparator>
  void quickSort(int start, int end, SortComparator comp = SortComparator()) {
    if (start < end) {
      int p = Partition(start, end, comp);
      quickSort(start, p - 1);
      quickSort(p + 1, end);
    }
  }

  void set(int index, T element) {
    if (index >= 0 && index < capacity) {
      data[index] = element;
    }
  }

  void insert(int index, T element) {
    if (index >= 0 && index <= capacity) {
      if (index == capacity)
        append(element);
      else {
        append(data[capacity - 1]);
        for (int i = capacity - 1; i > index; i--) {
          data[i] = data[i - 1];
        }
        data[index] = element;
      }
    }
  }

  int index(T element) {
    int index = 0;
    if (capacity == 0)
      index = notFound;
    else {
      while (index < capacity && data[index] != element) index++;
      if (index == capacity) index = notFound;
    }
    return index;
  }

  template <class SortComparator = DefaultComparator<T>>
  void sort(int l, int r, SortComparator comp = SortComparator()) {
    if (l < 0 || r < 0 || l > r || l >= length || r >= length) return;
    quickSort(l, r, comp);
  }

  void remove(int index) {
    if (index >= 0 && index < capacity) {
      if (capacity == 1)
        clear();
      else if (index != capacity - 1) {
        for (int i = index; i < capacity - 1; i++) data[i] = data[i + 1];
        capacity--;
      } else {
        capacity--;
      }
    }
  }

  void print() {
    if (capacity == 0) {
      std::cout << "Empty\n";
    }
    for (int i = 0; i < capacity; i++) std::cout << data[i] << " ";
    std::cout << std::endl;
  }

 public:
  T *data;
  Heap() {
    data = new T[initSize];
    capacity = 0;
    length = initSize;
  }

  Heap(const Heap &) = delete;
  Heap(Heap &&) = delete;

  Heap &operator=(const Heap &) = delete;
  Heap &operator=(const Heap &&) = delete;

  const T &top() const {
    if (capacity > 0)
      return data[0];
    else
      return notFound;
  }

  T pop() {
    T result;
    if (capacity > 0) {
      result = data[0];
      data[0] = data[capacity - 1];
      heapify(0);
      remove(capacity - 1);
    } else {
      result = nullptr;
    }
    return result;
  }

  void push(const T element) {
    append(element);
    int i = capacity - 1;
    int parent = (i - 1) / 2;
    while (i > 0 && comp(data[parent], data[i])) {
      T t = data[i];
      data[i] = data[parent];
      data[parent] = t;
      i = parent;
      parent = (i - 1) / 2;
    }
  }

  int get(T index) {
    int element = 0;
    if (index >= 0 && index < capacity) {
      element = data[index];
    } else {
      element = wrongIndex;
    }
    return element;
  }

  void append(T element) {
    if (capacity >= length) expand();
    data[capacity] = element;
    capacity++;
  }

  ~Heap() {
    delete[] data;
    capacity = 0;
    length = 0;
  }

  void clear() {
    T *newData = new T[initSize];
    delete[] data;
    data = newData;
    capacity = 0;
    length = 0;
  }

  int count() { return capacity; }
};

int main(void) {
  Heap<string> array;
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
