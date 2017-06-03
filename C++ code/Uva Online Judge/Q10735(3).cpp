#include<cstdio>
//#include<cassert>
#include<vector>
using namespace std;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
//void bssert(bool valid){if(valid)return;for(int a=0,b=0;;)a/=b;}
struct Hungary
{
	int N,M;
	bool VA[500],VB[1000000];
	int MATCH[1000000],RM[500];
	vector<int>ET[500];
	bool Match(const int u)
	{
		if(VA[u])return false;
		VA[u]=true;
		for(const int nxt:ET[u])
		{
			VB[nxt]=true;
			if(MATCH[nxt]==-1||Match(MATCH[nxt]))
			{
				MATCH[nxt]=u;
				RM[u]=nxt;
				return true;
			}
		}
		return false;
	}
	bool Solve()
	{
		for(int i=0;i<M;i++)MATCH[i]=-1;
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)VA[j]=false;
			for(int j=0;j<M;j++)VB[j]=false;
			if(!Match(i))return false;
		}
		return true;
	}
}HUNGARY;
int V,E;
struct Edge
{
	int a,b,type,color;
	bool vis;
	Edge(){}
	Edge(const int _a,const int _b,const int _t):a(_a),b(_b),type(_t),color(-1),vis(false){}
};
vector<Edge>EDGE;
vector<int>ET[100];
int CUR[100];
int COLOR_CNT;
int GetNxt(const int u)
{
	const int ei=ET[u][CUR[u]];
	EDGE[ei].color=COLOR_CNT;
	return EDGE[ei].b;
}
void MarkColor(const int u)
{
	if(CUR[u]!=-1)
	{
		const Edge &e=EDGE[ET[u][CUR[u]]];
		if(e.vis&&e.color==-1)
		{
			for(int n=GetNxt(u);n!=u;n=GetNxt(n));
			COLOR_CNT++;
			return;
		}
		return;
	}
	for(int &i=CUR[u]=0;i<(int)ET[u].size();i++)
	{
		const int ei=ET[u][i];
		Edge &e=EDGE[ei];
		if(e.color==-1)
		{
			e.vis=true;
			MarkColor(e.b);
			e.vis=false;
		}
	}
	CUR[u]=-1;
}
vector<int>ANS;
vector<bool>CVIS;
void Dfs(const int u,const int color)
{
	ANS.push_back(u);
	for(const int ei:ET[u])
	{
		const Edge &e=EDGE[ei];
		if(e.vis)continue;
		if(!CVIS[e.color])
		{
			CVIS[e.color]=true;
			EDGE[ei].vis=true;
			Dfs(e.b,e.color);
		}
	}
	for(const int ei:ET[u])
	{
		const Edge &e=EDGE[ei];
		if(e.vis)continue;
		if(e.color==color){EDGE[ei].vis=true;Dfs(e.b,color);return;}
	}
} 
bool Solve()
{
	vector<int>idx;
	do
	{
		HUNGARY.N=E;
		int &sz=HUNGARY.M=0;
		for(int i=0;i<E;i++)HUNGARY.ET[i].clear();
		for(int i=0;i<V;i++)
		{
			if(ET[i].size()&1)return false;
			const int cnt=ET[i].size()/2;
			for(int j=0;j<cnt;j++)
			{
				for(const auto ei:ET[i])
				{
					const Edge &e=EDGE[ei];
					if(e.type==0||e.b!=i)HUNGARY.ET[ei].push_back(sz);
				}
				idx.push_back(i);
				sz++;
			}
		}
	}while(0);
	if(!HUNGARY.Solve())return false;
	for(int i=0;i<E;i++)
	{
		const Edge &e=EDGE[i];
		const int u=idx[HUNGARY.RM[i]];
		if(e.type==1)assert(e.a==u&&"type=1");
		else
		{
			if(e.b==u)swap(EDGE[i].a,EDGE[i].b);
			assert(e.a==u&&"type=0");
		}
	}
	for(int i=0;i<V;i++)ET[i].clear(),CUR[i]=-1;
	for(int i=0;i<E;i++)ET[EDGE[i].a].push_back(i);
	COLOR_CNT=0;
	MarkColor(0);
	for(const Edge &e:EDGE)assert(e.color!=-1&&!e.vis);
	CVIS.clear();
	for(int i=0;i<COLOR_CNT;i++)CVIS.push_back(false);
//	ANS.resize(E+1);return true;
	ANS.clear();
	Dfs(0,0);
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	static int casecount;assert(scanf("%d",&casecount)==1);
	while(casecount--)
	{
		assert(scanf("%d%d",&V,&E)==2);
		for(int i=0;i<V;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b,type;i<E;i++)
		{
			static char tmp[2];
			assert(scanf("%d%d%s",&a,&b,tmp)==3);
			a--,b--;
			if(tmp[0]=='U')type=0;
			else assert(tmp[0]=='D'),type=1;
			EDGE.push_back(Edge(a,b,type));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		static int kase=0;
		if(kase++)puts("");
		if(!Solve())puts("No euler circuit exist");
		else
		{
			assert((int)ANS.size()==E+1);
			for(int i=0;i<(int)ANS.size();i++)
			{
				if(i)putchar(' ');
				printf("%d",ANS[i]+1);
			}
			puts("");
		}
	}
	assert(scanf("%d",&casecount)!=1);
	return 0;
}
