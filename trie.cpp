#include <bits/stdc++.h>

class Trie {
public:
    Trie() : root_(std::make_unique<TrieNode>()) {}

    void insert(const std::string& word) {
        TrieNode* node = root_.get();
        for (const auto& ch : word) {
            if (!node->children.contains(ch)) {
                node->children[ch] = std::make_unique<TrieNode>();
            }
            node = node->children[ch].get();
            node->prefix_count++;
        }
        node->end_count++;
    }

    size_t count(const std::string& word) const {
        const TrieNode* node = findNode(word);
        return node != nullptr ? node->end_count : 0;
    }

    bool search(const std::string& word) const {
        return count(word) > 0;
    }

    bool startsWith(const std::string& prefix) const {
        return findNode(prefix) != nullptr;
    }

    size_t countWordsWithPrefix(const std::string& prefix) const {
        const TrieNode* node = findNode(prefix);
        return node ? node->prefix_count : 0;
    }

private:
    // TODO(eleven-dimension, czsnb): Use a node pool to optimize performance.
    struct TrieNode {
        std::unordered_map<char, std::unique_ptr<TrieNode>> children;
        size_t end_count = 0;
        size_t prefix_count = 0;
    };

    const TrieNode* findNode(const std::string& str) const {
        const TrieNode* node = root_.get();
        for (char ch : str) {
            auto child_iter = node->children.find(ch);
            if (child_iter == node->children.end()) {
                return nullptr;
            }
            node = child_iter->second.get();
        }
        return node;
    }

    std::unique_ptr<TrieNode> root_;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int T;
    std::cin >> T;

    while (T--) {
        int n, m;
        std::cin >> n >> m;

        Trie trie;
        for (int i = 1; i <= n; i++) {
            std::string s;
            std::cin >> s;

            trie.insert(s);
        }

        for (int i = 1; i <= m; i++) {
            std::string s;
            std::cin >> s;

            std::cout << trie.countWordsWithPrefix(s) << std::endl;
        }
    }
}
