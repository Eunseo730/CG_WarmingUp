#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <conio.h>

using namespace std;

const int N = 30;
const int OBSTACLE_COUNT = 30;

char grid[N][N]; // 2D map
bool visited[N][N];

struct Node 
{
    int x, y;
    int dir; // 0: 상, 1: 하, 2: 좌, 3: 우, -1: 시작점
    int len; // 현재 방향으로 몇 칸 왔는지
    vector<pair<int, int>> path; // 경로
};

int dx[] = { 0, 0, -1, 1 };
int dy[] = { -1, 1, 0, 0 };

struct Player
{
    int x;
    int y;
};

Player p{ 0, 1 };

bool inBounds(int x, int y) 
{
    return x >= 0 && x < N && y >= 0 && y < N;
}

void PlaceObstacles() 
{
    srand(time(0));

    int placed = 0;

    while (placed < OBSTACLE_COUNT) 
    {
        int x = rand() % N;
        int y = rand() % N;
        if ((x == 0 && y == 0) || (x == N - 1 && y == N - 1)) continue;
        if (grid[y][x] == '1') {
            grid[y][x] = 'X';
            placed++;
        }
    }
}

bool Bfs() 
{
    queue<Node> q;
    q.push({ 0, 0, -1, 0, {{0, 0}} });
    visited[0][0] = true;

    while (!q.empty()) 
    {
        Node cur = q.front(); q.pop();

        // 도착 확인
        if (cur.x == N - 1 && cur.y == N - 1) 
        {
            // 방향 전환 여부 확인
            int prevDir = -2;
            bool changed = false;

            for (size_t i = 1; i < cur.path.size(); ++i) 
            {
                int dx = cur.path[i].first - cur.path[i - 1].first;
                int dy = cur.path[i].second - cur.path[i - 1].second;
                int dir = (dx == 1) ? 3 : (dx == -1) ? 2 : (dy == 1) ? 1 : 0;
                if (prevDir != -2 && prevDir != dir) 
                {
                    changed = true;
                    break;
                }
                prevDir = dir;
            }
            if (!changed) continue;

            // 경로 기록
            for (auto& p : cur.path)
            {
                grid[p.second][p.first] = '0';
            }
            return true;
        }

        for (int d = 0; d < 4; ++d) 
        {
            int nx = cur.x + dx[d];
            int ny = cur.y + dy[d];

            if (!inBounds(nx, ny)) continue;
            if (grid[ny][nx] == '1' && !visited[ny][nx]) 
            {
                if (cur.dir == d && cur.len >= 5) continue; // 조건1
                if (cur.dir != -1 && cur.dir == d && grid[ny][nx] == 'X') continue; // 장애물 피하기

                visited[ny][nx] = true;
                vector<pair<int, int>> newPath = cur.path;
                newPath.emplace_back(nx, ny);
                q.push({ nx, ny, d, (cur.dir == d ? cur.len + 1 : 1), newPath });
            }
            else if (grid[ny][nx] == 'X') 
            {
                // 장애물 조건: 방향 전환 (이전 방향 제외)
                for (int nd = 0; nd < 4; ++nd) 
                {
                    if (nd == cur.dir) continue;
                    int tx = cur.x + dx[nd];
                    int ty = cur.y + dy[nd];
                    if (inBounds(tx, ty) && grid[ty][tx] == '1' && !visited[ty][tx]) 
                    {
                        visited[ty][tx] = true;
                        vector<pair<int, int>> newPath = cur.path;
                        newPath.emplace_back(tx, ty);
                        q.push({ tx, ty, nd, 1, newPath });
                    }
                }
            }
        }
    }

    return false;
}

void Init()
{
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            grid[i][j] = '1';
}

void Print()
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
            cout << grid[i][j];
        cout << '\n';
    }
}

void MoveUp()
{
    if (grid[p.y - 1][p.x] == '0')
    {
        Player prev = p;
        p.y--;
        grid[p.y][p.x] = '*';
        grid[prev.y][prev.x] = '0';
        Print();
    }

    else
        return;
}

void MoveDown()
{
    if (grid[p.y + 1][p.x] == '0')
    {
        Player prev = p;
        p.y++;
        grid[p.y][p.x] = '*';
        grid[prev.y][prev.x] = '0';
        Print();
    }

    else
        return;
}

void MoveLeft()
{
    if (grid[p.y][p.x - 1] == '0')
    {
        Player prev = p;
        p.x--;
        grid[p.y][p.x] = '*';
        grid[prev.y][prev.x] = '0';
        Print();
    }

    else
        return;
}

void MoveRight()
{
    if (grid[p.y][p.x + 1] == '0')
    {
        Player prev = p;
        p.x++;
        grid[p.y][p.x] = '*';
        grid[prev.y][prev.x] = '0';
        Print();
    }

    else
        return;
}

void Choose()
{
    char choose;
    choose = _getch();

    switch (choose)
    {
    case 13:   // 엔터, 아스키 코드
        Init();
        PlaceObstacles();

        if (!Bfs())
        {
            cout << "경로를 찾을 수 없습니다.\n";
        }

        Print();
        break;
    case 'r':
        grid[p.y][p.x] = '*';
        Print();
        break;
    case 'w':
        MoveUp();
        break;
    case 'a':
        MoveLeft();
        break;
    case 's':
        MoveDown();
        break;
    case 'd':
        MoveRight();
        break;
    }
}

int main() {

    Init();
    PlaceObstacles();

    if (!Bfs()) 
    {
        cout << "경로를 찾을 수 없습니다.\n";
        return 0;
    }
    Print();

    while (true)
    {
        Choose();
    }
}