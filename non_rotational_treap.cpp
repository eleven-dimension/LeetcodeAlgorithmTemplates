#include <bits/stdc++.h>

class Treap {
 private:
  const int INF = std::numeric_limits<int>::max();

  struct Node {
    int ls, rs;
    int size, rnd, val;
  };

  std::vector<Node> t;
  int cnt;
  int root;

  void ModifySize(int p) { t[p].size = t[t[p].ls].size + t[t[p].rs].size + 1; }

  void NewNode(int& k, int x) {
    t[++cnt] = {0, 0, 1, rand(), x};
    k = cnt;
  }

  int Merge(int x, int y) {
    if (!x || !y) {
      return x | y;
    }
    if (t[x].rnd < t[y].rnd) {
      t[x].rs = Merge(t[x].rs, y);
      ModifySize(x);
      return x;
    } else {
      t[y].ls = Merge(x, t[y].ls);
      ModifySize(y);
      return y;
    }
  }

  void Split(int p, int k, int& x, int& y) {
    if (!p) {
      x = y = 0;
      return;
    }
    if (t[p].val <= k) {
      x = p;
      Split(t[p].rs, k, t[p].rs, y);
      ModifySize(x);
    } else {
      y = p;
      Split(t[p].ls, k, x, t[p].ls);
      ModifySize(y);
    }
  }

  int RankToNum(int p, int rank) {
    if (rank == t[t[p].ls].size + 1) {
      return t[p].val;
    } else if (rank <= t[t[p].ls].size) {
      return RankToNum(t[p].ls, rank);
    } else {
      return RankToNum(t[p].rs, rank - t[t[p].ls].size - 1);
    }
  }

 public:
  Treap(int size) : cnt(0), root(0) {
    t = std::vector<Node>(size);
    srand(unsigned(time(NULL)));
  }

  void Push(int v) {
    int x, y, z;
    Split(root, v, x, y);
    NewNode(z, v);
    root = Merge(Merge(x, z), y);
  }

  void Pop(int v) {
    int x, y, z;
    Split(root, v, x, z);
    Split(x, v - 1, x, y);
    y = Merge(t[y].ls, t[y].rs);
    root = Merge(Merge(x, y), z);
  }

  int NumToRank(int v) {
    int x, y;
    Split(root, v - 1, x, y);
    int rank = t[x].size + 1;
    root = Merge(x, y);
    return rank;
  }

  int RankToNum(int rank) { return RankToNum(root, rank); }

  int Pre(int v) {
    int x, y, k, pre;
    Split(root, v - 1, x, y);
    if (!x) {
      return -INF;
    }
    k = t[x].size;
    pre = RankToNum(x, k);
    root = Merge(x, y);
    return pre;
  }

  int Next(int v) {
    int x, y, nex;
    Split(root, v, x, y);
    if (!y) {
      return INF;
    }
    nex = RankToNum(y, 1);
    root = Merge(x, y);
    return nex;
  }
};

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  const int N = 200000 + 50;

  int n, op, val;
  cin >> n;

  Treap treap(N);
  while (n--) {
    cin >> op >> val;
    if (op == 1) {
      treap.Push(val);
    } else if (op == 2) {
      treap.Pop(val);
    } else if (op == 3) {
      cout << treap.NumToRank(val) << endl;
    } else if (op == 4) {
      cout << treap.RankToNum(val) << endl;
    } else if (op == 5) {
      cout << treap.Pre(val) << endl;
    } else {
      cout << treap.Next(val) << endl;
    }
  }
}