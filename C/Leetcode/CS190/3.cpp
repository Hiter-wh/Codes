#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<vector<char>> board;
vector<vector<bool>> visited;
int r, c;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

bool is_valid_move(int x, int y, int nx, int ny) {
    if (board[(x + nx) / 2][(y + ny) / 2] == '.') {
        return true;
    }
    return false;
}

int dfs(int x, int y) {
    if (x < 0 || y < 0 || x >= r || y >= c || visited[x][y] || board[x][y] != '.') {
        return 0;
    }

    visited[x][y] = true;
    int area = 1;

    for (int i = 0; i < 4; ++i) {
        int nx = x + 2 * dx[i];
        int ny = y + 2 * dy[i];
        if (is_valid_move(x, y, nx, ny)) {
            area += dfs(nx, ny);
        }
    }

    return area;
}

int main() {
    cin >> r >> c;

    // Adjust the number of rows and columns
    r = r * 2 + 1;
    c = c * 2 + 1;

    board.resize(r, vector<char>(c));
    visited.resize(r, vector<bool>(c, false));

    // Read the board
    for (int i = 0; i < r; ++i) {
        string row;
        cin >> row;
        for (int j = 0; j < c; ++j) {
            board[i][j] = row[j];
        }
    }

    // Find the areas of the four sections
    vector<int> areas;
    for (int i = 1; i < r; i += 2) {
        for (int j = 1; j < c; j += 2) {
            if (!visited[i][j]) {
                areas.push_back(dfs(i, j));
            }
        }
    }

    // Sort and reverse the areas
    sort(areas.begin(), areas.end());
    reverse(areas.begin(), areas.end());

    // Output the areas
    for (int area : areas) {
        cout << area << " ";
    }
    cout << endl;

    return 0;
}
