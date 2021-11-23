/*
Решение всех задач данного раздела предполагает использование кучи,
реализованной в виде шаблонного класса. Решение должно поддерживать передачу
функции сравнения снаружи. Куча должна быть динамической.

Формат входных данных: Сначала вводится количество массивов K. Затем по очереди
размер каждого массива и элементы массива. Каждый массив упорядочен по
возрастанию. Формат выходных данных: Итоговый отсортированный массив.
*/

#include <iostream>
constexpr int initSize = 2;
constexpr int sizeIteration = 2;
constexpr int wrongIndex = -1;
constexpr int notFound = -1;

template <class Type>
struct DefaultComparator {
  bool operator()(const Type &l, const Type &r) { return l > r; }
};

typedef struct {
  int *data;
  int currentIndex;
  int length;
} array_t;

struct ArrayComparator {
  bool operator()(const array_t *l, const array_t *r) {
    return l->data[l->currentIndex] > r->data[r->currentIndex];
  }
};

template <class T = int, class Comparator = DefaultComparator<T>>
class Heap {
 private:
  T *data;
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

  void append(T element) {
    if (capacity >= length) expand();
    data[capacity] = element;
    capacity++;
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

  void clear() {
    T *newData = new T[initSize];
    delete[] data;
    data = newData;
    capacity = 0;
    length = 0;
  }

 public:
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

  ~Heap() {
    delete[] data;
    capacity = 0;
    length = 0;
  }
};

int main() {
  int arraysAmount;
  int arrayLength;
  int totalLength = 0;
  int element;
  std::cin >> arraysAmount;
  array_t **arrays = new array_t *[arraysAmount];
  for (int i = 0; i < arraysAmount; i++) arrays[i] = new array_t;

  for (int i = 0; i < arraysAmount; i++) {
    std::cin >> arrayLength;
    totalLength += arrayLength;
    arrays[i]->length = arrayLength;
    arrays[i]->currentIndex = 0;
    arrays[i]->data = new int[arrayLength];
    for (int j = 0; j < arrays[i]->length; j++) {
      std::cin >> element;
      arrays[i]->data[j] = element;
    }
  }

  int *totalArray = new int[totalLength];
  Heap<array_t *, ArrayComparator> heap;

  array_t *temp;

  for (int i = 0; i < arraysAmount; i++) heap.push(arrays[i]);
  for (int i = 0; i < totalLength; i++) {
    temp = heap.pop();
    totalArray[i] = temp->data[temp->currentIndex];
    temp->currentIndex++;
    if (temp->currentIndex != temp->length) heap.push(temp);
  }
  for (int i = 0; i < totalLength; i++) std::cout << totalArray[i] << " ";
  std::cout << "\n";

  for (int i = 0; i < arraysAmount; i++) {
    delete[] arrays[i]->data;
    delete[] arrays[i];
  }
  delete[] arrays;
  delete totalArray;
  return 0;
}