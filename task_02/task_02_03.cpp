/*
Дано число N < 10^6 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел 
K добавляется в правое поддерево root; иначе в левое поддерево root.
Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения
снаружи.
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
class BST {
    struct bstNode {
        bstNode *left;
        bstNode *right;
        Key key;
        
        bstNode(const Key& key): left(nullptr), right(nullptr), key(key) {
        }
    };
public:
    BST(Comparator comp = Comparator()): root(nullptr), comp(comp) {
    }
    
    ~BST() {
        while (!queue.empty())
            queue.pop();
        if (root != nullptr)
        {
            queue.push(root);
            bstNode *deleted = nullptr;
            while (!queue.empty())
            {
                deleted = queue.front();
                queue.pop();
                if (deleted)
                {
                    queue.push(deleted->left);
                    queue.push(deleted->right);
                    delete deleted;
                }
            }
        }
    }

    void insert(Key newKey) {
        bstNode *newNode = new bstNode(newKey);
        while (!queue.empty())
            queue.pop();
        if (root != nullptr)
        {
            queue.push(root);
            bstNode *fatherToNew = nullptr;
            while (!queue.empty())
            {
                fatherToNew = queue.front();
                queue.pop();
                if (comp(newKey, fatherToNew->key) >= 0)
                {
                    if (fatherToNew->right != nullptr)
                        queue.push(fatherToNew->right);
                    else
                        break;
                }
                else if (comp(newKey, fatherToNew->key) < 0)
                {
                    if (fatherToNew->left != nullptr)
                        queue.push(fatherToNew->left);
                    else
                        break;
                }
            }
            if (comp(newKey, fatherToNew->key) >= 0)
                fatherToNew->right = newNode;
            else
                fatherToNew->left = newNode;
        }
        else
            root = newNode;
    }

    void preOrder()
    {
        std::stack<bstNode *> first;
        std::stack<bstNode *> second;
        bstNode *current = nullptr;
        if (root != nullptr)
        {
            first.push(root);
            while(!first.empty())
            {
                current = first.top();
                first.pop();
                second.push(current);
                if (current->left != nullptr)
                    first.push(current->left);
                if (current->right != nullptr)
                    first.push(current->right);
            }
            while (!second.empty())
            {
                current = second.top();
                second.pop();
                std::cout << current->key << " ";
            }
            std::cout << std::endl;
        }
    }


private:
    bstNode *root;
    Comparator comp;
    std::queue<bstNode *> queue;
};

int main()
{
    BST<int> bst;
    int numbersAmount = 0;
    int value = 0;
    std::cin >> numbersAmount;
    for (int i = 0; i < numbersAmount; i++)
    {
        std::cin >> value;
        bst.insert(value);
    }
    bst.preOrder();
    return 0;
}