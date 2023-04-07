#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;

    // Read the number of students
    cin >> n;

    // Read the students' scores
    vector<int> scores(n);
    for (int i = 0; i < n; ++i) {
        cin >> scores[i];
    }

    // Sort the scores in descending order
    sort(scores.rbegin(), scores.rend());

    int m;

    // Read the number of queries
    cin >> m;

    // Process the queries
    for (int i = 0; i < m; ++i) {
        int N1;
        cin >> N1;

        // Output the score at the given index
        cout << scores[N1 - 1] << endl;
    }

    return 0;
}
