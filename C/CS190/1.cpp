#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> numbers = {1, 2, 3, 4, 5};
    int n;

    // Read the number of swaps
    cin >> n;

    // Perform the swaps
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;

        // Swap the values
        swap(numbers[a - 1], numbers[b - 1]);
    }

    // Find the number whose value is 3
    for (int i = 0; i < 5; ++i) {
        if (numbers[i] == 3) {
            cout << i + 1 << endl;
            break;
        }
    }

    return 0;
}
