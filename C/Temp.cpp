//
//  main.cpp
//  B. Transfer Money
//
//  Created by Majd on 2/20/23.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <cfloat>
#include <queue>
using namespace std;

typedef std::pair<int, int> pair_1;
typedef pair<double, double> iPair;

struct pair_hash
{
    template <class T1, class T2>
    size_t operator() (const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second) << 10;
    }
};
struct myComp {
    constexpr bool operator()(
            pair<int, int> const& a,
            pair<int, int> const& b)
    const noexcept
    {
        return a.second < b.second;
    }
};
void print_List(vector<vector<int>> &adj_list, unordered_map <pair_1, int, pair_hash> &edge_Map){
    cout << "---------------------- " << endl;
    for (int i = 0; i < adj_list.size(); i++) {
        cout << "Node [" << i << "]->";
        for (int j = 0; j < adj_list[i].size(); j++)
        {
            cout << "[" << adj_list[i][j] << "," << edge_Map[make_pair(i, adj_list[i][j])] << "] ";
        }
        cout << endl;
    }
    cout << "---------------------- " << endl;
}


void send_Money(vector<vector<int>> &adj_list, unordered_map <pair_1, int, pair_hash> &edge_Map, int start, int dest, int num_friends){

    vector<double> money(num_friends, INT_MAX);
    money[start] = 100;

    priority_queue<iPair, vector<iPair>, greater<iPair> >pq;

    pq.push(make_pair(100, start));

    // Compute using Dijkstra's Algorithm
    while (!pq.empty()) {
        // Extract min
        double u = pq.top().second;
        pq.pop();
        // Visit neighbors and update
        for(int it = 0; it < adj_list[u].size(); it++) {
            int v = adj_list[u][it];
            if(money[u]/((double)1-(edge_Map[make_pair(u, v)]/(double)100)) < money[v]) // Smaller edge
            {
                money[v]=money[u]/((double)1-(edge_Map[make_pair(u, v)]/(double)100));
                pq.push(make_pair(money[v],v));
                //cout << setprecision(11) << (double)money[v] << endl;
            }
        }
    }
    cout << setprecision(11) << money[dest] << endl;
}

int main(int argc, const char * argv[]) {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    // Store all edges values
    unordered_map <pair_1, int, pair_hash> edge_Map;

    // Number of friends
    int n;
    cin >> n;

    n++;

    // Linked list to store graph
    vector<vector<int>> adj_List(n);

    // Number of edges
    int m;
    cin >> m;


    int input_Node_1;
    int input_Node_2;
    int input_Value;

    // input
    for(int it = 0; it < m; it++){
        // Take input
        cin >> input_Node_1 >> input_Node_2 >> input_Value;

        adj_List[input_Node_1].push_back(input_Node_2);
        adj_List[input_Node_2].push_back(input_Node_1);
        edge_Map[make_pair(input_Node_1, input_Node_2)] = input_Value;
        edge_Map[make_pair(input_Node_2, input_Node_1)] = input_Value;

    }

    int start;
    int dest;
    cin >> start >> dest;

    send_Money(adj_List, edge_Map, start, dest, n);

    return 0;
}