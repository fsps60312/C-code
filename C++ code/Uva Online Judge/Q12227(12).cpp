#include<cstdio>
#include<vector>
#include<queue>
#include<cmath>
//#include<cassert>
using namespace std;
typedef long long LL;
void assert(bool valid){if(valid)return;while(1)printf("E");}
const LL INF=2147483647;
void getmin(LL &a,LL b){if(b<a)a=b;}
struct Point
{
	LL x,y,z;
	Point(){}
	void Scanf(){scanf("%lld%lld%lld",&x,&y,&z);}
}BEGIN,END;
LL T,N;
struct Warmhole
{
	Point entry,exit;
	LL creation,shift;
	void Scanf()
	{
		entry.Scanf(),exit.Scanf();
		scanf("%lld%lld",&creation,&shift);
	}
};
vector<Warmhole>WARMHOLE;
LL Hypot(LL a,LL b,LL c){return (LL)(ceil(sqrt(a*a+b*b+c*c))+0.5);}
LL Dis(Point &a,Point &b){return Hypot(a.x-b.x,a.y-b.y,a.z-b.z);}
struct Edge
{
	LL to,creation,shift,cost;
	Edge(LL to=0,LL creation=0,LL shift=0,LL cost=0):to(to),creation(creation),shift(shift),cost(cost){}
};
vector<Edge>AD[50];
LL TIME[50],UPRE[50],CPRE[50],CNT[50],LPRE[50];
bool INQ[50];
LL Solve()
{
	static LL vis_cnt,vis[50];
	vis_cnt=0;
	queue<LL>q;
	for(LL i=0;i<N;i++)
	{
		q.push(i);
		Warmhole &w=WARMHOLE[i];
		TIME[i]=min(Dis(BEGIN,w.exit),max(w.creation,Dis(BEGIN,w.entry))+w.shift);
		UPRE[i]=-1;
		INQ[i]=true;
		CNT[i]=0;
		vis[i]=0;
	}
	while(!q.empty())
	{
		LL u=q.front();q.pop();
		INQ[u]=false,CNT[u]++;
		if(CNT[u]>N+1)
		{
			vis_cnt++;
			vis[u]=vis_cnt;
			for(LL i=UPRE[u];;i=UPRE[i])
			{
				assert(i!=-1);
				if(vis[i]==vis_cnt){u=i;break;}
				vis[i]=vis_cnt;
			}
			vector<int>loop;
			loop.push_back(u);
			for(LL i=UPRE[u];i!=u;i=UPRE[i])loop.push_back(i);
			for(LL i=0;i<N;i++)CNT[i]=0;
			LL mn=INF,idx=-1;
			for(LL i=0;i<loop.size();i++)
			{
				LL &j=UPRE[loop[i]];
				if(CPRE[j]==-INF)continue;
				else if(TIME[j]-(LPRE[j]+CPRE[j])<mn)mn=TIME[j]-(LPRE[j]+CPRE[j]),idx=j;
			}
			if(mn>0)
			{
				assert(idx!=-1);
				TIME[idx]-=mn;
//				printf("LPRE=%lld,CPRE=%lld,TIME[%lld]=%lld\n",LPRE[idx],CPRE[idx],idx,TIME[idx]);
				u=idx;
			}
		}
		for(LL i=0;i<AD[u].size();i++)
		{
			Edge &e=AD[u][i];
			LL time=max(TIME[u]+e.cost,e.creation)+e.shift;
			if(time>=TIME[e.to])continue;
			TIME[e.to]=time;
			UPRE[e.to]=u;
			CPRE[e.to]=e.creation;
			LPRE[e.to]=e.shift;
			if(!INQ[e.to])INQ[e.to]=true,q.push(e.to);
		}
	}
	LL ans=Dis(BEGIN,END);
	for(LL i=0;i<N;i++)
	{
		Warmhole &w=WARMHOLE[i];
		if(TIME[i]+Dis(w.exit,END)<ans)ans=TIME[i]+Dis(w.exit,END);
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%lld",&T)==1)
	{
		while(T--)
		{
			BEGIN.Scanf(),END.Scanf();
			scanf("%lld",&N);
			assert(N>=0&&N<=50);
			WARMHOLE.clear();
			for(LL i=0;i<N;i++)
			{
				static Warmhole w;
				w.Scanf();
				WARMHOLE.push_back(w);
			}
			for(LL i=0;i<N;i++)AD[i].clear();
			for(LL i=0;i<N;i++)
			{
				for(LL j=0;j<N;j++)
				{
					Warmhole &w1=WARMHOLE[i],&w2=WARMHOLE[j];
//					AD[i].push_back(Edge(j,-INF,0,Dis(w1.exit,w2.exit)));
					AD[i].push_back(Edge(j,w2.creation,w2.shift,Dis(w1.exit,w2.entry)));
				}
			}
			printf("%lld\n",Solve());
		}
	}
	return 0;
}
