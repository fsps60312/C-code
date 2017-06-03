#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
using namespace std;
const int INF=0x7fffffff;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
template<class T>inline bool getmin(T&a,const T&b){return b<a?(a=b,true):false;}
int N;
vector<int>ET[200000];
pair<int,int>H1[200000],H2[200000];
void Update(const pair<int,int>p,pair<int,int>&h1,pair<int,int>&h2)
{
	if(p.first>h1.first)h2=h1,h1=p;
}
void Update(const int u,const pair<int,int>p)
{
	Update(p,H1[u],H2[u]);
//	if(p.first>H1[u].first)H2[u]=H1[u],H1[u]=p;
//	else if(p.first>H2[u].first)H2[u]=p;
}
void Dfs1(const int u,const int pa)
{
	H1[u]=H2[u]=make_pair(-1,-1);
	for(const int nxt:ET[u])if(nxt!=pa)
	{
		Dfs1(nxt,u);
		Update(u,make_pair((H1[nxt].second==-1?0:H1[nxt].first)+1,nxt));
		Update(u,make_pair((H2[nxt].second==-1?0:H2[nxt].first)+1,nxt));
	}
}
int ANS;
void Dfs2(const int u,const int pa,const pair<int,int>hp1,const pair<int,int>hp2)
{
	if(hp1.second!=-1)Update(u,make_pair(hp,pa));
	if(H1[u].second!=-1&&H2[u].second==-1)
	{
		getmin(ANS,H1[u].first);
		printf("u=%d, len=%d\n",u+1,H1[u].first);
	}
	for(const int nxt:ET[u])if(nxt!=pa)
	{
		const auto pc=(nxt==H1[u].second?H2:H1)[u];
		if(hp==-1&&pc.second==-1)Dfs2(nxt,u,-1);
		else if(hp==-1)Dfs2(nxt,u,pc.first+1);
		else if(pc.second==-1)Dfs2(nxt,u,hp+1);
		else if(hp==pc.first)Dfs2(nxt,u,hp+1);
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b);
			ET[b].push_back(a);
		}
		Dfs1(0,-1);
		ANS=INF;
		Dfs2(0,-1,-1);
		printf("%d\n",ANS==INF?-1:ANS);
	}
	return 0;
}
