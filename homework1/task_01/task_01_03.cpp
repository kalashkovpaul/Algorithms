// Задание 1, Вариант 3

// Если в числе содержится только один бит со значением 1, записать в выходной
// поток OK. Иначе записать FAIL.

// Необходимо использование битовых операций.
// Использование арифметических операций запрещено.

#include <iostream>

#define OK 0

int getOnesAmount(unsigned long long number) {
  int result = 0;
  while (number) {
    result += number & 1;
    number = number >> 1;
  }
  return result;
}

int main() {
  unsigned long long int number;
  std::cin >> number;
  int onesAmount = getOnesAmount(number);
  if (onesAmount == 1)
    std::cout << "OK" << std::endl;
  else
    std::cout << "FAIL" << std::endl;
  return OK;
}
