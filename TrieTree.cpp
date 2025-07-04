#include <iostream>
#include <string>

using namespace std;

struct Node {
    bool end;
    Node* letters[26];
    int count;
    Node() {
        end = false;
        for (int i = 0; i < 26; ++i)
            letters[i] = nullptr;
        count = 0;
    }
};

class TrieTree {
private:
    Node* root;

    Node* remove(Node* node, string word, int index, bool all) {
        if (index != word.length()) {
            if (node->letters[word[index] - 'a'])
                node->letters[word[index] - 'a'] = remove(node->letters[word[index] - 'a'], word, index + 1, all);
            else
                return node;
        }
        else {
            if (!node->end) return node;
            if (all)
                node->count = 0;
            else
                node->count -= 1;
            if (node->count == 0)
                node->end = false;
        }
        if (node == root || node->end)
            return node;
        for (int i = 0; i < 26; ++i)
            if (node->letters[i])
                return node;
        delete node;
        return nullptr;
    }

    void deleteChildren(Node* node) {
        if (node == nullptr) return;
        for (int i = 0; i < 26; ++i)
            deleteChildren(node->letters[i]);
        delete node;
    }

    void print(Node* node, string word) {
        if (node == nullptr) return;
        if (node->end)
            cout << word << " (" << node->count << ")\n";
        for (int i = 0; i < 26; ++i)
            print(node->letters[i], word + (char)('a' + i));
    }
public:
    TrieTree() {
        root = new Node;
    }
    void insert(string word) {
        Node* node = root;
        for (char c : word) {
            if (node->letters[c - 'a'] == nullptr)
                node->letters[c - 'a'] = new Node;
            node = node->letters[c - 'a'];
        }
        node->end = true;
        ++node->count;
    }

    bool find(string word) {
        Node* node = root;
        for (char c : word) {
            if (node->letters[c - 'a'] == nullptr)
                return false;
            node = node->letters[c - 'a'];
        }
        return node->end;
    }

    void remove(string word, bool all = false) {
        remove(root, word, 0, all);
    }

    ~TrieTree() {
        deleteChildren(root);
    }

    void print() {
        for (int i = 0; i < 26; ++i)
            print(root->letters[i], string() + (char)('a' + i));
    }
};

int main() {
    TrieTree tt;
    tt.insert("cat");
    tt.insert("car");
    tt.print();
}
            //if (word.find("cat") != std::string::npos) {
            //    cout << word << endl;
            //}     