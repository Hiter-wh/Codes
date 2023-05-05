#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> tree;
vector<bool> is_black;
int result = 0;

int mid_traversal(int node) {
    int subtree_size = 0;

    if (is_black[node]) {// is black

        for (int child : tree[node]) {
            subtree_size = max(mid_traversal(child), subtree_size);
        }
        result = max(result, subtree_size);

        return 0;
    } else {// is not black

        for (int child : tree[node]) {
            subtree_size += mid_traversal(child);
        }
        result = max(result, subtree_size+1);
        return subtree_size + 1;
    }
}

int main() {
    int n, t, k;
    cin >> n >> t;

    tree.resize(n + 1);
    is_black.resize(n + 1, false);

    // Read fathers of nodes and build the tree
    for (int i = 1; i < n; ++i) {
        int father;
        cin >> father;
        tree[father].push_back(i);
    }

    // Read black nodes
    for (int i = 0; i < t; ++i) {
        cin >> k;
        is_black[k] = true;
    }

    mid_traversal(0);
    cout << result << endl;

    return 0;
}
