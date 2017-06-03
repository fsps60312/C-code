#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=2147483647;
long long Count(const vector<pair<int,int> >&s,const pair<int,int>&l,const pair<int,int>&r){for(int i=1;i<(int)s.size();i++)assert(s[i-1]<=s[i]);return upper_bound(s.begin(),s.end(),l)-lower_bound(s.begin(),s.end(),r);}
int N;
bool VIS[100000];
vector<int>ET[100000];
int MAX_SZ[100000],SZ[100000];
int GetSZ(const int u,const int parent,vector<int>&nodes)
{
	if(VIS[u])return 0;
	nodes.push_back(u);
	int &sz=SZ[u]=1,max_sz=MAX_SZ[u]=0;
	for(int i=0;i<(int)ET[u].size();i++)if(ET[u][i]!=parent)
	{
		const int nxt=ET[u][i];
		const int chsz=GetSZ(nxt,u,nodes);
		sz+=chsz;
		max_sz=max(max_sz,chsz);
	}
	return sz;
}
int FindWeightPoint(const int one_point)
{
	vector<int>nodes;
	const int sz=GetSZ(one_point,-1,nodes);
	int ans_u=-1,ans_sz=INF;
	for(int i=0;i<(int)nodes.size();i++)
	{
		const int u=nodes[i];
//		printf(" %d",u+1);
		const int chsz=min(sz-SZ[u],MAX_SZ[u]);
		if(chsz<ans_sz)ans_sz=chsz,ans_u=u;
	}
//	puts("");
	return ans_u;
}
char SYMBOL[100001];
int GetDif(const int u)
{
	switch(SYMBOL[u])
	{
		case'(':return 1;
		case')':return -1;
		default:assert(0);return 0;
	}
}
#include<utility>
void getmin(int &a,const int b){if(b<a)a=b;}
void DfsHeights(const int u,const int parent,const pair<int,int>&height,vector<pair<int,int> >&ans,const int sign)
{
	if(VIS[u])return;
	ans.push_back(height);
	for(int i=0;i<(int)ET[u].size();i++)if(ET[u][i]!=parent)
	{
		const int nxt=ET[u][i];
		pair<int,int>nxt_height=make_pair(height.first+GetDif(nxt)*sign,height.second);
		getmin(nxt_height.second,nxt_height.first);
		DfsHeights(nxt,u,nxt_height,ans,sign);
	}
}
long long ANS;
void Solve(const int one_point)
{
//	printf("one_point=%d\n",one_point+1);
	const int u=FindWeightPoint(one_point);
	vector<pair<int,int> >allh,allg;
	for(int i=0;i<(int)ET[u].size();i++)
	{
		DfsHeights(ET[u][i],u,make_pair(GetDif(ET[u][i]),min(0,GetDif(ET[u][i]))),allh,1);
		DfsHeights(ET[u][i],u,make_pair(-GetDif(ET[u][i]),min(0,-GetDif(ET[u][i]))),allg,-1);
	}
	sort(allg.begin(),allg.end());
	sort(allh.begin(),allh.end());
	if(SYMBOL[u]=='(')ANS+=Count(allh,make_pair(-1,-1),make_pair(-1,-1));
	else ANS+=Count(allg,make_pair(-1,-1),make_pair(-1,-1));
	for(int i=0;i<(int)ET[u].size();i++)
	{
		vector<pair<int,int> >h,g;
		DfsHeights(ET[u][i],u,make_pair(GetDif(ET[u][i]),min(0,GetDif(ET[u][i]))),h,1);
		DfsHeights(ET[u][i],u,make_pair(-GetDif(ET[u][i]),min(0,-GetDif(ET[u][i]))),g,-1);
		sort(h.begin(),h.end());
		sort(g.begin(),g.end());
		for(int j=0;j<(int)g.size();j++)if(g[j].first==g[j].second)
		{
			const int v=g[j].first-GetDif(u);
			ANS+=Count(allh,make_pair(v,v),make_pair(v,v))-Count(h,make_pair(v,v),make_pair(v,v));
		}
	}
	VIS[u]=true;
	for(int i=0;i<(int)ET[u].size();i++)if(!VIS[ET[u][i]])Solve(ET[u][i]);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		scanf("%s",SYMBOL);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		ANS=0;
		for(int i=0;i<N;i++)VIS[i]=false;
		Solve(0);
		printf("%lld\n",ANS);
	}
	return 0;
}
