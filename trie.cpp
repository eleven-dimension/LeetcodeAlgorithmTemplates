#include <bits/stdc++.h>

template <typename CharT>
concept CharConcept = requires(CharT ch) {
    std::is_integral_v<CharT>;
};

template <CharConcept CharT>
class Trie {
public:
    Trie() : root(new TrieNode()) {}

    void insert(const std::basic_string<CharT>& word) {
        TrieNode* node = root.get();
        for (const auto& ch : word) {
            if (!node->children.contains(ch)) {
                node->children[ch] = std::make_unique<TrieNode>();
            }
            node = node->children[ch].get();
            node->prefixCount++;
        }
        node->isEnd = true;
    }

    bool search(const std::basic_string<CharT>& word) const {
        const TrieNode* node = findNode(word);
        return node != nullptr && node->isEnd;
    }

    bool startsWith(const std::basic_string<CharT>& prefix) const {
        return findNode(prefix) != nullptr;
    }

    size_t countWordsWithPrefix(const std::basic_string<CharT>& prefix) const {
        const TrieNode* node = findNode(prefix);
        return node ? node->prefixCount : 0;
    }

private:
    struct TrieNode {
        std::unordered_map<CharT, std::unique_ptr<TrieNode>> children;
        bool isEnd = false;
        size_t prefixCount = 0;
    };

    const TrieNode* findNode(const std::basic_string<CharT>& str) const {
        const TrieNode* node = root.get();
        for (const auto& ch : str) {
            if (!node->children.contains(ch)) {
                return nullptr;
            }
            node = node->children.at(ch).get();
        }
        return node;
    }

    std::unique_ptr<TrieNode> root;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    int T;
    std::cin >> T;

    while (T--) {
        int n, m;
        std::cin >> n >> m;

        Trie<char> trie;
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