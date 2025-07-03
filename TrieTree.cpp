#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct TrieNode {
    TrieNode* children[26];
    bool end;
    int count;

    TrieNode() : end(false), count(0) {
        for (int i = 0; i < 26; ++i) {
            children[i] = nullptr;
        }
    }
};

class Trie {
private:
    TrieNode* root;

    void deleteSubtree(TrieNode* node) {
        if (!node) return;

        for (int i = 0; i < 26; ++i) {
            deleteSubtree(node->children[i]);
        }

        delete node;
    }

    void printAllWords(TrieNode* node, string& currentWord, vector<string>& result) {
        if (!node) return;

        if (node->end) {
            result.push_back(currentWord + " (" + to_string(node->count) + ")");
        }

        for (int i = 0; i < 26; ++i) {
            if (node->children[i]) {
                currentWord.push_back('a' + i);
                printAllWords(node->children[i], currentWord, result);
                currentWord.pop_back();
            }
        }
    }

    bool removeHelper(TrieNode* node, const string& word, int index, bool removeAll) {
        if (!node) return false;

        if (index == word.length()) {
            if (node->end) {
                if (removeAll) {
                    node->count = 0;
                }
                else {
                    node->count--;
                }

                if (node->count <= 0) {
                    node->end = false;
                    node->count = 0;

                    // Check if node has no children
                    for (int i = 0; i < 26; ++i) {
                        if (node->children[i]) {
                            return false;
                        }
                    }
                    return true;
                }
            }
            return false;
        }

        int charIndex = word[index] - 'a';
        if (!node->children[charIndex]) {
            return false;
        }

        bool shouldDeleteChild = removeHelper(node->children[charIndex], word, index + 1, removeAll);

        if (shouldDeleteChild) {
            delete node->children[charIndex];
            node->children[charIndex] = nullptr;

            // Check if current node can be deleted
            if (!node->end) {
                for (int i = 0; i < 26; ++i) {
                    if (node->children[i]) {
                        return false;
                    }
                }
                return true;
            }
        }

        return false;
    }

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        deleteSubtree(root);
    }

    void insert(const string& word) {
        TrieNode* current = root;

        for (char c : word) {
            int index = c - 'a';
            if (!current->children[index]) {
                current->children[index] = new TrieNode();
            }
            current = current->children[index];
        }

        current->end = true;
        current->count++;
    }

    bool search(const string& word) {
        TrieNode* current = root;

        for (char c : word) {
            int index = c - 'a';
            if (!current->children[index]) {
                return false;
            }
            current = current->children[index];
        }

        return current->end;
    }

    void remove(const string& word, bool removeAll = false) {
        removeHelper(root, word, 0, removeAll);
    }

    void print() {
        vector<string> words;
        string currentWord;
        printAllWords(root, currentWord, words);
        for (const string& word : words) {
            //if (word.find("cat") != std::string::npos) {
            //    cout << word << endl;
            //}
            cout << word << endl;
        }
    }
};

int main() {
    Trie trie;

    trie.insert("acatable");
    trie.insert("armorca");
    trie.print();
}