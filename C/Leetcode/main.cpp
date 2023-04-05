#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    vector<int> prices(9);
    int M;

    // Read the total money amount
    cin >> M;

    // Read prices of numbers 1 to 9
    for (int i = 0; i < 9; ++i) {
        cin >> prices[i];
    }



    // Find the cheapest digit and its cost
    int cheapest_digit = -1;
    int min_cost = INT_MAX;
    for (int i = 0; i < 9; ++i) {
        if (prices[i] < min_cost) {
            min_cost = prices[i];
            cheapest_digit = i + 1;
        }
    }

    // Calculate the maximum length of the resulting number
    int max_length = M / min_cost;

    // If it's not possible to buy any number
    if (max_length == 0) {
        cout << -1 << endl;
        return 0;
    }

    // Replace the digits with more expensive ones while maintaining the affordability
    string result(max_length, '0' + cheapest_digit);
    int remaining_money = M - max_length * min_cost;

    for (int i = 0; i < max_length; ++i) {
        for (int j = 8; j >= 0; --j) {
            int extra_cost = prices[j] - min_cost;
            if (remaining_money >= extra_cost) {
                remaining_money -= extra_cost;
                result[i] = '1' + j;
                break;
            }
        }
    }

    cout << result << endl;
    return 0;
}
