#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<queue>
#include<utility>
using namespace std;
const int INF=2147483647;
template<class T>void getmax(T &a,const T &b){if(a<b)a=b;}
template<class T>void getmin(T &a,const T &b){if(b<a)a=b;}
struct SegTree
{
	int S[2000000];
	void Build(const int id,const int l,const int r)
	{
		S[id]=-INF;
		if(l<r)
		{
			const int mid=(l+r)/2;
			Build(id*2,l,mid),Build(id*2+1,mid+1,r);
		}
	}
	void Modify(const int id,const int l,const int r,const int bl,const int br,const int val)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br){getmax(S[id],val);return;}
		const int mid=(l+r)/2;
		Modify(id*2,l,mid,bl,br,val),Modify(id*2+1,mid+1,r,bl,br,val);
	}
	int Query(const int id,const int l,const int r,const int loc)
	{
		if(l==r)return S[id];
		const int ans=S[id],mid=(l+r)/2;
		if(loc<=mid)return max(ans,Query(id*2,l,mid,loc));
		else return max(ans,Query(id*2+1,mid+1,r,loc));
	}
}SEG;
int N,M,DIST[500000],DEPTH[500000];
vector<int>ET[500000],FLOOR[500000];
int GetDepth(const int u)
{
	int &ans=DEPTH[u];
	if(ans!=-1)return ans;
	ans=DIST[u];
	for(int i=0;i<(int)ET[u].size();i++)getmax(ans,GetDepth(ET[u][i]));
	return ans;
}
int GetCost(const int u)
{
	const int h=DIST[u],ans=max(h,DEPTH[u]-h);
	if((int)FLOOR[h].size()==1)return ans;
	const int id=(int)(lower_bound(FLOOR[h].begin(),FLOOR[h].end(),DEPTH[u])-FLOOR[h].begin());
	if(id+1==(int)FLOOR[h].size())return max(ans,FLOOR[h][id-1]+1);
	else return max(ans,FLOOR[h].back()+1);
}
int GetDists()
{
	static int deg[500000];
	for(int i=0;i<N;i++)deg[i]=0;
	for(int i=0;i<N;i++)for(int j=0;j<(int)ET[i].size();j++)++deg[ET[i][j]];
	queue<int>q;
	for(int i=0;i<N;i++)if(deg[i]==0)q.push(i),DIST[i]=0;
	int ans=0;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		ans=DIST[u];
		for(int i=0;i<(int)ET[u].size();i++)
		{
			const int nxt=ET[u][i];
			DIST[nxt]=DIST[u]+1;
			if(!--deg[nxt])q.push(nxt);
		}
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("raj5b.in","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b);
		}
		const int height=GetDists();
		for(int i=0;i<=height;i++)FLOOR[i].clear();
		for(int i=0;i<N;i++)DEPTH[i]=-1;
		for(int i=0;i<N;i++)FLOOR[DIST[i]].push_back(GetDepth(i));
		for(int i=0;i<=height;i++)sort(FLOOR[i].begin(),FLOOR[i].end());
		SEG.Build(1,0,height);
		for(int u=0;u<N;u++)for(int i=0;i<(int)ET[u].size();i++)
		{
			const int nxt=ET[u][i];
			if(DIST[u]+1<DIST[nxt])
			{
				SEG.Modify(1,0,height,DIST[u]+1,DIST[nxt]-1,DEPTH[nxt]-(DIST[nxt]-(DIST[u]+1)));
			}
			else assert(DIST[u]+1==DIST[nxt]);
		}
		pair<int,int>ans=make_pair(INF,-1);
//		for(int i=0;i<=height;i++)printf("SEG[%d]=%d\n",i,SEG.Query(1,0,height,i));
		for(int i=0;i<N;i++)getmin(ans,make_pair(max(GetCost(i),SEG.Query(1,0,height,DIST[i])+1),i));//,printf("(u=%d,h=%d,%d)\n",i,DIST[i],GetCost(i));
		printf("%d %d\n",ans.second+1,ans.first-1);
	}
	return 0;
}
