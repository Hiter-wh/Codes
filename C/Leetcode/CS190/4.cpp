#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

double dist_sq(double x1, double y1, double x2, double y2) {
    return pow(x1 - x2, 2) + pow(y1 - y2, 2);
}

int main() {
    double x1, y1, x2, y2;
    int n;
    cin >> x1 >> y1 >> x2 >> y2 >> n;

    double r1 = 0, r2 = 0;
    vector<pair<double, double>> missiles(n);

    for (int i = 0; i < n; ++i) {
        cin >> missiles[i].first >> missiles[i].second;
    }

    for (const auto &missile : missiles) {
        double d1 = dist_sq(x1, y1, missile.first, missile.second);
        double d2 = dist_sq(x2, y2, missile.first, missile.second);

        if (d1 > r1 && d2 > r2) {
            if (d1-r1 > d2-r2) {
                r2 = d2;
            } else {
                r1 = d1;
            }
        }
    }

    cout << static_cast<long long>(r1 + r2) << endl;

    return 0;
}
