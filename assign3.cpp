#include <iostream>
#include <queue>
using namespace std;

int a[7][7] = {
    {0, 1, 1, 1, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 0},
    {1, 0, 0, 1, 1, 0, 0},
    {1, 1, 1, 0, 1, 0, 0},
    {0, 0, 1, 1, 0, 1, 1},
    {0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 0}
};

void DFS(int start, int end, int visited[]){
    int i = start;
    if(i == end){
        cout << i << " ";
        cout << "\nEnd Reached (DFS)" << endl;
        return;
    }
    cout << i << " ";
    visited[i] = 1;
    for(int j = 0; j < 7; j++){
        if(a[i][j] == 1 && visited[j] == 0){
            DFS(j, end, visited);
            return;
        }
    }
}

void BFS(int start, int end, int visit[]){
    queue<int> q;
    int i = start;
    cout << i << " ";
    visit[i] = 1;
    q.push(i);
    while(!q.empty()){
        int d = q.front();
        q.pop();
        for(int j = 0; j < 7; j++){
            if(a[d][j] == 1 && visit[j] == 0){
                cout << j << " ";
                visit[j] = 1;
                if(j == end){
                    cout << "\nEnd Reached (BFS)" << endl;
                    return;
                }
                q.push(j);
            }
        }
    }
}

int main() {
    int start, end;
    cout << "Enter starting node (0-6): ";
    cin >> start;
    cout << "Enter ending node (0-6): ";
    cin >> end;

    if(start < 0 || start >= 7 || end < 0 || end >= 7){
        cout << "Invalid node input. Please enter nodes between 0 and 6." << endl;
        return 0;
    }

    int BFSvisit[7] = {0};
    int DFSvisit[7] = {0};

    cout << "DFS Traversal: ";
    DFS(start, end, DFSvisit);
    cout << "\nBFS Traversal: ";
    BFS(start, end, BFSvisit);

    return 0;
}

