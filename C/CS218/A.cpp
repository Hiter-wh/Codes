#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
//Last Update: March, 23,2023
#include <iostream>

int main() {
    // Declare an unordered_map (hash table) with key-value pairs of type (std::string, int)
    std::map<int, int> hashtable;

    // Insert key-value pairs into the hash table
    long long int n,m,t;
    cin>>n;
    for (int i = 0; i < n; ++i) {
        cin>>t;
        hashtable[t] ++;
    }

// Iterate through the sorted map and output the elements
    for (const auto &entry : hashtable) {
        std::cout <<entry.first << " " << entry.second << std::endl;
    }

    return 0;
}
