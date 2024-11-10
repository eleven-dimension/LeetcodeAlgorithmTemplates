#include <bits/stdc++.h>

class LiChaoSegmentTree {
 private:
  struct Line {
    long long m, b;

    Line(long long _m = 0,
         long long _b = -std::numeric_limits<long long>::max())
        : m(_m), b(_b) {}

    long long get(long long x) const { return m * x + b; }
  };

  struct Node {
    Line line;
    Node *left, *right;

    Node() : line(), left(nullptr), right(nullptr) {}
  };

  Node* root;
  long long minX, maxX;

  void insert(Line newLine, Node*& node, long long l, long long r) {
    if (!node) {
      node = new Node();
      node->line = newLine;
      return;
    }

    long long mid = (l + r) / 2;
    bool leftBetter = newLine.get(l) > node->line.get(l);
    bool midBetter = newLine.get(mid) > node->line.get(mid);

    if (midBetter) {
      std::swap(node->line, newLine);
    }

    if (r - l == 1) {
      return;
    } else if (leftBetter != midBetter) {
      insert(newLine, node->left, l, mid);
    } else {
      insert(newLine, node->right, mid, r);
    }
  }

  long long query(long long x, Node* node, long long l, long long r) const {
    if (!node) {
      return -std::numeric_limits<long long>::max();
    }
    if (r - l == 1) {
      return node->line.get(x);
    }
    long long mid = (l + r) / 2;
    long long res = node->line.get(x);
    if (x < mid) {
      res = std::max(res, query(x, node->left, l, mid));
    } else {
      res = std::max(res, query(x, node->right, mid, r));
    }
    return res;
  }

 public:
  LiChaoSegmentTree(long long _minX, long long _maxX)
      : root(nullptr), minX(_minX), maxX(_maxX) {}

  void insertLine(long long m, long long b) {
    Line newLine(m, b);
    insert(newLine, root, minX, maxX);
  }

  long long query(long long x) const { return query(x, root, minX, maxX); }
};