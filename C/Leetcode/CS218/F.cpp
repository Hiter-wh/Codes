#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <utility>
#include <queue>
#include <utility>
#include <limits>
using namespace std;
const int INF = numeric_limits<int>::max();
//---------------------Functional functions---------------------//
int d(int x, int y,int n){
    return x*n+y;
}
void add_edge(vector<vector<pair<int, int>>> &graph, int u, int v, int weight) {
    graph[u].push_back({v, weight});

}
//---------------------END---------------------//


//---------------------Input Graph and edges---------------------//
vector<vector<pair<int, int>>> input_matrix(int n, int banana) {
    // Read the Map
    vector<vector<char>> _map(n, vector<char>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> _map[i][j];
        }
    }
    //Calculate the edges, store graph in form of adjacency list
    vector<vector<pair<int, int>>> graph(n*n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int rw=INF;
            if(_map[i][j]=='b'){rw=banana;} else{rw=1;}
            auto v=d(i,j,n);
            if(j>0){auto u=d(i,j-1,n);add_edge(graph, u, v, rw);}
            if(i>0){auto u=d(i-1,j,n);add_edge(graph, u, v, rw);}
            if(j<n-1){auto u=d(i,j+1,n);add_edge(graph, u, v, rw);}
            if(i<n-1){auto u=d(i+1,j,n);add_edge(graph, u, v, rw);}
        }

    }

    return graph;
}
//---------------------END---------------------//






long long dijkstra(const vector<vector<pair<int, int>>> &graph, int source,int destination, int tot_size) {
    int n = graph.size();
    vector<int> distance(n, INF);
    vector<bool> visited(n, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    distance[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (const auto &edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (!visited[v]) {
                int new_distance = distance[u] + weight;
                if (new_distance < distance[v]) {
                    distance[v] = new_distance;
                    pq.push({distance[v], v});
                }
            }
        }
    }


    /*for (int i = 0; i < tot_size; ++i) {
        for (int j = 0; j < tot_size; ++j) {
            cout<<"distance for "<<i<<" and "<<j<<"  is :"<<distance[d(i,j,tot_size)]<<endl;
        }
    }*/



    return distance[destination];
}

int main() {
    int n, banana;

    cin >> n >> banana;
    banana++;
    vector<vector<pair<int, int>>> graph= input_matrix(n,banana);

    int source= d(0,0,n);
    int destination= d(n-1,n-1,n);
    auto result = dijkstra(graph, source,destination,n);
    std::cout<<result;
    return 0;
}