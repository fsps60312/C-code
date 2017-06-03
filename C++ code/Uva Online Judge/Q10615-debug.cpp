#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
#define N 110
int n, MaxColor;
int color[N][N], link[N], inRow[N], inCol[N];
char map[N][N];
bool vis[N];
vector<int> G[N];
void init()
{
	memset(inRow, 0, sizeof(inRow));
	memset(inCol, 0, sizeof(inCol));
	MaxColor = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		G[i].clear();
		scanf("%s", map[i]);
		for (int j = 0; j < n; j++)
		{
			if (map[i][j] == '*')
			{
				inRow[i]++, inCol[j]++;
				G[i].push_back(j);
			}
		}
	}
	for (int i = 0; i < n; i++)MaxColor = max(MaxColor, max(inRow[i], inCol[i]));
	for (int i = 0; i < n; i++) if (inRow[i] < MaxColor)for (int j = 0; j < n && inRow[i] < MaxColor; j++)
	{
		while (inRow[i] < MaxColor && inCol[j] < MaxColor)
		{
			inRow[i]++;
			inCol[j]++;
			G[i].push_back(j);
		}
	}
}
bool dfs(int u)
{
	for (int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		if (!vis[v])
		{
			vis[v] = true;
			if (!(~link[v]) || dfs(link[v]))
			{
				link[v] = u;
				return true;
			}
		}
	}
	return false;
}
void hungary()
{
	memset(link, -1, sizeof(link));
	for (int i = 0; i < n; i++)
	{
		memset(vis, 0, sizeof(vis));
		dfs(i);
	}
}
void solve()
{
	memset(color, 0, sizeof(color));
	int cnt = 0;
	while (cnt < MaxColor)
	{
		++cnt;
		hungary();
		for (int i = 0; i < n; i++)
		{
			int row = link[i];
			if (map[row][i] == '*') color[row][i] = cnt;
			for (int j = 0; j < G[row].size(); j++)if (G[row][j] == i)
			{
				G[row].erase(G[row].begin() + j);
				break;
			}
		}
	}
	printf("%d\n", MaxColor);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (j)printf(" ");
			printf("%d", color[i][j]);
		}
		printf("\n");
	}
}
int main()
{
	int test;
	scanf("%d", &test);
	while (test--)
	{
		init();
		solve();
	}
	return 0;
}
