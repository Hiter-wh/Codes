#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> bit;

// Update function for the binary indexed tree
void update(int index, int value) {
    while (index < bit.size()) {
        bit[index] = max(bit[index], value);
        index += index & -index;
    }
}

// Query function for the binary indexed tree
int query(int index) {
    int result = 0;
    while (index > 0) {
        result = max(result, bit[index]);
        index -= index & -index;
    }
    return result;
}

int main() {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }

    // Compress the input array to handle large numbers efficiently
    vector<int> sorted_nums = nums;
    sort(sorted_nums.begin(), sorted_nums.end());
    for (int i = 0; i < n; ++i) {
        nums[i] = lower_bound(sorted_nums.begin(), sorted_nums.end(), nums[i]) - sorted_nums.begin() + 1;
    }

    // Initialize the binary indexed tree with size n+1
    bit.resize(n + 1, 0);

    // Iterate through the compressed input array
    int result = 0;
    for (int i = 0; i < n; ++i) {
        // Find the maximum sum of a strictly increasing subarray ending at the current element
        int max_sum = query(nums[i] - 1) + sorted_nums[nums[i] - 1];
        result = max(result, max_sum);

        // Update the binary indexed tree with the current element's maximum sum
        update(nums[i], max_sum);
    }

    cout << result << endl;

    return 0;
}
