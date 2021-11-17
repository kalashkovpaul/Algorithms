// Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию. \
A[0..n-1] и B[0..m-1]. n » m. Найдите их пересечение.\
Требуемое время работы: O(m * log k), где k - позиция элемента B[m-1] в массиве A.. \
В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом \
поиска элемента B[i-1]. n, k ≤ 10000.

#include <iostream>
#define OK 0
#define NOT_FOUND -1

typedef struct {
  int length;
  int *array;
} array_t;

void scanArray(array_t *array) {
  int *data = new int[array->length];
  for (int i = 0; i < array->length; i++) {
    std::cin >> data[i];
  }
  array->array = data;
}

void printArray(array_t *array) {
  for (int i = 0; i < array->length; i++) std::cout << array->array[i] << ' ';
}

void freeArray(array_t *array) {
  delete[] array->array;
  array->array = nullptr;
  array->length = 0;
}

void findLimitsForBinary(array_t *array, int element, int *low, int *high) {
  int i = 1;
  *low = 0;
  while (i - 1 < array->length && array->array[i - 1] <= element) {
    i *= 2;
  }
  if (i - 1 < array->length) {
    *high = i - 1;
    *low = i / 2 - 1;
  } else {
    *low = i / 2 - 1;
    *high = array->length - 1;
  }
}

int binarySearch(array_t *array, int left, int right, int element) {
  if (right >= left) {
    int middle = left + (right - left) / 2;
    if (array->array[middle] == element) return middle;
    if (array->array[middle] > element)
      return binarySearch(array, left, middle - 1, element);
    return binarySearch(array, middle + 1, right, element);
  }
  return NOT_FOUND;
}

void findIntersection(array_t *firstArray, array_t *secondArray,
                      array_t *resultArray) {
  int leftBinary = 0, rightBinary = 0;
  int index = 0;
  resultArray->length = 0;
  findLimitsForBinary(firstArray, secondArray->array[0], &leftBinary,
                      &rightBinary);
  index =
      binarySearch(firstArray, leftBinary, rightBinary, secondArray->array[0]);
  if (index != NOT_FOUND) {
    resultArray->array[0] = firstArray->array[index];
    resultArray->length += 1;
    leftBinary = index;
  }
  int i = 1;
  while (firstArray->array[firstArray->length - 1] >= secondArray->array[i] &&
         i < secondArray->length) {
    int high = leftBinary + 1;
    while (high - 1 < firstArray->length &&
           firstArray->array[high - 1] <= secondArray->array[i])
      high *= 2;
    if (high - 1 < firstArray->length) {
      rightBinary = high - 1;
      leftBinary = high / 2 - 1;
    } else {
      leftBinary = high / 2 - 1;
      rightBinary = firstArray->length - 1;
    }
    index = binarySearch(firstArray, leftBinary, rightBinary,
                         secondArray->array[i]);
    if (index != NOT_FOUND) {
      resultArray->array[resultArray->length] = firstArray->array[index];
      resultArray->length += 1;
      leftBinary = index;
    }
    i++;
  }
}

int main() {
  int n = 0, m = 0;
  std::cin >> n >> m;

  array_t firstArray = {0};
  array_t secondArray = {0};
  array_t resultArray = {0};

  firstArray.length = n;
  secondArray.length = m;
  resultArray.array = new int[m];
  resultArray.length = 0;

  scanArray(&firstArray);
  scanArray(&secondArray);

  findIntersection(&firstArray, &secondArray, &resultArray);

  printArray(&resultArray);

  freeArray(&firstArray);
  freeArray(&secondArray);
  freeArray(&resultArray);

  return OK;
}