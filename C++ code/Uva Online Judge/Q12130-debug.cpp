#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
const int MAXN = 510;

struct node {
	int x, y, h;
	node(int _x = 0, int _y = 0, int _h = 0) {
		x = _x;
		y = _y;
		h = _h;
	}
} arr[MAXN*MAXN];
int map[MAXN][MAXN];
int vis[MAXN][MAXN];
int n, m, d;
int cnt;
int dx[4]={1, -1, 0, 0};
int dy[4]={0, 0, 1, -1};
queue<node> q;

int cmp(node a, node b) {
	return a.h > b.h;
}

void cal() {
	memset(vis, -1, sizeof(vis));
	int ans = 0;
	while (!q.empty())
		q.pop();
	for (int i = 0; i < cnt; i++) {
		node cur = arr[i];
		if (vis[cur.x][cur.y] != -1)
			continue;
		int flag = 1;
		int bound = cur.h - d;
		int top = cur.h;
		q.push(cur);
		int tot = 1;
		while (!q.empty()) {
			cur = q.front();
			q.pop();
			vis[cur.x][cur.y] = top;
			for (int i = 0; i < 4; i++) {
				int nx = cur.x + dx[i];
				int ny = cur.y + dy[i];
				if (nx < 1 || ny < 1 || nx > n || ny > m)
					continue;
				if (map[nx][ny] <= bound)
					continue;
				if (vis[nx][ny] != -1) {
					if (vis[nx][ny] != top)
						flag = 0;
					continue;
				}
				node tmp;
				tmp.x = nx, tmp.y = ny, tmp.h = map[nx][ny];
				vis[nx][ny] = top;
				if (tmp.h == top) 
					tot++;
				q.push(tmp);
			}
		}
		if (flag) 
			ans += tot;
	}
	printf("%d\n", ans);
}

int main() {
//	freopen("in.txt","r",stdin);
//	freopen("new.txt","w",stdout);
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d%d", &n, &m, &d);
		cnt = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				scanf("%d", &map[i][j]);
				arr[cnt++] = node(i, j, map[i][j]);
			}
		sort(arr, arr+cnt, cmp);
		cal();
	}
	return 0;
}
