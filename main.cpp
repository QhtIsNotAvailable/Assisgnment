#include <cstdio>
#include <iostream>
#include <iomanip>

#include "alist.h"

template <typename T>
void test_func(uint32_t init_size)
{
    uint32_t *init_key = new uint32_t[init_size];
    T *init_value = new T[init_size];
    for (size_t i = 0; i < init_size; i++)
    {
        std::cin >> init_key[i] >> init_value[i];
    }

    // Create an instance of Alist
    // This init_size may not be the actual size of the list due to the duplicate keys
    alist::Alist<T> my_alist(init_size, init_key, init_value);
    delete[] init_key;
    delete[] init_value;

    int n; // num of operations
    int op_type;
    uint32_t key, pos, strategy;
    T value;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        std::cin >> op_type;
        switch (op_type)
        {
        case 0:
            std::cin >> pos >> key >> value;
            my_alist.insert(pos, key, value);
            break;
        case 1:
            std::cin >> pos;
            my_alist.erase(pos);
            break;
        case 2:
            std::cin >> key;
            my_alist.remove(key);
            break;
        case 3:
            std::cin >> key >> value;
            my_alist.push_back(key, value);
            break;
        case 4:
            my_alist.clear();
            break;
        case 5:
            std::cout << std::fixed << std::setprecision(2) << my_alist.pop_back() << std::endl;
            break;
        case 6:
            std::cin >> key;
            std::cout << std::fixed << std::setprecision(2) << my_alist.get_value(key) << std::endl;
            break;
        case 7:
            my_alist.show();
            break;
        case 8:
            std::cin >> strategy;
            my_alist.set_strategy(strategy);
            break;
        case 9:
            std::cin >> key;
            std::cout << my_alist.get_pos(key) << std::endl;
            break;
        case 10:
            my_alist.reverse();
            break;
        default:
            printf("Operation-Type Error!\n");
        }
    }
}

int main()
{
    uint32_t value_type = 1;
    uint32_t init_size = 0;
    std::cin >> value_type >> init_size;

    switch (value_type)
    {
    case 0:
        test_func<int>(init_size);
        break;
    case 1:
        test_func<double>(init_size);
        break;
    default:
        printf("Value-Type Error!\n");
    }
    return 0;
}