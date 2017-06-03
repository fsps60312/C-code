#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=2147483647;
long long Count(const vector<int>&s,const int v){return upper_bound(s.begin(),s.end(),v)-lower_bound(s.begin(),s.end(),v);}
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
		printf(" %d",u+1);
		const int chsz=min(sz-SZ[u],MAX_SZ[u]);
		if(chsz<ans_sz)ans_sz=chsz,ans_u=u;
	}
	puts("");
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
void DfsHeights(const int u,const int parent,const int height,vector<int>&ans)
{
	if(VIS[u])return;
	ans.push_back(height);
	for(int i=0;i<(int)ET[u].size();i++)if(ET[u][i]!=parent)
	{
		const int nxt=ET[u][i];
		DfsHeights(nxt,u,height+GetDif(nxt),ans);
	}
}
long long ANS;
void Solve(const int one_point)
{
	printf("one_point=%d\n",one_point+1);
	const int u=FindWeightPoint(one_point);
	vector<int>all;
	for(int i=0;i<(int)ET[u].size();i++)DfsHeights(ET[u][i],u,GetDif(ET[u][i]),all);
	sort(all.begin(),all.end());
	ANS+=Count(all,-1);
	for(int i=0;i<(int)ET[u].size();i++)
	{
		vector<int>h;
		DfsHeights(ET[u][i],u,GetDif(ET[u][i]),h);
		sort(h.begin(),h.end());
		for(int j=0;j<(int)h.size();j++)ANS+=Count(all,h[j]-1)-Count(h,h[j]-1);
	}
	VIS[u]=true;
	for(int i=0;i<(int)ET[u].size();i++)if(!VIS[ET[u][i]])Solve(ET[u][i]);
}
int main()
{
	freopen("in.txt","r",stdin);
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
