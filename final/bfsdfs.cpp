#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <omp.h>

using namespace std;

vector<int> graph[100];
bool visited[100];

// Parallel BFS
void BFS(int start, int vertices)
{
    // Mark all nodes unvisited
    for (int i = 0; i < vertices; i++)
        visited[i] = false;

    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "\nBFS Traversal: ";

    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        cout << node << " ";

        // Parallel traversal of neighbors
        #pragma omp parallel for
        for (int i = 0; i < graph[node].size(); i++)
        {
            int next = graph[node][i];

            if (!visited[next])
            {
                // Critical section for thread safety
                #pragma omp critical
                {
                    if (!visited[next])
                    {
                        visited[next] = true;
                        q.push(next);
                    }
                }
            }
        }
    }
}

// Parallel DFS
void DFS(int start, int vertices)
{
    // Mark all nodes unvisited
    for (int i = 0; i < vertices; i++)
        visited[i] = false;

    stack<int> s;
    s.push(start);

    cout << "\nDFS Traversal: ";

    while (!s.empty())
    {
        int node = s.top();
        s.pop();

        if (!visited[node])
        {
            visited[node] = true;

            cout << node << " ";

            // Parallel traversal of neighbors
            #pragma omp parallel for
            for (int i = 0; i < graph[node].size(); i++)
            {
                int next = graph[node][i];

                if (!visited[next])
                {
                    // Critical section for thread safety
                    #pragma omp critical
                    {
                        if (!visited[next])
                        {
                            s.push(next);
                        }
                    }
                }
            }
        }
    }
}

int main()
{
    int vertices, edges;
    int u, v;
    int start;

    cout << "Enter number of vertices: ";
    cin >> vertices;

    cout << "Enter number of edges: ";
    cin >> edges;

    cout << "Enter edges (u v):\n";

    for (int i = 0; i < edges; i++)
    {
        cin >> u >> v;

        // Undirected graph
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    cout << "Enter starting vertex: ";
    cin >> start;

    BFS(start, vertices);

    DFS(start, vertices);

    return 0;
}