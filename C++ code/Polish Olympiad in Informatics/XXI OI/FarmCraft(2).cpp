#include<cstdio>
#include<cassert>
#include<utility>
#include<vector>
#include<algorithm>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
int N,C[500000];
vector<int>ET[500000];
bool Cmps(const pair<int,int>&a,const pair<int,int>&b){return a.second-a.first>b.second-b.first;}
pair<int,int>Dfs(const int u,const int parent)
{
	vector<pair<int,int> >s;
	for(int i=0;i<(int)ET[u].size();i++)if(ET[u][i]!=parent)s.push_back(Dfs(ET[u][i],u));
	sort(s.begin(),s.end(),Cmps);
	int t=0;
	int sz=1,ans=C[u];
	for(int i=0;i<(int)s.size();i++)
	{
		getmax(ans,t+1+s[i].second);
		t+=s[i].first*2;
		sz+=s[i].first;
	}
	return make_pair(sz,ans);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&C[i]);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<N-1;i++)scanf("%d%d",&a,&b),--a,--b,ET[a].push_back(b),ET[b].push_back(a);
		pair<int,int>ans=Dfs(0,-1);
		assert(ans.first==N);
		printf("%d\n",max((N-1)*2+C[0],ans.second));
	}
	return 0;
}
