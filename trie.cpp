#include <bits/stdc++.h>

template <typename CharT>
concept CharConcept = requires(CharT ch) {
    std::is_integral_v<CharT>;
};

template <CharConcept CharT>
class Trie {
public:
    Trie() : root_(new TrieNode()) {}

    void insert(const std::basic_string<CharT>& word) {
        TrieNode* node = root_.get();
        for (const auto& ch : word) {
            if (!node->children_.contains(ch)) {
                node->children_[ch] = std::make_unique<TrieNode>();
            }
            node = node->children_[ch].get();
            node->prefix_count_++;
        }
        node->is_end_ = true;
    }

    bool search(const std::basic_string<CharT>& word) const {
        const TrieNode* node = findNode(word);
        return node != nullptr && node->is_end_;
    }

    bool startsWith(const std::basic_string<CharT>& prefix) const {
        return findNode(prefix) != nullptr;
    }

    size_t countWordsWithPrefix(const std::basic_string<CharT>& prefix) const {
        const TrieNode* node = findNode(prefix);
        return node ? node->prefix_count_ : 0;
    }

private:
    struct TrieNode {
        std::unordered_map<CharT, std::unique_ptr<TrieNode>> children_;
        bool is_end_ = false;
        size_t prefix_count_ = 0;
    };

    const TrieNode* findNode(const std::basic_string<CharT>& str) const {
        const TrieNode* node = root_.get();
        for (const auto& ch : str) {
            if (!node->children_.contains(ch)) {
                return nullptr;
            }
            node = node->children_.at(ch).get();
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