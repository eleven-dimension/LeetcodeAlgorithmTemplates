#include <bits/stdc++.h>

class Splay {
 private:
  struct Node {
    int val;
    // repetition of values
    int rep;
    int size;
    int fa;
    int son[2];

    Node() : val(0), rep(0), size(0), fa(0) { son[0] = son[1] = 0; }

    Node(int v, int r, int s, int f, int l_son, int r_son)
        : val(v), rep(r), size(s), fa(f) {
      son[0] = l_son;
      son[1] = r_son;
    }
  };

  std::vector<Node> tree;
  int root = 0;
  // size of the tree
  int sz = 0;

  // del a node
  void clear(int u) {
    tree[u].val = 0;
    tree[u].rep = 0;
    tree[u].size = 0;
    tree[u].fa = 0;
    tree[u].son[0] = 0;
    tree[u].son[1] = 0;
  }

  // get the relationship between fa and u
  int get(int u) { return tree[tree[u].fa].son[1] == u; }

  // update siz
  void update(int u) {
    if (u) {
      tree[u].size = tree[u].rep;
      if (tree[u].son[0])
        tree[u].size += tree[tree[u].son[0]].size;
      if (tree[u].son[1])
        tree[u].size += tree[tree[u].son[1]].size;
    }
  }

  // let u be son of v, r := relaiton, left or right son
  void connect(int u, int v, int r) {
    if (u)
      tree[u].fa = v;
    if (v)
      tree[v].son[r] = u;
  }

  // rotate u upwards
  void rotate(int u) {
    int f = tree[u].fa, ff = tree[f].fa;
    int ru = get(u), rf = get(f);
    connect(tree[u].son[ru ^ 1], f, ru);
    connect(f, u, ru ^ 1);
    connect(u, ff, rf);
    update(f);
    update(u);
  }

  void splay(int u) {
    while (tree[u].fa) {
      int f = tree[u].fa;
      if (tree[f].fa) {
        if (get(u) == get(f))
          rotate(f);
        else
          rotate(u);
      }
      rotate(u);
    }
    root = u;
  }

  int pre() {
    int p = tree[root].son[0];
    while (tree[p].son[1]) {
      p = tree[p].son[1];
    }
    return p;
  }

  int nxt() {
    int p = tree[root].son[1];
    while (tree[p].son[0]) {
      p = tree[p].son[0];
    }
    return p;
  }

 public:
  Splay(int max_size) { tree = std::vector<Node>(max_size); }

  void Push(int x) {
    if (!root) {
      root = ++sz;
      tree[root] = Node{x, 1, 1, 0, 0, 0};
      return;
    }
    int p = root, f = 0;
    while (true) {
      if (x == tree[p].val) {
        tree[p].rep++;
        update(p);
        update(f);
        splay(p);
        return;
      }
      f = p;
      int dir = x > tree[p].val;
      p = tree[p].son[dir];
      if (!p) {
        ++sz;
        tree[sz] = Node{x, 1, 1, f, 0, 0};
        tree[f].son[dir] = sz;
        update(f);
        splay(sz);
        return;
      }
    }
  }

  int NumToRank(int x) {
    int p = root;
    int ans = 0;
    while (true) {
      if (x < tree[p].val) {
        p = tree[p].son[0];
        continue;
      }
      if (tree[p].son[0])
        ans += tree[tree[p].son[0]].size;

      if (x == tree[p].val) {
        splay(p);
        return ans + 1;
      }
      ans += tree[p].rep;
      p = tree[p].son[1];
    }
  }

  int RankToNum(int x) {
    int p = root;
    while (true) {
      if (tree[p].son[0] && x <= tree[tree[p].son[0]].size) {
        p = tree[p].son[0];
        continue;
      }
      if (tree[p].son[0])
        x -= tree[tree[p].son[0]].size;

      if (x <= tree[p].rep) {
        splay(p);
        return tree[p].val;
      }
      x -= tree[p].rep;
      p = tree[p].son[1];
    }
  }

  void Pop(int x) {
    NumToRank(x);
    if (tree[root].rep > 1) {
      tree[root].rep--;
      update(root);
      return;
    }
    if (!tree[root].son[0] && !tree[root].son[1]) {
      clear(root);
      root = 0;
      return;
    }
    if (!tree[root].son[0]) {
      int cpy = root;
      root = tree[root].son[1];
      tree[root].fa = 0;
      clear(cpy);
      return;
    }
    if (!tree[root].son[1]) {
      int cpy = root;
      root = tree[root].son[0];
      tree[root].fa = 0;
      clear(cpy);
      return;
    }

    int cpy = root, left = pre();
    splay(left);
    connect(tree[cpy].son[1], root, 1);
    clear(cpy);
    update(root);
    return;
  }

  int Pre(int x) {
    Push(x);
    int res = tree[pre()].val;
    Pop(x);
    return res;
  }

  int Next(int x) {
    Push(x);
    int res = tree[nxt()].val;
    Pop(x);
    return res;
  }
};