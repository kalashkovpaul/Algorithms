/*
Требование для всех вариантов Задачи 4
Решение должно поддерживать передачу функции сравнения снаружи.

4_2. Порядковые статистики. Дано число N и N строк. Каждая строка содержит команду 
добавления или удаления натуральных чисел, а также запрос на получение k-ой порядковой 
статистики. Команда добавления числа A задается положительным числом A, команда удаления 
числа A задается отрицательным числом “-A”. Запрос на получение k-ой порядковой статистики 
задается числом k. 
Требования: скорость выполнения запроса - O(log n).

*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

template <class T>
struct DefaultComparator {
    int operator() (const T& l, const T& r) {
        if (l < r)
            return -1;
        else if (l > r)
            return 1;
        else
            return 0;
    }
};

template <class Key, class Comparator=DefaultComparator<Key>>
class AVLTree {
    struct avlNode {
        avlNode *left;
        avlNode *right;
        Key key;
        uint8_t height;

        avlNode(const Key& key): left(nullptr), right(nullptr), key(key), height(1) {
        }
        ~avlNode()
        {
            delete left;
            delete right;
        }
    };
public:
    AVLTree(Comparator comp = Comparator()): root(nullptr), comp(comp) {
    }
    
    ~AVLTree()
    {
        delete root;
    }

    void insert(const Key& newKey) {
        root = insertInternal(newKey, root);
    }

    void erase(const Key& key) {

    }


private:
    avlNode *root;
    Comparator comp;
    
    avlNode *insertInternal(const Key& key, avlNode *node)
    {
        if (!node)
            return new avlNode(key);
        int cmpRes = comp(key, node->key);
        if (cmpRes == -1)
            node->left = insertInternal(key, node->left);
        else
            node->right = insertInternal(key, node->right);
        return balance(node);
    }

    uint8_t height(avlNode *node)
    {
        if (!node)
            return 0;
        return node->height;
    }

    void fixHeight(avlNode *node)
    {
        if (!node)
            return;
        node->height = std::max(height(node->left), height(node->right));
    }

    uint8_t bfactor(avlNode *node)
    {
        return heigh(node->right) - height(node->left);
    }

    avlNode *rotateLeft(avlNode *node)
    {    
        avlNode *rotated = node->right;
        node->right = rotated->left;
        rotated->left = node;
        fixHeight(node);
        fixHeight(rotated);
        return rotated;
    }

    avlNode *rotateRight(avlNode *node)
    {
        avlNode *rotated = node->left;
        node->left = rotated->right;
        rotated->right = node;
        fixHeight(node);
        fixHeight(rotated);
        return rotated;
    }

    avlNode *balance(avlNode *node)
    {
        fixHeight(node);
        uint8_t bf = bfactor(node);
        if (bf == 2) {
            if (bfactor(node->right) < 0)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        else if (bf == -2) {
            if (bfactor(node->left) > 0)
                node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        return node;
    }
};

int main()
{
    return 0;
}