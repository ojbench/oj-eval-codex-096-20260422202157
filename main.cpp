// Problem 096 - Cousins in a Binary Tree (expanded preorder with -1 as null)
// Reads multiple queries and one line of expanded preorder, outputs 1 if nodes are cousins, else 0

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    if (!(cin >> q)) return 0;
    vector<pair<int,int>> queries;
    queries.reserve(q);
    for (int i = 0; i < q; ++i) {
        int x, y;
        cin >> x >> y;
        queries.emplace_back(x, y);
    }

    // Read the rest of the line as expanded preorder sequence of integers
    vector<int> seq;
    seq.reserve(2048);
    int v;
    while (cin >> v) seq.push_back(v);

    // Build maps: value -> depth, value -> parent
    unordered_map<int,int> depth;
    unordered_map<int,int> parent;
    depth.reserve(seq.size()*2);
    parent.reserve(seq.size()*2);

    // We traverse the expanded preorder sequence using a stack of (parent, depth, state)
    // But since it's expanded with -1 as null, we can simulate recursion with an index
    // Recursive lambda to consume sequence and fill maps
    size_t idx = 0;
    function<void(int,int)> build = [&](int par, int dep){
        if (idx >= seq.size()) return; // safety
        int val = seq[idx++];
        if (val == -1) {
            return; // null node
        }
        parent[val] = par;
        depth[val] = dep;
        build(val, dep+1); // left
        build(val, dep+1); // right
    };

    build(-1, 0);

    // Answer queries
    ostringstream out;
    for (auto [x,y] : queries) {
        auto itx = depth.find(x);
        auto ity = depth.find(y);
        int ans = 0;
        if (itx != depth.end() && ity != depth.end()) {
            if (itx->second == ity->second) {
                int px = parent.count(x) ? parent[x] : -2;
                int py = parent.count(y) ? parent[y] : -3;
                if (px != py) ans = 1;
            }
        }
        out << ans << '\n';
    }

    cout << out.str();
    return 0;
}

