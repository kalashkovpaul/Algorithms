/*
Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой 
адресацией. Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом 
Горнера.
Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении 
элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, удаления строки 
из множества и проверки принадлежности данной строки множеству.

1_1. Для разрешения коллизий используйте квадратичное пробирование. i-ая проба
g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
*/

#include <iostream>
#include <vector>

size_t strHash(const std::string& data)
{
    size_t hash = 0;
    size_t simple = 19;
    for (char i : data)
        hash = hash * simple + i;
    return hash;
}

template <class T>
struct Hasher {
    size_t operator()(const T& key) const
    {
        return key;
    }
};

template <>
struct Hasher<std::string> {
    size_t operator()(const std::string& key) const
    {
        return strHash(key);
    }
};

struct ExampleStruct {
    std::string str;
};

template <>
struct Hasher<ExampleStruct> {
    size_t operator()(const ExampleStruct& key) const
    {
        return strHash(key.str);
    }
};

template <class T>
struct DefaultEqual {
    bool operator()(const T& l, const T& r) const
    {
        return l == r;
    }
};

template <class Key, class Equal = DefaultEqual<Key>, class Hash = Hasher<Key>>
class HashSet {
public:
    HashSet()
    {
        HashElement newElement = HashElement();
        std::vector<HashElement> tmp(initialSize, newElement);
        buckets = tmp;
        hash = Hash();
        equal = Equal();
        itemsCount = 0;
    }

    HashSet(const HashSet&) = delete;
    HashSet& operator=(const HashSet&) = delete;

    ~HashSet() = default;

    bool add(const Key& key)
    {
        if (has(key)) {
            return false;
        }
        if (itemsCount * 100 > buckets.size() * maxLoadFactor)
            grow();
        int i = 0;
        size_t bucketIdx = 0;
        size_t curHash = hash(key);
        do {
            bucketIdx = (curHash + i * (i + 1) / 2) % buckets.size();
            i++;
        } while (buckets[bucketIdx].condition == busy && i < buckets.size());
        buckets[bucketIdx].key = key;
        buckets[bucketIdx].condition = busy;
        itemsCount++;
        return true;
    }

    bool has(const Key& key)
    {
        size_t i = 0;
        size_t curHash = hash(key);
        size_t bucketIdx = curHash % buckets.size();
        do {
            if (buckets[bucketIdx].condition == busy && equal(buckets[bucketIdx].key, key))
                return true;
            else if (buckets[bucketIdx].condition == free)
                return false;
            else {
                bucketIdx = (curHash + i * (i + 1) / 2) % buckets.size();
            }
            i++;
        } while (i < buckets.size());
        return false;
    }

    bool del(const Key& key)
    {
        if (!has(key))
            return false;
        size_t i = 0;
        size_t curHash = hash(key);
        size_t bucketIdx = curHash % buckets.size();
        while (i < buckets.size()) {
            if (buckets[bucketIdx].condition == busy && equal(buckets[bucketIdx].key, key)) {
                buckets[bucketIdx].condition = deleted;
                itemsCount--;
                return true;
            } else {
                bucketIdx = (curHash + i * (i + 1) / 2) % buckets.size();
                i++;
            }
        }
        return false;
    }

private:
    static constexpr int initialSize = 8;
    static constexpr int free = 1;
    static constexpr int deleted = 2;
    static constexpr int busy = 3;
    static constexpr int maxLoadFactor = 75;
    static constexpr int sizeIteration = 2;

    struct HashElement {
        Key key;
        int condition;

        HashElement()
            : key()
            , condition(free)
        {
        }
        HashElement(Key& key)
            : key(key)
            , condition(free)
        {
        }
    };

    std::vector<HashElement> buckets;
    Hash hash;
    Equal equal;
    size_t itemsCount;

    size_t squareProbeHash(const Key& key, size_t i)
    {
        return (hash(key) + i * (i + 1) / 2);
    }

    void grow()
    {
        std::vector<HashElement> newBuckets(buckets.size() * sizeIteration);
        size_t newIndex = 0;
        size_t oldIndex = 0;
        for (size_t i = 0; i < buckets.size(); i++) {
            oldIndex = i;
            if (buckets[oldIndex].condition == busy) {
                int j = 0;
                size_t curHash = hash(buckets[oldIndex].key);
                do {
                    newIndex = (curHash + j * (j + 1) / 2) % (buckets.size() * sizeIteration);
                    j++;
                } while (newBuckets[newIndex].condition == busy && j < (buckets.size() * sizeIteration));
                newBuckets[newIndex] = buckets[oldIndex];
                buckets[oldIndex].condition = deleted;
            }
        }
        buckets = std::move(newBuckets);
    }
};

int main()
{
    HashSet<std::string> set;
    std::string key;
    char operation = 0;
    while (std::cin >> operation >> key) {
        bool result = false;
        switch (operation) {
        case '+':
            result = set.add(key);
            break;
        case '?':
            result = set.has(key);
            break;
        case '-':
            result = set.del(key);
            break;
        default:
            break;
        }
        if (result) {
            std::cout << "OK" << std::endl;
        } else {
            std::cout << "FAIL" << std::endl;
        }
    }
    return 0;
}
