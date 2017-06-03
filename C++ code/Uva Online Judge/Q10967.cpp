#include<cstdio>
#include<vector>
#include<map>
#include<cassert>
#include<queue>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
struct Edge
{
	int to;
	LL cost;
	Edge(){}
	Edge(const int _t,const LL &_c):to(_t),cost(_c){}
};
vector<vector<Edge> >ET;
struct Pq
{
	int u;
	LL cost;
	Pq(){}
	Pq(const int _u,const LL &_c):u(_u),cost(_c){}
	bool operator<(const Pq &p)const{return cost>p.cost;}
};
LL Solve()
{
	const int n=ET.size();
	vector<bool>vis;
	vis.resize(n,false);
	priority_queue<Pq>pq;
	pq.push(Pq(0,0LL));
	while(!pq.empty())
	{
		const Pq p=pq.top();pq.pop();
		if(vis[p.u])continue;
		vis[p.u]=true;
		if(p.u==1)return p.cost;
		for(const Edge &e:ET[p.u])pq.push(Pq(e.to,p.cost+e.cost));
	}
	return INF;
}
void AddEdge(const int a,const int b,const LL &cost,bool directed)
{
	ET[a].push_back(Edge(b,cost));
	if(!directed)ET[b].push_back(Edge(a,cost));
}
map<int,int>IDX;
int GetIdx(const int r,const int c,const int t)
{
	assert(c>=0&&c<100&&t>=0&&t<4);
	const int v=(r*100+c)*4+t;
	const auto it=IDX.find(v);
	if(it!=IDX.end())return it->second;
	const int sz=IDX.size();
	ET.push_back(vector<Edge>());
	return IDX[v]=sz;
}
void Initialize()
{
	static int row,column;assert(scanf("%d%d",&row,&column)==2);
	static char grid[100][101];
	static int direction[100][100];
	vector<int>dr,dc;
	ET.clear(),IDX.clear(),GetIdx(row-1,0,0),GetIdx(0,column-1,0);
	for(int i=0;i<row;i++)
	{
		assert(scanf("%s",grid[i])==1);
		for(int j=0;j<column;j++)switch(grid[i][j])
		{
			case'#':break;
			case'N':case'E':case'S':case'W':
				dr.push_back(i),dc.push_back(j);
				break;
			case'.':
				if(i-1>=0&&grid[i-1][j]=='.')AddEdge(GetIdx(i-1,j,0),GetIdx(i,j,0),1LL,false);
				if(j-1>=0&&grid[i][j-1]=='.')AddEdge(GetIdx(i,j-1,0),GetIdx(i,j,0),1LL,false);
				break;
			default:assert(0);break;
		}
	}
	vector<LL>dw;
	for(int i=0;i<(int)dr.size();i++)
	{
		static LL v;
		assert(scanf("%lld",&v)==1),dw.push_back(v);
		int &d=direction[dr[i]][dc[i]]=-1;
		switch(grid[dr[i]][dc[i]])
		{
			case'W':d++;
			case'S':d++;
			case'E':d++;
			case'N':d++;break;
			default:assert(0);break;
		}
		assert(d>=0&&d<4);
	}
	for(int i=0;i<(int)dr.size();i++)
	{
		const int r=dr[i],c=dc[i],d=direction[r][c];
		const LL &w=dw[i];
		const static int displace[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
		const int outr=r+displace[d][0],outc=c+displace[d][1];
		if(outr>=0&&outr<row&&outc>=0&&outc<column&&grid[outr][outc]=='.')
		{
			AddEdge(GetIdx(outr,outc,0),GetIdx(r,c,d),1LL,true);
			for(int disp=1;disp<=3;disp++)
			{
				const int tr=r+displace[(d+disp)%4][0],tc=c+displace[(d+disp)%4][1];
				AddEdge(GetIdx(r,c,d),GetIdx(r,c,(d+disp)%4),disp==2?w*2LL:w,true);
				if(tr>=0&&tr<row&&tc>=0&&tc<column&&grid[outr][outc]!='#')
				{
					AddEdge(GetIdx(r,c,(d+disp)%4),GetIdx(tr,tc,grid[outr][outc]=='.'?0:(d+disp+2)%4),1LL,true);
				}
			}
		}
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	static int casecount;assert(scanf("%d",&casecount)==1);
	while(casecount--)
	{
		Initialize();
		const LL ans=Solve();
		if(ans==INF)puts("Poor Kianoosh");
		else printf("%lld\n",ans);
	}
	return 0;
}
