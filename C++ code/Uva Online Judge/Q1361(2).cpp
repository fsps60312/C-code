#include<cstdio>
#include<vector>
#include<algorithm>
#include<stack>
using namespace std;
int N,M;
int CH[20000],VIS[20000];
struct Edge
{
	int a,b;
	bool isloop,vis;
	Edge(){}
	Edge(int a,int b):a(a),b(b),isloop(false),vis(false){}
	int To(int from){return from!=a?a:b;}
};
vector<Edge>EDGE;
vector<int>TO[20000];
int To(int u,int i){return EDGE[TO[u][i]].To(u);}
vector<int>LOOP;
struct Stk
{
	int u,fa,i;
	Stk(){}
	Stk(int u,int fa,int i):u(u),fa(fa),i(i){}
};
bool MarkLoop(int _u,int _fa)
{
	stack<Stk>stk;
	stk.push(Stk(_u,_fa,-1));
	while(!stk.empty())
	{
		Stk s=stk.top();stk.pop();
		int &u=s.u,&fa=s.fa,&i=s.i;
		if(i==-1)
		{
			if(VIS[u])
			{
				int ur=u;
				int ans=0;
				do
				{
					Edge &e=EDGE[TO[u][CH[u]]];
					bool &isloop=e.isloop;
					if(isloop)return false;
//					printf("loop(%d,%d)\n",e.a,e.b);
					isloop=true;
					u=e.To(u);
					ans++;
				}while(u!=ur);
//				printf("ans=%d\n",ans);
				LOOP.push_back(ans);
				continue;
			}
			VIS[u]=true;
		}
		CH[u]=++i;
		if(i>=TO[u].size())continue;
		stk.push(Stk(u,fa,i));
		Edge &e=EDGE[TO[u][i]];
		if(e.vis)continue;
		e.vis=true;
		int j=e.To(u);
		if(j==fa)continue;
		stk.push(Stk(j,u,-1));
	}
	return true;
}
typedef long long LL;
const LL MOD=1000000000LL;
struct Big
{
	vector<LL>d;
	Big(int v){d.clear();d.push_back(v);}
	void carry()
	{
		for(int i=0;;i++)
		{
			if(i==d.size()-1)
			{
				if(d[i]/MOD)
				{
					d.push_back(d[i]/MOD);
					d[i]%=MOD;
					continue;
				}
				else break;
			}
			else
			{
				d[i+1]+=d[i]/MOD;
				d[i]%=MOD;
			}
		}
	}
	Big operator*=(int v)
	{
		for(int i=0;i<d.size();i++)d[i]*=v;
		carry();
	}
	void print()
	{
		int idx=d.size()-1;
		printf("%lld",d[idx]);
		for(idx--;idx>=0;idx--)printf("%09lld",d[idx]);
	}
};
bool solve()
{
	LOOP.clear();
	if(!MarkLoop(0,-1))return false;
	for(int i=0;i<N;i++)if(!VIS[i])return false;
	Big ans=Big(1);
	for(int i=0;i<LOOP.size();i++)ans*=LOOP[i]+1;
	ans.print();
	return true;
}
int main()
{
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)
		{
			TO[i].clear();
			VIS[i]=false;
		}
		EDGE.clear();
		for(int i=0,k;i<M;i++)
		{
			static vector<int>v;
			v.clear();
			scanf("%d",&k);
			int a,b;scanf("%d",&b);b--;
			for(k--;k--;)
			{
				a=b;
				scanf("%d",&b);b--;
				int sz=EDGE.size();
				TO[a].push_back(sz);
				TO[b].push_back(sz);
				EDGE.push_back(Edge(a,b));
			}
		}
		static int kase=0;
		if(kase++)puts("");
		if(!solve())puts("0");
		else puts("");
	}
	return 0;
}
