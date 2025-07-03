#include <iostream>
#include <string>
#include <list>

using namespace std;

class HashTable {
private:
    struct Cell {
        string key;
        string value;
    };

    int capacity;
    int size;
    float k;
    list<Cell>* arr;

    int h(string key) {
        long long int res = 0;
        for (char c : key) {
            res = res * 13 + c;
        }
        return res % capacity;
    }
public:
    HashTable() {
        capacity = 8;
        size = 0;
        k = 0.6;
        arr = new list<Cell>[capacity];
    }
    ~HashTable() {
        delete[] arr;
    }
    string& operator[](string key) {
        int index = h(key);
        for (Cell& c : arr[index]) {
            if (c.key == key)
                return c.value;
        }
        arr[index].push_back({ key, "" });
        ++size;
        if ((double)size / capacity >= k) {
            expansion();
            index = h(key);
            for (Cell& c : arr[index]) {
                if (c.key == key)
                    return c.value;
            }
        }
        return arr[index].back().value;
    }
    void expansion() {
        list<Cell>* old = arr;
        capacity *= 2;
        arr = new list<Cell>[capacity];
        for (int i = 0; i < capacity / 2; ++i) {
            for (Cell& c : old[i]) {
                int index = h(c.key);
                arr[index].push_back({ c.key, c.value });
            }
        }
        delete[] old;
    }
    void erase(string key) {
        int index = h(key);
        for (auto it = arr[index].begin(); it != arr[index].end(); ++it)
            if (it->key == key) {
                arr[index].erase(it);
                return;
            }
    }
    bool exist(string key) {
        int index = h(key);
        for (Cell& c : arr[index]) {
            if (c.key == key)
                return true;
        }
        return false;
    }
    void print() {
        for (int i = 0; i < capacity; ++i) {
            cout << "[" << i << "]: ";
            if (arr[i].empty())
                cout << "NULL\n";
            else {
                for (Cell& c : arr[i]) {
                    cout << "(Key: " << c.key << "; Value: " << c.value << ") ";
                }
                cout << endl;
            }
        }
    }
};

int main() {
    HashTable ht;
    ht["Oleg"] = "Super";
    ht["Anton"] = "Puper";
    ht["Trofa"] = "Buuuuu";
    ht["Bublik"] = "Tennis";
    ht.print();
}