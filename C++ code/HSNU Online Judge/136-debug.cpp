#include <vector>
#include <map>
#include <cstdio>
using namespace std;
#define for_each(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)
const int MAX_N = 1000;
const int MAX_M = 5000;
const int MAX_DEG = 10;
struct Edge
{
	int start, target, cost, mask;
};
int n, m;
vector<pair<int, int> > graph[MAX_N];
map<int, int> tree[MAX_N];
vector<int> cross[MAX_N];
Edge edge[MAX_M];
int dp[MAX_N][1 << MAX_DEG];
int color[MAX_N];
int depth[MAX_N];
int parent[MAX_N];
int ancestor[MAX_N];
int findAncestor(int i)
{
	return (ancestor[i] == i) ? i : (ancestor[i] = findAncestor(ancestor[i]));
}
void dfsTarjan(int i, int d, int p)
{
	color[i] = 1;
	depth[i] = d;
	parent[i] = p;
	ancestor[i] = i;
	for_each(it, graph[i])
	if (color[it->first] == 0 && edge[it->second].cost == 0)
	{
		dfsTarjan(it->first, d + 1, i);
		ancestor[it->first] = i;
		tree[i].insert(make_pair(it->first, tree[i].size()));
	}
	for_each(it, graph[i])
	if (color[it->first] == 2 && edge[it->second].cost > 0)
	cross[findAncestor(it->first)].push_back(it->second);
	color[i] = 2;
}
void dfsDp(int i)
{
	for_each(it, graph[i])
	if (it->first!=parent[i]&&edge[it->second].cost==0)dfsDp(it->first);
	for_each(it, cross[i])
	if (edge[*it].cost>0&&(depth[edge[*it].start]+depth[edge[*it].target]-depth[i]*2)%2==0)
	for (int k = 0; k < 2; k++)
	{
		int j = (k == 0) ? edge[*it].start : edge[*it].target;
		if (j == i) continue;
		for (edge[*it].cost += dp[j][0]; parent[j] != i; j = parent[j])
		edge[*it].cost += dp[parent[j]][1 << tree[parent[j]][j]];
		edge[*it].mask |= 1 << tree[i][j];
	}
	for (int mask = (1 << (int) tree[i].size()) - 1; mask >= 0; mask--)
	{
		for_each(it, tree[i])
		if (((mask >> it->second) & 1) == 0)
		dp[i][mask] += dp[it->first][0];
		for_each(it, cross[i])
		if (edge[*it].mask > 0 && (mask & edge[*it].mask) == 0)
		dp[i][mask] = max(dp[i][mask], dp[i][mask | edge[*it].mask] + edge[*it].cost);
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	memset(edge, 0, sizeof(edge));
	int total = 0;
	while (m--)
	{
		scanf("%d%d%d", &edge[m].start, &edge[m].target, &edge[m].cost);
		edge[m].start--, edge[m].target--;
		graph[edge[m].start].push_back(make_pair(edge[m].target, m));
		graph[edge[m].target].push_back(make_pair(edge[m].start, m));
		total += edge[m].cost;
	}
	memset(color, 0, sizeof(color));
	dfsTarjan(0, 0, -1);
	memset(dp, 0, sizeof(dp));
	dfsDp(0);
	printf("%d\n", total - dp[0][0]);
	return 0;
}
