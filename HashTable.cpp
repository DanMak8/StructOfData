#include <iostream>

using namespace std;

class HashTable {
private:
    struct Cell {
        bool use = false;
        int key;
        int value;
    };

    int capacity;
    int size;
    float k;
    Cell* arr;

    int h(int key) {
        return key * 17 % capacity;
    }
    int h2(int key) {
        int res = key * 5 % capacity;
        if (res % 2 == 0)
            res += 1;
        return res;
    }
public:
    HashTable() {
        capacity = 8;
        size = 0;
        k = 0.5;
        arr = new Cell[capacity];
    }
    ~HashTable() {
        delete[] arr;
    }
    int getIndex(int key) {
        int index = h(key);
        int step = h2(key);
        while (arr[index].use && arr[index].key != key) {
            index += step;
            index %= capacity;
        }
        if (!arr[index].use) {
            arr[index] = { true, key, 0 };
            ++size;
            if ((double)size / capacity >= k) {
                expansion();
                index = getIndex(key);
            }
        }
        return index;
    }
    void expansion() {
        Cell* old = arr;
        capacity *= 2;
        arr = new Cell[capacity];
        size = 0;

        for (int i = 0; i < capacity / 2; ++i) {
            if (old[i].use) {
                int index = getIndex(old[i].key);
                arr[index].value = old[i].value;
            }
        }

        delete[] old;
    }
    int& operator[](int key) {
        int index = getIndex(key);
        return arr[index].value;
    }
    void erase(int key) {
        int index = getIndex(key);
        arr[index].use = false;
    }
    bool exist(int key) {
        int index = h(key);
        while (arr[index].use && arr[index].key != key) {
            index += 1;
            index %= capacity;
        }
        return arr[index].use;
    }
    void print() {
        for (int i = 0; i < capacity; ++i) {
            cout << '[' << i << "] ";
            if (arr[i].use) {
                cout << "Key: " << arr[i].key << " Value: " << arr[i].value << endl;
            }
            else cout << "NULL\n";
        }
    }
};

int main() {
    HashTable ht;
    ht[5] = 25;
    ht[11] = 121;
    ht[12] = 144;
    ht[11] += 5;
    ht.print();
}