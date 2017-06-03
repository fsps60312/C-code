#include <cstdio>  
#include <cstring>  
#include <string>  
#include <vector>  
#include <iostream>  
#include <algorithm>  
using namespace std;

const int N = 30;

vector<string> g[N];
vector<string> ans;

int t, n, parent[N];
bool used[N][1005];

int find(int x){
	return parent[x] == x ? x : parent[x] = find(parent[x]);
}
int vis[N];
int cnt, tot, ru[N], chu[N];
void init(){
	memset(ru, 0, sizeof(ru));
	memset(chu, 0, sizeof(chu));
	memset(vis, 0, sizeof(vis));
	memset(used, 0, sizeof(used));
	for (int i = 0;i < 26;i++){
		g[i].clear();
		parent[i] = i;
	}
	cnt = 1;tot = 0;
	scanf("%d", &n);
	string s;
	while (n--){
		cin >> s;
		int u = s[0] - 'a', v = s[s.length()- 1] - 'a';
		if (!vis[u]){vis[u] = 1;tot++;}
		if (!vis[v]){vis[v] = 1;tot++;}
		ru[v]++;chu[u]++;
		g[u].push_back(s);
		int pu = find(u);
		int pv = find(v);
		if (pu != pv){
			parent[pu] = pv;
			cnt++;
		}
	}
	for (int i = 0;i < 26;i++)
		sort(g[i].begin(), g[i].end());
}
void dfs(int u){
	for (int i = 0;i < g[u].size();i++){
		int v = g[u][i][g[u][i].length()- 1] - 'a';
		if (used[u][i])continue;
		used[u][i] = 1;
		dfs(v);
		ans.push_back(g[u][i]);
	}
}
bool solve(){
	if (cnt != tot)return false;
	int Min = 30;
	int odd = 0, st;
	for (int i = 0;i < 26;i++){
		if (g[i].size())Min = min(Min, i);
		if (ru[i] - chu[i] == -1){
			odd++;
			st = i;
		}
		else if (chu[i] - ru[i] == -1)
			odd++;
		else if (chu[i] != ru[i])return false;
		if (odd > 2)return false;
	}
	ans.clear();
	if (!odd)dfs(Min);
	else dfs(st);
	for (int i = ans.size()- 1;i > 0;i--)
		cout << ans[i] << ".";
	cout << ans[0] << endl;
	return true;
}

int main(){
	freopen("in.txt","r",stdin);
	freopen("new.txt","w",stdout);
	scanf("%d", &t);
	while (t--){
		init();
		if (!solve())printf("***\n");
	}
	return 0;
}

