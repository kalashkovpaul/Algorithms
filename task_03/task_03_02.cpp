// Формат входных данных.
// В первой строке количество команд n. n ≤ 1000000.
// Каждая команда задаётся как 2 целых числа: a b.
// a = 1 - push front
// a = 2 - pop front
// a = 3 - push back
// a = 4 - pop back
// Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
// Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
// Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается “-1”. 
// Формат выходных данных.
// Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.

// Реализовать дек с динамическим зацикленным буфером.

#include <iostream>

#define OK 0
#define INIT_SIZE 2
#define SIZE_ITERATION 2
#define EMPTY_DEQUE -1

class Deque {
public:
    Deque() {
        start = new int[INIT_SIZE];
        length = 0;
        head = start;
        tail = head;
        isEmpty = true;
    }

    ~Deque() {
        delete[] start;
        length = 0;
    }

    void pushFront(int value) {
        if (length == 0) {
            *head = value;
            length = INIT_SIZE;
        }
        else if (isEmpty) {
            *head = value;
        }
        else {
            head++;
            if (head >= start + length || head == tail) {
                if (tail != start && tail != head) {
                    head = start;
                    *head = value;
                }
                else {
                    int *t = new int[length * SIZE_ITERATION];
                    int *pointer;
                    int i = 0;
                    
                    if (tail < head)
                        pointer = tail;
                    else
                        pointer = start;
                    while (pointer < head && i < length * SIZE_ITERATION && pointer < start + length) {
                        t[i++] = *(pointer++);
                    }
                    
                    if (tail >= head) {
                        int j = length * SIZE_ITERATION - 1;
                        pointer = start + length - 1;
                        while (pointer >= tail && j > 0 && pointer >= start) {
                            t[j--] = *(pointer--);
                        }
                        tail = t + j + 1;
                    }
                    else {
                        tail = t;
                    }
                    head = t + i - 1;
                    delete[] start;
                    start = t;
                    head++;
                    *head = value;
                    length *= SIZE_ITERATION;
                }
            }
            else {
                *head = value;
            }
        }
        isEmpty = 0;
    }

    int popFront() {
        int value;
        if (head != tail) {
            value = *head;
            head--;
            if (head < start)
                head = start + length - 1;
        }
        else if (!isEmpty) {
            value = *head;
            isEmpty = true;
        }
        else {
            value = EMPTY_DEQUE;
        }
        return value;
    }

    void pushBack(int value) {
        if (length == 0) {
            *tail = value;
            length = INIT_SIZE;
        }
        else if (isEmpty) {
            *head = value;
        }   
        else {
            tail--;
            if (tail < start || tail == head) {
                if (head != start + length - 1 && tail != head) {
                    tail = start + length - 1;
                    *tail = value;
                }
                else {
                    int *t = new int[length * SIZE_ITERATION];
                    int *pointer;
                    int i = 0;
                    
                    if (tail < head)
                        pointer = tail;
                    else
                        pointer = start;
                    while (pointer < head || pointer == start && i < length * SIZE_ITERATION && \
                    pointer < start + length) {
                        t[i++] = *(pointer++);
                    }
                    
                    if (tail >= head) {
                        int j = length * SIZE_ITERATION - 1;
                        pointer = start + length - 1;
                        while (pointer >= tail && pointer != head && j > 0 && pointer >= start) {
                            t[j--] = *(pointer--);
                        }
                        tail = t + j + 1;
                    }   
                    else {
                        tail = t;
                    }
                    head = t + i - 1;
                    delete[] start;
                    start = t;
                    tail--;
                    *tail = value;
                    length *= SIZE_ITERATION;                   
                }
            }
            else {
                *tail = value;
            }
        }
        isEmpty = 0;
    }

    int popBack() {
        int value;
        if (tail == head) {
            if (isEmpty)
                value = EMPTY_DEQUE;
            else {
                isEmpty = 1;
                value = *tail;
            }
        }
        else {
            value = *tail;
            tail++;
            if (tail >= start + length)
                tail = start;
        }
        return value;
    }

private:
    int *head;
    int *tail;
    int *start;
    int length;
    bool isEmpty;
};

int main() {
    int commandAmounts = 0;
    std::cin >> commandAmounts;
    Deque deque;
    bool isEverythingCorrect = true;
    for (int i = 0; i < commandAmounts; i++) {
        int command = 0;
        int value = 0;
        int result = 0;
        std::cin >> command;
        switch (command)
        {
        case 1:
            std::cin >> value;
            deque.pushFront(value);
            break;
        case 2:
            std::cin >> result; 
            value = deque.popFront();
            if (value != result)
                isEverythingCorrect = false;
            break;
        case 3:
            std::cin >> value;
            deque.pushBack(value);
            break;
        case 4:
            std::cin >> result;
            value = deque.popBack();
            if (value != result)
                isEverythingCorrect = false;
            break;
        default:
            break;
        }
    }
    if (isEverythingCorrect)
        std::cout << "YES\n";
    else
        std::cout << "NO\n";
    //delete deque;
    return OK;
}